#pragma once
#include "Event.h"

class Leave : public Event {
private:
    int id;

public:
    Leave(int ts, int id);
    void Execute(Clinic& clinic) override;
    int getId() const;
};