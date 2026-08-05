#include "../../include/Entities/Doctor.h"

Doctor::Doctor()
    : branch(0), lvl(DoctorLvl::Junior), shiftStart(0),
    brAfter(0), brDur(0), status(DoctorAvlbl::OffShift), patientSncBr(0),
    busyUntil(-1), breakEndsAt(-1), currentPatient(nullptr) {
}

Doctor::Doctor(int branch, DoctorLvl lvl, int shiftStart, int brAfter, int breakDur)
    : branch(branch), lvl(lvl), shiftStart(shiftStart),
    brAfter(brAfter), brDur(breakDur), status(DoctorAvlbl::OffShift), patientSncBr(0),
    busyUntil(-1), breakEndsAt(-1), currentPatient(nullptr) {
}

int Doctor::getBranch() const { return branch; }
DoctorLvl Doctor::getLvl() const { return lvl; }
int Doctor::getShiftStart() const { return shiftStart; }
int Doctor::getBreakAfter() const { return brAfter; }
int Doctor::getBreakDur() const { return brDur; }
DoctorAvlbl Doctor::getAvlbl() const { return status; }
int Doctor::getPatientSncBr() const { return patientSncBr; }

int Doctor::getBusyUntil() const { return busyUntil; }
int Doctor::getBreakEndsAt() const { return breakEndsAt; }
Patient* Doctor::getCurrentPatient() const { return currentPatient; }

void Doctor::setAvlbl(DoctorAvlbl a) { status = a; }
void Doctor::setPatientSncBr(int cnt) { patientSncBr = cnt; }

void Doctor::assignPatient(Patient* p, int finishTime) {
    currentPatient = p;
    busyUntil = finishTime;
    status = DoctorAvlbl::Busy;
}

void Doctor::finishVisit(int currentTime) {
    currentPatient = nullptr;
    busyUntil = -1;
    patientSncBr++;

    if (brAfter > 0 && patientSncBr >= brAfter) {
        status = DoctorAvlbl::OnBreak;
        breakEndsAt = currentTime + brDur;
        patientSncBr = 0;
    }
    else {
        status = DoctorAvlbl::Available;
    }
}

void Doctor::endBreak() {
    status = DoctorAvlbl::Available;
    breakEndsAt = -1;
}

bool Doctor::IsAvlbl(int currentTime) const {
    return currentTime >= shiftStart && status == DoctorAvlbl::Available;
}