#include <iostream>#include "include/Simulation/Clinic.h"
#include "include/IO/FileManager.h"

int main() {
    std::string inputFile = "tests/sample_inputs/test1.txt";

    Clinic clinic;
    FileManager fm;

    if (!fm.LoadData(inputFile, clinic)) {
        std::cerr << "Failed to load input file.\n";
        return 1;
    }

    std::cout << "LoadData OK - CP1 build passes.\n";

    // CP2: uncomment once Clinic::run() is implemented by Member 4
    // clinic.run();
    // fm.WriteOutput("output.txt", clinic.getDonePatients(),
    //                clinic.getBranches(), clinic.getNumBranches(),
    //                clinic.getTotalRegular(), clinic.getEscalatedCount());

    return 0;
}
