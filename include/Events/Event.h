#pragma once
// Owner: Member 2 (System Entities & Events) - class design.
// NOTE (agreed): Execute() bodies are filled in by Member 4 (Scheduler),
// since they call into Clinic's structures. Member 2 owns the declarations.

// --- Note from Clinic (Member 4) --- YA EHAAAAAB
// Confirmed: Execute(Clinic& clinic) signature matches what Clinic.h
// expects - takes a reference, not a pointer. Once Member 4 writes the
// Execute() bodies (CP2), they'll call:
//     clinic.handleCheckIn(Patient* p)
//     clinic.handleLeave(int patientId)
//     clinic.handleEscalate(int patientId)
// These three methods already exist (empty stubs) in Clinic.h/cpp.

class Clinic; // forward declaration, avoids circular include

class Event {
public:
    virtual ~Event() {}
    virtual int getTimestamp() const = 0;
    virtual void Execute(Clinic& clinic) = 0; // pure virtual
};
