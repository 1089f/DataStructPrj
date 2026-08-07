#include "../../include/GUI/GUIrender.h"
#include "../../include/Entities/Doctor.h"
#include "../../include/Entities/Branch.h"
#include "../../include/Entities/Patient.h"
#include <raylib.h>

GUIRenderer::GUIRenderer(Clinic& c)
    : clinic(c), paused(true), speedLvl(1), fTimer(0.0f), simFinished(false) {}

Color DrStatusClr(DoctorAvlbl status) {
    if (status == DoctorAvlbl::Available) return GREEN;
    else if (status == DoctorAvlbl::Busy)    return ORANGE;
    else if (status == DoctorAvlbl::OnBreak) return LIGHTGRAY;
    else if (status == DoctorAvlbl::OffShift) return RED;
    else return WHITE;
}

void GUIRenderer::DrawDoctorBox(Doctor* doc, int x, int y) {
    Color bxClr = DrStatusClr(doc->getAvlbl());
    DrawRectangle(x, y, 195, 80, bxClr);
    DrawRectangleLines(x, y, 195, 80, DARKGRAY);

    const char* lvlStr = (doc->getLvl() == DoctorLvl::Senior) ? "[S]" : "[J]";
    DrawText(lvlStr, x + 5, y + 5, 13, DARKGRAY);

    if (doc->getAvlbl() == DoctorAvlbl::Busy) {
        Patient* p = doc->getCurrentPatient();
        if (p != nullptr) {
            DrawText(TextFormat("BUSY", p->getId()), x + 28, y + 5, 14, BLACK);
            DrawText(TextFormat("P#%d  free@%d", p->getId(), doc->getBusyUntil()), x + 5, y + 24, 13, BLACK);
        } else {
            DrawText("BUSY", x + 28, y + 5, 14, BLACK);
        }
    } else if (doc->getAvlbl() == DoctorAvlbl::Available) {
        DrawText("FREE", x + 28, y + 5, 14, BLACK);
    } else if (doc->getAvlbl() == DoctorAvlbl::OnBreak) {
        DrawText("ON BREAK", x + 28, y + 5, 14, BLACK);
        DrawText(TextFormat("until t=%d", doc->getBreakEndsAt()), x + 5, y + 24, 13, BLACK);
    } else {
        DrawText("OFF SHIFT", x + 28, y + 5, 14, BLACK);
        DrawText(TextFormat("starts@%d", doc->getShiftStart()), x + 5, y + 24, 13, BLACK);
    }
}

void GUIRenderer::DrawLegend(int y) {
    DrawRectangle(10, y, 18, 18, GREEN);
    DrawText("Free", 32, y + 1, 14, BLACK);

    DrawRectangle(110, y, 18, 18, ORANGE);
    DrawText("Busy", 132, y + 1, 14, BLACK);

    DrawRectangle(210, y, 18, 18, LIGHTGRAY);
    DrawRectangleLines(210, y, 18, 18, DARKGRAY);
    DrawText("On Break", 232, y + 1, 14, BLACK);

    DrawRectangle(340, y, 18, 18, RED);
    DrawText("Off Shift", 362, y + 1, 14, BLACK);

    DrawRectangle(470, y, 18, 18, (Color){ 220, 50, 50, 255 });
    DrawText("Emergency", 492, y + 1, 14, BLACK);

    DrawRectangle(610, y, 18, 18, (Color){ 65, 120, 210, 255 });
    DrawText("Regular", 632, y + 1, 14, BLACK);

    DrawRectangle(720, y, 18, 18, (Color){ 140, 50, 190, 255 });
    DrawText("In-Visit", 742, y + 1, 14, BLACK);
}

int GUIRenderer::getTotalWaitE() const {
    const DoublyLinkedList<Patient*>* ewq = clinic.getWaitingEmergency();
    int tot = 0;
    for (int b = 0; b < clinic.getNumBranches(); b++)
        tot += ewq[b].size();
    return tot;
}

int GUIRenderer::getTotalWaitR() const {
    const PriorityQueue<Patient*>* rwq = clinic.getWaitingRegular();
    int tot = 0;
    for (int b = 0; b < clinic.getNumBranches(); b++)
        tot += rwq[b].size();
    return tot;
}

