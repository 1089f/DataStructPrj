// CheckIn.h
#pragma once
#include "Event.h"
#include "../Entities/Patient.h"

class CheckIn : public Event {
private:
    PatientType type;
    int id;
    int branch;
    int tests;
public:
    CheckIn(int ts, PatientType type, int id, int branch, int tests);

    void Execute(Clinic& clinic) override;
    Patient* createPatient();     
};