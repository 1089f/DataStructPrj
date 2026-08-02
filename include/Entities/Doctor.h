#pragma once

enum class DoctorLvl { Senior, Junior };
enum class DoctorAvlbl {Available, OnBreak, OffShift};

class Doctor {
private:
    int branch;
    DoctorLvl lvl;
    int shiftStart;
    int brAfter;
    int brDur;
    DoctorAvlbl status;
    int patientSncBr;
public:
    Doctor();
    Doctor(int branch, DoctorLvl lvl, int shiftStart, int brAfter, int breakDur);

    int getBranch() const;
    DoctorLvl getLvl() const;
    int getShiftStart() const;
    int getBreakAfter() const;
    int getBreakDur() const;
    DoctorAvlbl getAvlbl() const;
    int getPatientSncBr() const;

    void setAvlbl(DoctorAvlbl a);
    void setPatientSncBr(int cnt);

    void PatientSeen();
    bool IsAvlbl(int currTime) const;

};
