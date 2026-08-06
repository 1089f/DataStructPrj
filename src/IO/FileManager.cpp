#include "../../include/IO/FileManager.h"
#include "../../include/IO/Statistics.h"
#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Entities/Doctor.h"
#include "../../include/Entities/Patient.h"
#include "../../include/Events/CheckIn.h"
#include "../../include/Events/Leave.h"
#include "../../include/Events/Urgent.h"
#include <fstream>

FileManager::FileManager() {}

bool FileManager::LoadData(const std::string& filepath, Clinic& clinic) {
    std::ifstream in(filepath);
    if (!in.is_open()) return false;

    int B, SU, WU, PS, PJ;
    in >> B >> SU >> WU >> PS >> PJ;

    Branch* branches = new Branch[B];
    int total = 0;
    for (int i = 0; i < B; i++) {
        int n;
        in >> n;
        branches[i] = Branch(i + 1, n);
        total += n;
    }

    int* slot = new int[B]();
    for (int d = 0; d < total; d++) {
        int BR, SH, BA, BD;
        char SP;
        in >> BR >> SP >> SH >> BA >> BD;
        DoctorLvl lvl = (SP == 'S') ? DoctorLvl::Senior : DoctorLvl::Junior;
        branches[BR - 1].setDoc(slot[BR - 1]++, Doctor(BR, lvl, SH, BA, BD));
    }
    delete[] slot;

    clinic.setBranches(branches, B);

    int autoE;
    in >> autoE;
    clinic.loadUtilities(SU, WU, PS, PJ, autoE);

    int M;
    in >> M;

    for (int i = 0; i < M; i++) {
        char ev;
        in >> ev;
        if (ev == 'C') {
            char pt;
            int TS, ID, BR, TESTS;
            in >> pt >> TS >> ID >> BR >> TESTS;
            PatientType type = (pt == 'E') ? PatientType::Emergency : PatientType::Regular;
            clinic.addEvent(new CheckIn(TS, type, ID, BR, TESTS));
        } else if (ev == 'L') {
            int TS, ID;
            in >> TS >> ID;
            clinic.addEvent(new Leave(TS, ID));
        } else {
            int TS, ID;
            in >> TS >> ID;
            clinic.addEvent(new Urgent(TS, ID));
        }
    }

    in.close();
    return true;
}

int FileManager::comparePatients(Patient* a, Patient* b) {
    if (a->getFT() != b->getFT()) return a->getFT() - b->getFT();
    if (a->getNumTests() != b->getNumTests()) return a->getNumTests() - b->getNumTests();
    return a->getId() - b->getId();
}

void FileManager::merge(Patient** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Patient** L = new Patient*[n1];
    Patient** R = new Patient*[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comparePatients(L[i], R[j]) <= 0) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void FileManager::mergeSort(Patient** arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void FileManager::WriteOutput(const std::string& filepath,
                               DoublyLinkedList<Patient*>& doneList,
                               Branch* branches, int branchCount,
                               int totalRegular, int escalatedCount) {
    int n = doneList.size();
    Patient** arr = new Patient*[n > 0 ? n : 1];
    DoublyLinkedList<Patient*>::Node* node = doneList.getHead();
    for (int i = 0; i < n; i++, node = node->next)
        arr[i] = node->data;

    if (n > 1) mergeSort(arr, 0, n - 1);

    std::ofstream out(filepath);
    out << "FT ID CT WT VT\n";
    for (int i = 0; i < n; i++) {
        out << arr[i]->getFT() << " "
            << arr[i]->getId() << " "
            << arr[i]->getCheckInTime() << " "
            << arr[i]->getWT() << " "
            << arr[i]->getVT() << "\n";
    }

    Statistics stats;
    for (int i = 0; i < n; i++) stats.record(arr[i]);
    for (int i = 0; i < escalatedCount; i++) stats.recordEscalation();

    stats.writeStats(out, branches, branchCount, totalRegular);

    delete[] arr;
    out.close();
}
