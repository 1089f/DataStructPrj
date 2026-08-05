#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Entities/Patient.h"

Clinic::~Clinic() {
    delete[] branches;
    delete[] waitingEmergency;
    delete[] waitingRegular;
    delete[] inVisit;
}
void Clinic::loadUtilities(int setup, int wrapup, int seniorPerTest,
    int juniorPerTest, int autoE) {
    setupDuration = setup;
    wrapupDuration = wrapup;
    seniorPerTestDuration = seniorPerTest;
    juniorPerTestDuration = juniorPerTest;
    autoEscalationLimit = autoE;
}

void Clinic::setBranches(Branch* branchArray, int count) {
    branches = branchArray;
    numBranches = count;

    waitingEmergency = new DoublyLinkedList<Patient*>[count];
    waitingRegular = new PriorityQueue<Patient*>[count];
    inVisit = new DoublyLinkedList<Patient*>[count];
}

void Clinic::addEvent(Event* e) {
    eventQueue.enqueue(e);
}

void Clinic::run() {
}

void Clinic::handleCheckIn(Patient* p) {
    if (!p) return;
    patientLookup.insert(p->getId(), p);

    int brIdx = p->getBranch() - 1;
    if (brIdx < 0 || brIdx >= numBranches) return;

    if (p->getType() == PatientType::Emergency) {
        waitingEmergency[brIdx].insertEnd(p);
    } else {
        double prio = calculatePriority(p->getCheckInTime(), currentTime, p->getNumTests());
        waitingRegular[brIdx].insert(p, prio);
    }
}

void Clinic::handleLeave(int patientId) {
    Patient* p = patientLookup.get(patientId);
    if (!p) return;
    if (p->getType() != PatientType::Regular || p->getStatus() != PatientStatus::Waiting) return;

    int brIdx = p->getBranch() - 1;
    if (brIdx < 0 || brIdx >= numBranches) return;

    Patient* removed = nullptr;
    if (waitingRegular[brIdx].remove(p, removed)) {
        patientLookup.remove(patientId);
        delete removed;
    }
}

void Clinic::handleEscalate(int patientId) {
    Patient* p = patientLookup.get(patientId);
    if (!p) return;
    if (p->getType() != PatientType::Regular || p->getStatus() != PatientStatus::Waiting) return;

    int brIdx = p->getBranch() - 1;
    if (brIdx < 0 || brIdx >= numBranches) return;

    Patient* removed = nullptr;
    if (waitingRegular[brIdx].remove(p, removed)) {
        removed->setType(PatientType::Emergency);
        waitingEmergency[brIdx].insertEnd(removed);
    }
}
double Clinic::calculatePriority(int checkInTime, int currentTime, int numTests) {
    int waitTime = currentTime - checkInTime;
    return (WAIT_WEIGHT * waitTime) - (TEST_WEIGHT * numTests);
}