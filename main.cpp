#include <iostream>
#include "include/Simulation/Clinic.h"
#include "include/IO/FileManager.h"
#include "include/GUI/GUIrender.h"
using namespace std;

int main() {
    std::string inputFile = "tests/sample_inputs/test4.txt";

    Clinic clinic;
    FileManager fm;

    if (!fm.LoadData(inputFile, clinic)) {
        std::cerr << "Failed to load input file.\n";
        return 1;
    }

    GUIRenderer gui(clinic);
    gui.Init();
    gui.Run();
    gui.Shutdown();

    clinic.run();

    fm.WriteOutput("output.txt", clinic.getDonePatients(),
        clinic.getBranches(), clinic.getNumBranches(),
        clinic.getTotalRegular(), clinic.getEscalatedCount());

    return 0;
}
