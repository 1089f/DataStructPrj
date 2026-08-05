#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Events/Event.h"

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
    while (!eventQueue.isEmpty() || anyPatientsWaiting() || anyPatientsInVisit()) {
        // 1. process events due at currentTime
        Event* e = nullptr;
        while (eventQueue.peek(e) && e->getTimestamp() == currentTime) {
            eventQueue.dequeue(e);
            e->Execute(*this);
        }
        // 2. free up doctors (visits done, breaks ended)
        // 3. auto-escalation check
        // 4. assign doctors to waiting patients

        currentTime++;
    }
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
bool Clinic::anyPatientsWaiting() const {
    for (int i = 0; i < numBranches; i++) {
        if (!waitingEmergency[i].isEmpty()) return true;
        if (!waitingRegular[i].isEmpty()) return true;
    }
    return false;
}

bool Clinic::anyPatientsInVisit() const {
    for (int i = 0; i < numBranches; i++) {
        if (!inVisit[i].isEmpty()) return true;
    }
    return false;
}