#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Events/Event.h"
#include "../../include/Entities/Patient.h"
#include "../../include/Entities/Doctor.h"
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
        Event* e = nullptr;
        while (eventQueue.peek(e) && e->getTimestamp() == currentTime) {
            eventQueue.dequeue(e);
            e->Execute(*this);
        }
        for (int b = 0; b < numBranches; b++) {
            Doctor* docs = branches[b].getDoc();
            int n = branches[b].getDocCnt();

            for (int d = 0; d < n; d++) {
                Doctor& doc = docs[d];

                if (doc.getAvlbl() == DoctorAvlbl::Busy && doc.getBusyUntil() == currentTime) {
                    Patient* p = doc.getCurrentPatient();
                    if (p) {
                        p->setFT(currentTime);
                        p->setStatus(PatientStatus::Finished);

                        auto* node = inVisit[b].getHead();
                        while (node != nullptr) {
                            if (node->data == p) {
                                inVisit[b].removeNode(node);
                                break;
                            }
                            node = node->next;
                        }
                        donePatients.insertEnd(p);
                    }
                    doc.finishVisit(currentTime);
                }
                else if (doc.getAvlbl() == DoctorAvlbl::OnBreak && doc.getBreakEndsAt() == currentTime) {
                    doc.endBreak();
                }
                else if (doc.getAvlbl() == DoctorAvlbl::OffShift && currentTime >= doc.getShiftStart()) {
                    doc.setAvlbl(DoctorAvlbl::Available);
                }
            }
        }
        for (int b = 0; b < numBranches; b++) {
            // collect patients past the threshold before removing any,
            // since remove() reshuffles the heap and invalidates indices
            DoublyLinkedList<Patient*> toEscalate;

            for (int i = 0; i < waitingRegular[b].size(); i++) {
                Patient* p = nullptr;
                if (waitingRegular[b].getAt(i, p) && p != nullptr) {
                    if (currentTime - p->getCheckInTime() > autoEscalationLimit) {
                        toEscalate.insertEnd(p);
                    }
                }
            }

            auto* node = toEscalate.getHead();
            while (node != nullptr) {
                Patient* p = node->data;
                Patient* removed = nullptr;
                if (waitingRegular[b].remove(p, removed)) {
                    removed->setType(PatientType::Emergency);
                    waitingEmergency[b].insertEnd(removed);
                    escalatedCount++;
                }
                node = node->next;
            }
        }
        // recompute priorities so wait time affects ordering as time advances
for (int b = 0; b < numBranches; b++) {
    int n = waitingRegular[b].size();
    if (n == 0) continue;

    // pull everyone out, then reinsert with fresh scores
    Patient** tmp = new Patient*[n];
    int cnt = 0;
    Patient* p = nullptr;
    while (waitingRegular[b].extractMax(p)) {
        tmp[cnt++] = p;
    }
    for (int i = 0; i < cnt; i++) {
        double prio = calculatePriority(tmp[i]->getCheckInTime(), currentTime, tmp[i]->getNumTests());
        waitingRegular[b].insert(tmp[i], prio);
    }
    delete[] tmp;
}
        // 4. assign doctors to waiting patients
        for (int b = 0; b < numBranches; b++) {

            // Emergency first   prefer Senior, fall back to Junior
            while (!waitingEmergency[b].isEmpty()) {
                Doctor* doc = findDoctor(b, true);
                if (doc == nullptr) break;

                Patient* p = nullptr;
                if (!waitingEmergency[b].removeHead(p)) break;

                startVisit(p, doc, b);
            }

            // Then Regular   prefer Junior, fall back to Senior
            while (!waitingRegular[b].isEmpty()) {
                Doctor* doc = findDoctor(b, false);
                if (doc == nullptr) break;

                Patient* p = nullptr;
                if (!waitingRegular[b].extractMax(p)) break;

                startVisit(p, doc, b);
            }
        }

        currentTime++;
    }
}

void Clinic::handleCheckIn(Patient* p) {
    if (!p) return;
    patientLookup.insert(p->getId(), p);

    int brIdx = p->getBranch() - 1;
    if (brIdx < 0 || brIdx >= numBranches) return;

    if (p->getType() == PatientType::Emergency) {
        waitingEmergency[brIdx].insertEnd(p);
    } else {
        totalRegularPatients++;
        double prio = calculatePriority(p->getCheckInTime(), currentTime, p->getNumTests());
        waitingRegular[brIdx].insert(p, prio);
    }
}

void Clinic::handleLeave(int patientId) {
    Patient* p = patientLookup.get(patientId);
    if (!p) return;
    if (p->getStatus() != PatientStatus::Waiting) return;

    int brIdx = p->getBranch() - 1;
    if (brIdx < 0 || brIdx >= numBranches) return;

    if (p->getType() == PatientType::Emergency) {
        auto* node = waitingEmergency[brIdx].getHead();
        while (node != nullptr) {
            if (node->data == p) {
                waitingEmergency[brIdx].removeNode(node);
                patientLookup.remove(patientId);
                delete p;
                return;
            }
            node = node->next;
        }
    }
    else {
        Patient* removed = nullptr;
        if (waitingRegular[brIdx].remove(p, removed)) {
            patientLookup.remove(patientId);
            delete removed;
        }
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
    return -(WAIT_WEIGHT * checkInTime) - (TEST_WEIGHT * numTests);
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
Doctor* Clinic::findDoctor(int branchIdx, bool preferSenior) {
    Doctor* docs = branches[branchIdx].getDoc();
    int n = branches[branchIdx].getDocCnt();

    DoctorLvl first = preferSenior ? DoctorLvl::Senior : DoctorLvl::Junior;
    DoctorLvl second = preferSenior ? DoctorLvl::Junior : DoctorLvl::Senior;

    for (int d = 0; d < n; d++) {
        if (docs[d].IsAvlbl(currentTime) && docs[d].getLvl() == first) return &docs[d];
    }
    for (int d = 0; d < n; d++) {
        if (docs[d].IsAvlbl(currentTime) && docs[d].getLvl() == second) return &docs[d];
    }
    return nullptr;
}
void Clinic::startVisit(Patient* p, Doctor* doc, int branchIdx) {

    int perTest = (doc->getLvl() == DoctorLvl::Senior)
        ? seniorPerTestDuration
        : juniorPerTestDuration;

    int visitTime = setupDuration + wrapupDuration + (p->getNumTests() * perTest);

    p->setWT(currentTime - p->getCheckInTime());
    p->setVT(visitTime);
    p->setStatus(PatientStatus::InTest);

    doc->assignPatient(p, currentTime + visitTime);
    inVisit[branchIdx].insertEnd(p);
}