int GUIRenderer::getTotalInVisit() const {
    const DoublyLinkedList<Patient*>* iv = clinic.getInVisit();
    int tot = 0;
    for (int b = 0; b < clinic.getNumBranches(); b++)
        tot += iv[b].size();
    return tot;
}

bool GUIRenderer::btnClicked(int bx, int by, int bw, int bh) const {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return false;
    Vector2 m = GetMousePosition();
    return (m.x >= bx && m.x <= bx + bw && m.y >= by && m.y <= by + bh);
}

void GUIRenderer::DrawStatsStrip(int x, int y) {
    int we = getTotalWaitE();
    int wr = getTotalWaitR();
    int iv = getTotalInVisit();
    int dn = clinic.getDonePatients().size();

    DrawText(TextFormat("Emg Waiting: %d", we),  x,       y, 17, (Color){ 200, 30, 30, 255 });
    DrawText(TextFormat("Reg Waiting: %d", wr),  x + 175, y, 17, (Color){ 30, 90, 200, 255 });
    DrawText(TextFormat("In-Visit: %d",   iv),   x + 355, y, 17, (Color){ 120, 40, 175, 255 });
    DrawText(TextFormat("Done: %d",       dn),   x + 490, y, 17, DARKGREEN);
}

void GUIRenderer::DrawWaitingQueues(int panelX, int panelY, int panelH) {
    int col1 = panelX;
    int col2 = panelX + 210;
    int col3 = panelX + 420;

    Color emgClr = { 220, 50,  50,  255 };
    Color regClr = { 65,  120, 210, 255 };
    Color ivClr  = { 140, 50,  190, 255 };

    int maxY = panelY + panelH;

    DrawText("WAITING EMERGENCY", col1, panelY, 16, emgClr);
    int ey = panelY + 22;

    const DoublyLinkedList<Patient*>* ewq = clinic.getWaitingEmergency();
    bool anyE = false;
    for (int b = 0; b < clinic.getNumBranches() && ey < maxY - 8; b++) {
        if (ewq[b].size() == 0) continue;
        DrawText(TextFormat("Br%d:", b + 1), col1, ey, 13, DARKGRAY);
        ey += 17;
        auto* nd = ewq[b].getHead();
        while (nd != nullptr && ey < maxY - 8) {
            Patient* p = nd->data;
            DrawRectangle(col1, ey, 196, 22, emgClr);
            DrawText(TextFormat("P#%d  tests:%d", p->getId(), p->getNumTests()),
                     col1 + 5, ey + 4, 13, WHITE);
            ey += 26;
            nd = nd->next;
            anyE = true;
        }
    }
    if (!anyE)
        DrawText("(none)", col1 + 4, ey, 13, GRAY);

    DrawText("WAITING REGULAR", col2, panelY, 16, regClr);
    int ry = panelY + 22;

    const PriorityQueue<Patient*>* rwq = clinic.getWaitingRegular();
    bool anyR = false;
    for (int b = 0; b < clinic.getNumBranches() && ry < maxY - 8; b++) {
        int sz = rwq[b].size();
        if (sz == 0) continue;
        DrawText(TextFormat("Br%d:", b + 1), col2, ry, 13, DARKGRAY);
        ry += 17;
        for (int i = 0; i < sz && ry < maxY - 8; i++) {
            Patient* p = nullptr;
            if (rwq[b].getAt(i, p) && p != nullptr) {
                DrawRectangle(col2, ry, 196, 22, regClr);
                DrawText(TextFormat("P#%d  tests:%d", p->getId(), p->getNumTests()),
                         col2 + 5, ry + 4, 13, WHITE);
                ry += 26;
                anyR = true;
            }
        }
    }
    if (!anyR)
        DrawText("(none)", col2 + 4, ry, 13, GRAY);

    DrawText("IN-VISIT", col3, panelY, 16, ivClr);
    int iy = panelY + 22;

    const DoublyLinkedList<Patient*>* iv = clinic.getInVisit();
    bool anyIV = false;
    for (int b = 0; b < clinic.getNumBranches() && iy < maxY - 8; b++) {
        if (iv[b].size() == 0) continue;
        DrawText(TextFormat("Br%d:", b + 1), col3, iy, 13, DARKGRAY);
        iy += 17;
        auto* nd = iv[b].getHead();
        while (nd != nullptr && iy < maxY - 8) {
            Patient* p = nd->data;
            DrawRectangle(col3, iy, 185, 22, ivClr);
            DrawText(TextFormat("P#%d  tests:%d", p->getId(), p->getNumTests()),
                     col3 + 5, iy + 4, 13, WHITE);
            iy += 26;
            nd = nd->next;
            anyIV = true;
        }
    }
    if (!anyIV)
        DrawText("(none)", col3 + 4, iy, 13, GRAY);
}

