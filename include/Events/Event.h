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