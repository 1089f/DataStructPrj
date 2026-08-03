#pragma once
#include "Event.h"

class LeaveEvent : public Event {
private:
    int timestamp;
    int patientId;

public:
    LeaveEvent(int ts, int pid);

    int getTimestamp() const override;
    int getPatientId() const;
    void Execute(Clinic& clinic) override;
};
