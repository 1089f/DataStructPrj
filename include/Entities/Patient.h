#pragma once
// Owner: Member 2 (System Entities & Events)
// Pure data holder. No simulation logic here (that lives in Clinic/Scheduler).
// --- Note from Clinic (Member 4) ---
// Ya Ehab tany Once CP2's handleCheckIn(Patient* p) is implemented, Clinic will call
// getters matching this exact shape to compute priority for Regular
// patients:
//     int checkInTime = p->getCheckInTime();
//     int numTests     = p->getNumTests();
// (fed into Clinic::calculatePriority(checkInTime, currentTime, numTests))
// Also needs: getId() (for LookupTable), getBranch() (to route into the
// right per-branch waiting structure).

enum class PatientType { Regular, Emergency };

class Patient {
public:
    Patient() {}
    // TODO: Patient(int id, PatientType type, int checkInTime, int branch, int numTests);

    // TODO getters/setters for:
    // int id
    // PatientType type
    // int checkInTime
    // int startVisitTime   (set by Scheduler when assigned to a doctor)
    // int finishTime        (set by Scheduler when visit completes)
    // int numTests
    // int branch

    // NOTE: heapIndex is owned/managed ONLY by PriorityQueue (Member 1).
    // Do not read/write it anywhere else.
    // int heapIndex = -1;

    // WT/VT are DERIVED, not stored:
    // WT = startVisitTime - checkInTime
    // VT = finishTime - startVisitTime
    // (computed by whoever needs them, e.g. Scheduler / Statistics)
};