void GUIRenderer::DrawPlaybackControls(int y) {
    Color darkBtn = DARKGRAY;
    Color spdBtn  = { 80, 80, 130, 255 };

    DrawRectangle(10, y, 115, 34, darkBtn);
    DrawText(paused ? "  > PLAY" : "|| PAUSE", 18, y + 9, 16, WHITE);

    DrawRectangle(136, y, 82, 34, darkBtn);
    DrawText("STEP >>", 142, y + 9, 16, WHITE);

    DrawRectangle(228, y, 34, 34, spdBtn);
    DrawText("-", 241, y + 9, 18, WHITE);

    const char* spds[] = { "SLOW", "MED ", "FAST" };
    DrawText(TextFormat("Spd: %s", spds[speedLvl]), 270, y + 9, 16, BLACK);

    DrawRectangle(364, y, 34, 34, spdBtn);
    DrawText("+", 376, y + 9, 18, WHITE);

    if (simFinished)
        DrawText("Simulation complete.", 416, y + 9, 16, DARKGREEN);
    else if (paused)
        DrawText("Paused  (press SPACE to step)", 416, y + 9, 16, MAROON);
    else
        DrawText("Running...", 416, y + 9, 16, DARKBLUE);
}

void GUIRenderer::Init() {
    InitWindow(1280, 750, "Clinic Patient Scheduling - CIE205");
    SetTargetFPS(60);
}

void GUIRenderer::Run() {
    while (!WindowShouldClose()) {
        if (btnClicked(10, 682, 115, 34)) {
            paused = !paused;
            fTimer = 0.0f;
        }
        if (btnClicked(136, 682, 82, 34) || IsKeyPressed(KEY_SPACE)) {
            if (!simFinished)
                simFinished = !clinic.stepOnce();
        }
        if (btnClicked(228, 682, 34, 34) && speedLvl > 0)
            speedLvl--;
        if (btnClicked(364, 682, 34, 34) && speedLvl < 2)
            speedLvl++;

        if (!paused && !simFinished) {
            float delays[] = { 0.75f, 0.35f, 0.1f };
            fTimer += GetFrameTime();
            if (fTimer >= delays[speedLvl]) {
                simFinished = !clinic.stepOnce();
                fTimer = 0.0f;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Clinic Patient Scheduling  |  Timestep: %d",
                 clinic.getCurrentTime()), 10, 8, 20, DARKBLUE);
        DrawStatsStrip(640, 10);

        DrawLine(630, 45, 630, 670, (Color){ 180, 180, 180, 255 });

        for (int b = 0; b < clinic.getNumBranches(); b++) {
            Branch* br = clinic.getBranches() + b;
            DrawText(TextFormat("Branch %d", b + 1), 10, 52 + b * 160, 16, DARKBLUE);
            DrawLine(10, 70 + b * 160, 620, 70 + b * 160, (Color){ 200, 200, 200, 255 });
            for (int d = 0; d < br->getDocCnt(); d++) {
                int bx = 12 + d * 205;
                int by = 75 + b * 160;
                DrawDoctorBox(&br->getDoc()[d], bx, by);
            }
        }

        DrawWaitingQueues(642, 48, 620);
        DrawPlaybackControls(682);
        DrawLegend(724);

        EndDrawing();
    }
}

void GUIRenderer::Shutdown() {
    CloseWindow();
}
