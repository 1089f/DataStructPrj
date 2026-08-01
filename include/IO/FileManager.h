#pragma once
#include <string>
// Owner: Member 3 (File I/O & Statistics)
// Reads the input file, populates Branches/Doctors, builds the Events queue,
// and pre-scans for max patient ID (used to size the LookupTable).

// --- Note from Clinic (Member 4) ---
// Clinic now exposes these loading methods for LoadData() to call once
// parsing is done - exact signatures, already implemented and tested:
//     void loadUtilities(int setup, int wrapup, int seniorPerTest,
//                         int juniorPerTest, int autoE);
//     void setBranches(Branch* branchArray, int count);
//     void addEvent(Event* e);
// Clinic itself never reads the file - LoadData() does all parsing and
// pushes the results in via these three calls.

class Clinic; // forward declaration

class FileManager {
public:
    // TODO: bool LoadData(const std::string& filepath, Clinic& clinic);
};
