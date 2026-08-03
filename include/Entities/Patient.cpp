#include "Patient.h"

Patient::Patient()
	: id(0), checkTime(0), type(PatientType::Regular), numTest(0), branch(0),
	wt(0), vt(0), ft(0), st(PatientStatus::Waiting), heapIndex(-1) {
}

Patient::Patient(int id, int checkInTime, PatientType type, int numTests, int branch)
	: id(id), checkTime(checkInTime), type(type), numTest(numTests), branch(branch),
	wt(0), vt(0), ft(0), st(PatientStatus::Waiting), heapIndex(-1) {
}

int Patient::getId() const { return id; }
int Patient::getCheckInTime() const { return checkTime; }
PatientType Patient::getType() const { return type; }
int Patient::getNumTests() const { return numTest; }
int Patient::getBranch() const { return branch; }
int Patient::getWT() const { return wt; }
int Patient::getVT() const { return vt; }
int Patient::getFT() const { return ft; }
PatientStatus Patient::getStatus() const { return st; }

void Patient::setType(PatientType t) { type = t; }
void Patient::setWT(int wtime) { wt = wtime; }
void Patient::setVT(int vtime) { vt = vtime; }
void Patient::setFT(int ftime) { ft = ftime; }
void Patient::setStatus(PatientStatus s) { st = s; }

void Patient::FinalVT(int Ttest, int Tsetup, int Twrapup) {
	vt = Tsetup + Twrapup + (numTest * Ttest);
}

void Patient::setHeapIndex(int index) {
	heapIndex = index;
}

int Patient::getHeapIndex() const {
	return heapIndex;
}
