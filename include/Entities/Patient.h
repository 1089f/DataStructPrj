#pragma once
// Owner: Member 2 (System Entities & Events)
// Pure data holder. No simulation logic here (that lives in Clinic/Scheduler).

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
