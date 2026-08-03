#include <iomanip>
#include "../../include/IO/Statistics.h"
#include "../../include/Entities/Patient.h"
#include "../../include/Entities/Doctor.h"

Statistics::Statistics()
    : totalPatients(0), emergencyCount(0), regularCount(0),
      escalatedCount(0), totalWT(0.0), totalVT(0.0) {}

void Statistics::record(Patient* p) {
    totalPatients++;
    if (p->getType() == PatientType::Emergency)
        emergencyCount++;
    else
        regularCount++;
    totalWT += p->getWT();
    totalVT += p->getVT();
}

void Statistics::recordEscalation() {
    escalatedCount++;
}

void Statistics::writeStats(std::ofstream& out, Branch* branches, int branchCount) {
    out << "Patients: " << totalPatients
        << " [Emergency: " << emergencyCount
        << ", Regular: " << regularCount << "]\n";

    out << "Branches: " << branchCount << "\n";

    for (int i = 0; i < branchCount; i++) {
        int seniorCount = 0, juniorCount = 0;
        Doctor* docs = branches[i].getDoc();
        int docCnt = branches[i].getDocCnt();

        for (int j = 0; j < docCnt; j++) {
            if (docs[j].getLvl() == DoctorLvl::Senior)
                seniorCount++;
            else
                juniorCount++;
        }

        out << "Branch " << (i + 1) << ": Doctors: " << docCnt
            << " [Senior: " << seniorCount
            << ", Junior: " << juniorCount << "]\n";
    }

    double avgWT = (totalPatients > 0) ? (totalWT / totalPatients) : 0.0;
    double avgVT = (totalPatients > 0) ? (totalVT / totalPatients) : 0.0;

    out << std::fixed << std::setprecision(1);
    out << "Avg Wait = " << avgWT << ", Avg Visit = " << avgVT << "\n";
    out << "Auto-escalated: " << escalatedCount << "\n";
}

int Statistics::getTotalPatients() const { return totalPatients; }
int Statistics::getEscalatedCount() const { return escalatedCount; }
int Statistics::getRegularCount()   const { return regularCount; }
