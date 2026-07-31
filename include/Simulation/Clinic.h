#pragma once
// Owner: Member 4 (Hassan) - Simulation Engine & Scheduler
// The "conductor": owns branches, the events queue, waiting/in-visit/done
// structures, and the main time-step loop. Drives everything else.

#include "../DataStructures/Queue.h"
#include "../Entities/Branch.h"

class Event;

class Clinic {
public:
    Clinic() {}

    // TODO: void loadUtilities(int setup, int wrapup, int seniorPerTest, int juniorPerTest, int autoE);
    // TODO: void run(); // the main time-step loop (t = 0, 1, 2, ...)

    // Called by Event::Execute() implementations:
    // TODO: void handleCheckIn(/* patient info */);
    // TODO: void handleLeave(int patientId);
    // TODO: void handleEscalate(int patientId);

private:
    // TODO: Branch* branches; int numBranches;
    // TODO: Queue<Event*> events;
    // TODO: per-branch waiting Emergency / waiting Regular / in-visit structures
    // TODO: int currentTime;

    // TODO: void assignDoctors();       // Senior/Junior preference rules
    // TODO: void checkAutoEscalation(); // AutoE threshold check
};
