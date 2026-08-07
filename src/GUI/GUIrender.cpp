#include "../../include/GUI/GUIrender.h"
#include "../../include/Entities/Doctor.h"
#include "../../include/Entities/Branch.h"
#include <raylib.h>

GUIRenderer::GUIRenderer(Clinic& clinic) : clinic(clinic) {}

Color DrStatusClr(DoctorAvlbl status) {
    if (status == DoctorAvlbl::Available) return GREEN;
    else if (status == DoctorAvlbl::Busy) return ORANGE;
    else if (status == DoctorAvlbl::OnBreak) return LIGHTGRAY;
    else if (status == DoctorAvlbl::OffShift) return RED;
    else { return WHITE; }
}

void GUIRenderer::DrawDoctorBox(Doctor* doc, int x, int y) {
    Color bxClr = DrStatusClr(doc->getAvlbl());
    DrawRectangle(x, y, 200, 80, bxClr);

    if (doc->getAvlbl() == DoctorAvlbl::Busy) {
        Patient* p = doc->getCurrentPatient();
        if (p != nullptr) {
            DrawText(TextFormat("BUSY - Patient: %d\nUntil %d",
                p->getId(), doc->getBusyUntil()), x + 10, y + 10, 16, BLACK);
        }
        else {
            DrawText("BUSY", x + 10, y + 10, 16, BLACK);
        }
    }
    else if (doc->getAvlbl() == DoctorAvlbl::Available) {
        DrawText("FREE", x + 10, y + 10, 16, BLACK);
    }
    else if (doc->getAvlbl() == DoctorAvlbl::OnBreak) {
        DrawText(TextFormat("ON BREAK\nUntil %d", doc->getBreakEndsAt()),
            x + 10, y + 10, 16, BLACK);
    }
    else {
        DrawText("OFF SHIFT", x + 10, y + 10, 16, BLACK);
    }
}

void GUIRenderer::Init() {
    InitWindow(1000, 600, "Clinic Scheduling GUI");
}

void GUIRenderer::DrawLegend(int y) {
    DrawRectangle(10, y, 20, 20, GREEN);
    DrawText("Free", 35, y + 2, 16, BLACK);

    DrawRectangle(150, y, 20, 20, ORANGE);
    DrawText("Busy", 175, y + 2, 16, BLACK);

    DrawRectangle(290, y, 20, 20, LIGHTGRAY);
    DrawText("On Break", 315, y + 2, 16, BLACK);

    DrawRectangle(430, y, 20, 20, RED);
    DrawText("Off Shift", 455, y + 2, 16, BLACK);
}

void GUIRenderer::Run() {
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            clinic.stepOnce();
        }
        DrawText(TextFormat("Waiting Emergency: %d   Waiting Regular: %d   In-Visit: %d   Done: %d",
            0, 0, 0, clinic.getDonePatients().size()), //0,0,0 to be changed by Yousef
            10, 40, 18, BLACK);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawLegend(550);
        DrawText(TextFormat("Current Time: %d", clinic.getCurrentTime()), 10, 10, 20, BLACK);
        for (int b = 0; b < clinic.getNumBranches();b++) {
            Branch* branch = clinic.getBranches() + b;
            for (int d = 0; d < branch->getDocCnt(); d++) {
                Doctor* doc = &branch->getDoc()[d];

                int x = 50 + d * 250;
                int y = 100 + b * 150;

                DrawDoctorBox(doc, x, y);
            }
        }
        EndDrawing();
    }
}

void GUIRenderer::Shutdown() {
    CloseWindow();
}