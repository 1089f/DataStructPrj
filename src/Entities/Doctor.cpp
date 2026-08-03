#include "../../include/Entities/Doctor.h"

Doctor::Doctor()
    : branch(0), lvl(DoctorLvl::Junior), shiftStart(0),
    brAfter(0), brDur(0), status(DoctorAvlbl::OffShift), patientSncBr(0) {
}

Doctor::Doctor(int branch, DoctorLvl lvl, int shiftStart, int brAfter, int breakDur)
    : branch(branch), lvl(lvl), shiftStart(shiftStart),
    brAfter(brAfter), brDur(breakDur), status(DoctorAvlbl::OffShift), patientSncBr(0) {
}

int Doctor::getBranch() const { return branch; }
DoctorLvl Doctor::getLvl() const { return lvl; }
int Doctor::getShiftStart() const { return shiftStart; }
int Doctor::getBreakAfter() const { return brAfter; }
int Doctor::getBreakDur() const { return brDur; }
DoctorAvlbl Doctor::getAvlbl() const { return status; }
int Doctor::getPatientSncBr() const { return patientSncBr; }

void Doctor::setAvlbl(DoctorAvlbl a) { status = a; }
void Doctor::setPatientSncBr(int cnt) { patientSncBr = cnt; }

void Doctor::PatientSeen() {
    patientSncBr++;
    if (patientSncBr >= brAfter) {
        status = DoctorAvlbl::OnBreak;
        patientSncBr = 0;
    }
}

bool Doctor::IsAvlbl(int currentTime) const {
    return currentTime >= shiftStart && status == DoctorAvlbl::Available;
}