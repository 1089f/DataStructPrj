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

    cout << "LoadData OK - CP1 build passes.\n";

    GUIRenderer gui(clinic);
    gui.Init();
    gui.Run();
    gui.Shutdown();

    return 0;
}
