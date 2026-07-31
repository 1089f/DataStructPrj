#pragma once
// Owner: Member 2 (System Entities & Events)

enum class DoctorSpecialization { Senior, Junior };

class Doctor {
public:
    Doctor() {}
    // TODO: Doctor(int branch, DoctorSpecialization spec, int shiftStart, int breakAfter, int breakDuration);

    // TODO getters/setters for:
    // int branch
    // DoctorSpecialization specialization
    // int shiftStart
    // int breakAfter       (number of patients before a break)
    // int breakDuration
    // int patientsSeenSinceBreak
    // bool onBreak / breakEndsAt
    // Patient* currentPatient   // set ONLY by Scheduler (Member 4)

    // TODO: bool isAvailable(int currentTime) const;
};
