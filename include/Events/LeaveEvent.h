#pragma once
#include "Event.h"
// Owner (class/shape): Member 2 | Owner (Execute() body): Member 4

class LeaveEvent : public Event {
public:
    // TODO: LeaveEvent(int ts, int patientId);
    int getTimestamp() const override { return 0; /* TODO */ }
    void Execute(Clinic& clinic) override; // TODO: implemented by Member 4
};
