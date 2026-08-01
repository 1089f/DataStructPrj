#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Branch.h"

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
}

void Clinic::handleLeave(int patientId) {
}

void Clinic::handleEscalate(int patientId) {
}
double Clinic::calculatePriority(int checkInTime, int currentTime, int numTests) {
    int waitTime = currentTime - checkInTime;
    return (WAIT_WEIGHT * waitTime) - (TEST_WEIGHT * numTests);
}