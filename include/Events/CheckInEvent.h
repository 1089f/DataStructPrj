#pragma once
#include "Event.h"
// Owner (class/shape): Member 2 | Owner (Execute() body): Member 4

class CheckInEvent : public Event {
public:
    // TODO: CheckInEvent(int ts, int patientId, /* type, branch, tests, etc. */);
    int getTimestamp() const override { return 0; /* TODO */ }
    void Execute(Clinic& clinic) override; // TODO: implemented by Member 4
};
