#pragma once

class Event {
protected:
    int timestamp;

public:
    Event(int ts) : timestamp(ts) {}
    virtual ~Event() = default;

    virtual void Execute() = 0;
    int getTimestamp() const { return timestamp; }
};