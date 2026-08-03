#pragma once
#include <fstream>
#include "../Entities/Branch.h"

class Patient;

class Statistics {
private:
    int totalPatients;
    int emergencyCount;
    int regularCount;
    int escalatedCount;
    double totalWT;
    double totalVT;

public:
    Statistics();

    void record(Patient* p);
    void recordEscalation();
    void writeStats(std::ofstream& out, Branch* branches, int branchCount);

    int getTotalPatients() const;
    int getEscalatedCount() const;
    int getRegularCount() const;
};
