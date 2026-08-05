// NOTE (Member 4 / Hassan):
// KNOWN BUG: WriteOutput() takes totalRegular and escalatedCount but never
// passes them to stats.writeStats(), so "Auto-escalated" always prints 0.
// Clinic computes both correctly (verified: 3 escalated / 5 regular on an
// AutoE=8 run). Needs fixing in Statistics::writeStats().
//
// LoadData() calls into Clinic via loadUtilities(), setBranches(), addEvent().
#pragma once
#include <string>
#include "../DataStructures/LinkedList.h"

class Clinic;
class Patient;
class Branch;

class FileManager {
private:
    static void mergeSort(Patient** arr, int left, int right);
    static void merge(Patient** arr, int left, int mid, int right);
    static int comparePatients(Patient* a, Patient* b);

public:
    FileManager();

    bool LoadData(const std::string& filepath, Clinic& clinic);
    void WriteOutput(const std::string& filepath,
                     DoublyLinkedList<Patient*>& doneList,
                     Branch* branches, int branchCount,
                     int totalRegular, int escalatedCount);
};
