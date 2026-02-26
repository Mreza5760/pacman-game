#include "map.h"
#include "menu.h"
#include "draw.h"
#include "ghost.h"
#include "raylib.h"
#include "player.h"
#include "record.h"
#include "embedded_loader.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    InitWindow(ScW, ScH, "Pacman");

    if (icon_png_size > 0) {
        Image iconImg = LoadImageFromMemory(".png", icon_png, icon_png_size);
        if (iconImg.data != NULL) {
            SetWindowIcon(iconImg);
            UnloadImage(iconImg);
            TraceLog(LOG_INFO, "Window icon set successfully");
        }
    }

    InitAudioDevice();
    SetTargetFPS(120);
    
    bool Fexit = 0;
    Gs = -1, Ms = 0, Df = 1, Ls = 0, nameSz = 0;
    
    LoadAllEmbeddedAssets();

    readList();
    randomMap(); 
    PlayMusicStream(musicM);
    while (!WindowShouldClose()) {
        UpdateMusicStream(musicM);
        for (int i = 0; i < 3; i++) UpdateMusicStream(difSongs[i]);
        if (Fexit)
            break;
        switch (Gs) {
            case -1:
                getName(&Gs);
                break;
            case 0:
                ResumeMusicStream(musicM);
                getIn(&Gs, &Ms);
                DrawM(Ms);
                if (Gs && Gs != 2 && Gs != 3 && Gs != 5) PauseMusicStream(musicM);
                break;
            case 1:
                if (IsKeyPressed(KEY_M)) Gs = 0;

                ResumeMusicStream(difSongs[Df]);
                addItem();
                pacUpd(&Pacman);
                for (int i = 0; i < gosSz; i++) {
                    randCell(i+3);
                    gosUpd(&ghost[i], i+3);
                }

                DrawMap();
                if (Gs != 1) {
                    PauseMusicStream(difSongs[Df]);
                    StopMusicStream(musicM);
                    PlayMusicStream(musicM);
                }
                break;
            case 2:
                if (IsKeyPressed(KEY_M)) Gs = 0;
                getDf(&Gs, &Df);
                DrawDf(Df);
                break;
            case 3:
                ResumeMusicStream(musicM);
                drawRec();
                if (IsKeyPressed(KEY_DELETE)) delRec();
                if (IsKeyPressed(KEY_M)) Gs = 0;
                break;
            case 4:
                Fexit = 1;
                break;
            case 5:
                getInLose(&Gs, &Ls);
                DrawLose(Ls);
                break;
            case 6:
                DrawWel(&Gs);
                break;
        }
    }

    updRec();
    UnloadAllEmbeddedAssets();

    CloseAudioDevice();
    CloseWindow();
    return 0;
}