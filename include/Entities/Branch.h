#pragma once
// Owner: Member 2 (System Entities & Events)
// Holds the doctors for one branch. Doctor count is fixed at load time.
// --- Note from Clinic (Member 4) ---
// Ya Ehab Clinic expects FileManager to hand it a fully-built Branch array via:
//     void Clinic::setBranches(Branch* branchArray, int count);
// So: FileManager allocates/populates the Branch array, Clinic just
// stores the pointer - Branch itself doesn't need any special interface
// for Clinic beyond existing normally.
//
// IMPORTANT: if Branch owns a dynamically-allocated Doctor array
// internally, Branch needs a real destructor to free it. Clinic calls
// `delete[] branches;` in its own destructor, which runs each Branch's
// destructor automatically for every element in the array - so Branch's
// cleanup needs to be correct for that to not leak.

class Branch {
public:
    Branch() {}
    // TODO: Branch(int branchNumber, int numDoctors);

    // TODO: Doctor* getDoctors(); // fixed-size array, populated by FileManager
    // TODO: int getDoctorCount() const;
    // TODO: int getBranchNumber() const;
};
