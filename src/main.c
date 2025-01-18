#include "map.h"
#include "menu.h"
#include "draw.h"
#include "ghost.h"
#include "raylib.h"
#include "player.h"
#include "record.h"
#include <stdlib.h>
#include <stdbool.h>

int main() {
    InitWindow(ScW, ScH, "Pacman");
    InitAudioDevice();
    SetTargetFPS(120);
    
    bool Fexit = 0;
    Gs = -1, Ms = 0, Df = 1, Ls = 0, nameSz = 0;
    los =  LoadTexture("../assets/gameState/gameover.png");
    wel = LoadTexture("../assets/gameState/pacmantext.png");
    fontM = LoadFontEx("../assets/fonts/setbackt.ttf", 64, NULL, 0);
    musicM = LoadMusicStream("../assets/sounds/Tsukasa Saitoh - Elden Ring.mp3");
    texIn();
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
    UnloadFont(fontM);
    UnloadTexture(los);
    UnloadTexture(wel);
    UnloadTexture(Heart);
    UnloadTexture(Apple);
    UnloadTexture(Cherry);
    UnloadTexture(Pepper);
    UnloadTexture(Mushroom);
    UnloadTexture(Pacman.tex);
    UnloadMusicStream(musicM);
    for (int i = 0; i < 3; i++)
        UnloadMusicStream(difSongs[i]);
    for (int i = 0; i < 5; i++)
        UnloadTexture(pactex[i]);
    for (int i = 0; i < 11; i++)
        UnloadTexture(deathtex[i]);
    for (int i = 0; i < 9; i++) {
        UnloadTexture(ghost[i].tex);
        for (int j = 0; j < 9; j++)
            UnloadTexture(gostex[i][j]);
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}