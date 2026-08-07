#pragma once
#include "../Simulation/Clinic.h"

class GUIRenderer {
public:
    GUIRenderer(Clinic& clinic);
    void Init();
    void Run();
    void DrawDoctorBox(Doctor* doc, int x, int y);
    void DrawLegend(int y);
    void Shutdown();
private:
    Clinic& clinic;
};