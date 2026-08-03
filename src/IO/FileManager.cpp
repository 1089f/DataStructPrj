#include <fstream>
#include <iostream>
#include <iomanip>
#include "../../include/IO/FileManager.h"
#include "../../include/IO/Statistics.h"
#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Entities/Doctor.h"
#include "../../include/Entities/Patient.h"
#include "../../include/Events/CheckIn.h"
#include "../../include/Events/Leave.h"
#include "../../include/Events/Urgent.h"

FileManager::FileManager() {}

bool FileManager::LoadData(const std::string& filepath, Clinic& clinic) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file: " << filepath << "\n";
        return false;
    }

    int B, SU, WU, PS, PJ;
    file >> B >> SU >> WU >> PS >> PJ;

    int* docCounts = new int[B];
    for (int i = 0; i < B; i++) {
        file >> docCounts[i];
    }

    int totalDoctors = 0;
    for (int i = 0; i < B; i++) {
        totalDoctors += docCounts[i];
    }

    Branch* branches = new Branch[B];
    for (int i = 0; i < B; i++) {
        branches[i] = Branch(i + 1, docCounts[i]);
    }

    int* fillIdx = new int[B]();
    for (int d = 0; d < totalDoctors; d++) {
        int br, sh, ba, bd;
        char sp;
        file >> br >> sp >> sh >> ba >> bd;

        DoctorLvl lvl = (sp == 'S') ? DoctorLvl::Senior : DoctorLvl::Junior;
        Doctor doc(br, lvl, sh, ba, bd);
        branches[br - 1].setDoc(fillIdx[br - 1]++, doc);
    }

    delete[] docCounts;
    delete[] fillIdx;

    int autoE;
    file >> autoE;

    clinic.loadUtilities(SU, WU, PS, PJ, autoE);
    clinic.setBranches(branches, B);

    int M;
    file >> M;

    for (int i = 0; i < M; i++) {
        char eventType;
        file >> eventType;

        if (eventType == 'C') {
            char typ;
            int ts, id, br, tests;
            file >> typ >> ts >> id >> br >> tests;

            PatientType pType = (typ == 'E') ? PatientType::Emergency : PatientType::Regular;
            clinic.addEvent(new CheckIn(ts, pType, id, br, tests));

        } else if (eventType == 'L') {
            int ts, id;
            file >> ts >> id;
            clinic.addEvent(new Leave(ts, id));

        } else if (eventType == 'U') {
            int ts, id;
            file >> ts >> id;
            clinic.addEvent(new Urgent(ts, id));
        }
    }

    file.close();
    return true;
}

void FileManager::WriteOutput(const std::string& filepath,
                              DoublyLinkedList<Patient*>& doneList,
                              Branch* branches, int branchCount,
                              int totalRegular, int escalatedCount) {
    int n = doneList.size();
    if (n == 0) return;

    Patient** arr = new Patient*[n];
    int idx = 0;

    DoublyLinkedList<Patient*>::Node* cur = doneList.getHead();
    while (cur != nullptr) {
        arr[idx++] = cur->data;
        cur = cur->next;
    }

    mergeSort(arr, 0, n - 1);

    Statistics stats;
    for (int i = 0; i < n; i++) {
        stats.record(arr[i]);
    }

    std::ofstream out(filepath);
    if (!out.is_open()) {
        std::cerr << "Error: cannot write to file: " << filepath << "\n";
        delete[] arr;
        return;
    }

    out << std::left
        << std::setw(6) << "FT"
        << std::setw(6) << "ID"
        << std::setw(6) << "CT"
        << std::setw(6) << "WT"
        << "VT\n";

    for (int i = 0; i < n; i++) {
        Patient* p = arr[i];
        out << std::setw(6) << p->getFT()
            << std::setw(6) << p->getId()
            << std::setw(6) << p->getCheckInTime()
            << std::setw(6) << p->getWT()
            << p->getVT() << "\n";
    }

    out << "\n";
    stats.writeStats(out, branches, branchCount);

    out.close();
    delete[] arr;
}

int FileManager::comparePatients(Patient* a, Patient* b) {
    if (a->getFT() != b->getFT())
        return a->getFT() - b->getFT();
    if (a->getNumTests() != b->getNumTests())
        return a->getNumTests() - b->getNumTests();
    return a->getId() - b->getId();
}

void FileManager::merge(Patient** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Patient** L = new Patient*[n1];
    Patient** R = new Patient*[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comparePatients(L[i], R[j]) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void FileManager::mergeSort(Patient** arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
