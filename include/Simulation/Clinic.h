#pragma once
#include "../DataStructures/Queue.h"
#include "../DataStructures/PriorityQueue.h"
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/LookupTable.h"

class Branch;
class Event;
class Patient;
class Doctor;

enum class SimulationMode { Interactive, Silent };

class Clinic {
public:
    
    Clinic()
        : branches(nullptr), numBranches(0),
        waitingEmergency(nullptr), waitingRegular(nullptr), inVisit(nullptr),
        currentTime(0),
        setupDuration(0), wrapupDuration(0),
        seniorPerTestDuration(0), juniorPerTestDuration(0),
        autoEscalationLimit(0),
        totalRegularPatients(0), escalatedCount(0),
mode(SimulationMode::Silent), distanceTable(nullptr), transferMode(false), transferredCount(0)
    {
    }
    int getTransferredCount() const { return transferredCount; }
    ~Clinic();
    
    void loadUtilities(int setup, int wrapup, int seniorPerTest,
        int juniorPerTest, int autoE);

    void setBranches(Branch* branchArray, int count);

    void addEvent(Event* e);

    void run();                         
    void handleCheckIn(Patient* p);
    void handleLeave(int patientId);
    void handleEscalate(int patientId);

    void setMode(SimulationMode m) { mode = m; }
    SimulationMode getMode() const { return mode; }
    void promptModeSelection();
    void printSnapshot() const;

    static const int WAIT_WEIGHT = 2;
    static const int TEST_WEIGHT = 1;
    static double calculatePriority(int checkInTime, int currentTime, int numTests);
    DoublyLinkedList<Patient*>& getDonePatients() { return donePatients; }
    Branch* getBranches() { return branches; }
    int getNumBranches() const { return numBranches; }
    int getTotalRegular() const { return totalRegularPatients; }
    int getEscalatedCount() const { return escalatedCount; }
    //Done by Omar :
    // added some getters 2 be used in GUI w kda 
    int getCurrentTime() const { return currentTime; }
    const DoublyLinkedList<Patient*>* getWaitingEmergency() const { return waitingEmergency; }
    const PriorityQueue<Patient*>* getWaitingRegular() const { return waitingRegular; }
    const DoublyLinkedList<Patient*>* getInVisit() const { return inVisit; }

    bool stepOnce(); //added by Omar 
    // used to slow down the run so it can work fine with the GUI (tick by tick)
    void setDistanceTable(int** table, int count);
    static const int TRANSFER_MARGIN = 5;
private:
    
    Branch* branches;
    int numBranches;
    Queue<Event*> eventQueue;
    LookupTable<Patient*> patientLookup;
    DoublyLinkedList<Patient*>* waitingEmergency; 
    PriorityQueue<Patient*>* waitingRegular;       
    DoublyLinkedList<Patient*>* inVisit;           
    DoublyLinkedList<Patient*> donePatients;
    int currentTime;
    int setupDuration;
    int wrapupDuration;
    int seniorPerTestDuration;
    int juniorPerTestDuration;
    int autoEscalationLimit;
    int totalRegularPatients;
    int escalatedCount;
    SimulationMode mode;
    bool anyPatientsWaiting() const;
    bool anyPatientsInVisit() const;
    Doctor* findDoctor(int branchIdx, bool preferSenior);
    void startVisit(Patient* p, Doctor* doc, int branchIdx);
    int** distanceTable;
    bool transferMode;
    int findNearestBranch(int fromBranch, bool preferSenior);
    bool tryTransfer(Patient* p, int fromBranch);
    int transferredCount;
};