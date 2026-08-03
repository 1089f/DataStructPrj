#pragma once
#include "Event.h"

class Patient;

class CheckInEvent : public Event {
private:
    int timestamp;
    Patient* patient;

public:
    CheckInEvent(int ts, Patient* p);

    int getTimestamp() const override;
    Patient* getPatient() const;
    void Execute(Clinic& clinic) override;
};
