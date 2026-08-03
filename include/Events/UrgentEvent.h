#pragma once
#include "Event.h"

class UrgentEvent : public Event {
private:
    int timestamp;
    int patientId;

public:
    UrgentEvent(int ts, int pid);

    int getTimestamp() const override;
    int getPatientId() const;
    void Execute(Clinic& clinic) override;
};
