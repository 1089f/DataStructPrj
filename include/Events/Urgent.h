#pragma once
#include "Event.h"

class Urgent : public Event {
private:
    int id;

public:
    Urgent(int ts, int id);
    void Execute() override;
    int getId() const;
};