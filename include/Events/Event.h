// NOTE (Member 4 / Hassan):
// Execute() MUST keep the Clinic& parameter. It's how an event reaches the
// clinic when it fires - without it the event has no access to the waiting
// queues or the lookup table, and the simulation does nothing.
// The three subclasses call clinic.handleCheckIn() / handleLeave() /
// handleEscalate(), which already exist in Clinic and are wired up.
#pragma once

class Clinic;

class Event {
protected:
    int timestamp;

public:
    Event(int ts) : timestamp(ts) {}
    virtual ~Event() = default;

    virtual void Execute(Clinic& clinic) = 0;
    int getTimestamp() const { return timestamp; }
};