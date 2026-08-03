#pragma once
#include <string>

enum class PatientType { Regular, Emergency };
enum class PatientStatus { Waiting, InTest, Finished};

class Patient {
private:
    int id;
    int checkTime;
    int numTest;
    PatientType type;
    int wt, vt, ft;
    PatientStatus st;
    int branch;
    int heapIndex;

public:
    Patient();
    Patient(int id, int checkInTime, PatientType type, int numTests, int branch);

    int getId() const;
    int getCheckInTime() const;
    PatientType getType() const;
    int getNumTests() const;
    int getBranch() const;
    int getWT() const;
    int getVT() const;
    int getFT() const;
    PatientStatus getStatus() const;

    void setType(PatientType type);   // in case of escalation
    void setWT(int wt);
    void setVT(int vt);
    void setFT(int ft);
    void setStatus(PatientStatus st);

    void FinalVT(int Ttest, int Tsetup, int Twrapup);

    void setHeapIndex(int index);
    int getHeapIndex() const;
};
