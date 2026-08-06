#include "../../include/IO/Statistics.h"
#include "../../include/Entities/Patient.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Entities/Doctor.h"
#include <fstream>
#include <iomanip>

Statistics::Statistics()
    : totalPatients(0), emergencyCount(0), regularCount(0),
      escalatedCount(0), totalWT(0.0), totalVT(0.0) {}

void Statistics::record(Patient* p) {
    totalPatients++;
    if (p->getType() == PatientType::Emergency) emergencyCount++;
    else regularCount++;
    totalWT += p->getWT();
    totalVT += p->getVT();
}

void Statistics::recordEscalation() {
    escalatedCount++;
}

void Statistics::writeStats(std::ofstream& out, Branch* branches, int branchCount, int totalRegular) {
    out << "\nPatients: " << totalPatients
        << " [Emergency: " << emergencyCount
        << ", Regular: " << regularCount << "]\n";

    out << "Branches: " << branchCount << "\n";
    for (int i = 0; i < branchCount; i++) {
        int sc = 0, jc = 0;
        Doctor* docs = branches[i].getDoc();
        int cnt = branches[i].getDocCnt();
        for (int j = 0; j < cnt; j++) {
            if (docs[j].getLvl() == DoctorLvl::Senior) sc++;
            else jc++;
        }
        out << "Branch " << branches[i].getBranchNum()
            << ": Doctors: " << cnt
            << " [Senior: " << sc << ", Junior: " << jc << "]\n";
    }

    out << std::fixed << std::setprecision(1);
    double avgWT = totalPatients > 0 ? totalWT / totalPatients : 0.0;
    double avgVT = totalPatients > 0 ? totalVT / totalPatients : 0.0;
    out << "Avg Wait = " << avgWT << ", Avg Visit = " << avgVT << "\n";

    int base = totalRegular > 0 ? totalRegular : (regularCount + escalatedCount);
    out << "Auto-escalated: " << escalatedCount;
    if (base > 0 && escalatedCount > 0)
        out << " (" << std::fixed << std::setprecision(1)
            << (escalatedCount * 100.0 / base) << "%)";
    out << "\n";
}

int Statistics::getTotalPatients() const { return totalPatients; }
int Statistics::getEscalatedCount() const { return escalatedCount; }
int Statistics::getRegularCount() const { return regularCount; }
