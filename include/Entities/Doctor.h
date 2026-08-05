// NOTE (Member 4 / Hassan):
// The Scheduler queries these every tick - please don't remove or rename:
//   getAvlbl(), getBusyUntil(), getBreakEndsAt(), getCurrentPatient()
//   assignPatient(p, finishTime), finishVisit(currentTime), endBreak()
//   DoctorAvlbl::Busy
// finishVisit() replaced PatientSeen() - it also records when the break
// ends, which PatientSeen() never did (so doctors never came back).
#pragma once

enum class DoctorLvl { Senior, Junior };
enum class DoctorAvlbl { Available, Busy, OnBreak, OffShift };

class Patient;
class Doctor {
private:
    int branch;
    DoctorLvl lvl;
    int shiftStart;
    int brAfter;
    int brDur;
    DoctorAvlbl status;
    int patientSncBr;
    int busyUntil;
    int breakEndsAt;
    Patient* currentPatient;
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
    int getBusyUntil() const;
    int getBreakEndsAt() const;
    Patient* getCurrentPatient() const;
    void assignPatient(Patient* p, int finishTime);
    void finishVisit(int currentTime);
    void endBreak();
    void setAvlbl(DoctorAvlbl a);
    void setPatientSncBr(int cnt);

    void PatientSeen();
    bool IsAvlbl(int currTime) const;

};
