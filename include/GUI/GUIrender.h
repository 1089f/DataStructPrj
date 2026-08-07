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

    void DrawStatsStrip(int x, int y);
    void DrawWaitingQueues(int panelX, int panelY, int panelH);
    void DrawPlaybackControls(int y);

private:
    Clinic& clinic;
    bool paused;
    int speedLvl;
    float fTimer;
    bool simFinished;

    int getTotalWaitE() const;
    int getTotalWaitR() const;
    int getTotalInVisit() const;
    bool btnClicked(int bx, int by, int bw, int bh) const;
};
