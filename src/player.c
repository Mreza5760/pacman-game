#include "map.h"
#include "menu.h"
#include <time.h>
#include "ghost.h"
#include "player.h"
#include "raylib.h"

Player Pacman;
Vector2 pacStartPos;
int changeFrame = 0;

const char *pactex[5] = {
    "../assets/sprites/pac/pacClosed.png",
    "../assets/sprites/pac/pacNarrow.png",
    "../assets/sprites/pac/pacNarrow2.png", 
    "../assets/sprites/pac/pacWide.png",
    "../assets/sprites/pac/pacWide2.png"
};

const char *deathtex[11] = {
    "../assets/sprites/pac/deathAnim/death1.png",
    "../assets/sprites/pac/deathAnim/death2.png",
    "../assets/sprites/pac/deathAnim/death3.png",
    "../assets/sprites/pac/deathAnim/death4.png",
    "../assets/sprites/pac/deathAnim/death5.png",
    "../assets/sprites/pac/deathAnim/death6.png",
    "../assets/sprites/pac/deathAnim/death7.png",
    "../assets/sprites/pac/deathAnim/death8.png",
    "../assets/sprites/pac/deathAnim/death9.png",
    "../assets/sprites/pac/deathAnim/death10.png",
    "../assets/sprites/pac/deathAnim/death11.png"
};

void pacDef(Player *pac) {
    pac->pos = pacStartPos;
    pac->heart = 3;
    pac->point = 0;
    pac->speed = 0.25;
    pac->dir = 0;
    pac->frame = 0;
    pac->tex = LoadTexture(pactex[pac->frame]);
}

void death() {
    Pacman.dir = 0;
    for (int i = 0; i < 11; i++) {
        UnloadTexture(Pacman.tex);
        Pacman.tex = LoadTexture(deathtex[i]);

        DrawMap();

        double T = GetTime();
        while (GetTime() - T < 0.08);
    }

    if (!Pacman.heart) {
        Gs = 5;
        Ls = 0;
        return;
    }

    Mstate[(int)Pacman.pos.y][(int)Pacman.pos.x] = -1;
    Pacman.pos = pacStartPos;
    Blinky.pos = bliStartPos;
    Inky.pos = inkStartPos;
}

void pacUpd(Player *pac) {
    Player temp = *pac;
    
    if (changeFrame % 7 == 0) {
        UnloadTexture(pac->tex);
        pac->frame = (pac->frame+1)%5;
        pac->tex = LoadTexture(pactex[pac->frame]); 
        changeFrame = 0;
    }
    changeFrame++;
    
    if (IsKeyDown(KEY_RIGHT)) 
        pac->pos.x += pac->speed, pac->dir = 0;
    if (IsKeyDown(KEY_DOWN)) 
        pac->pos.y += pac->speed, pac->dir = 1;
    if (IsKeyDown(KEY_LEFT)) 
        pac->pos.x -= pac->speed, pac->dir = 2;
    if (IsKeyDown(KEY_UP)) 
        pac->pos.y -= pac->speed, pac->dir = 3;

    switch (Mstate[(int)pac->pos.y][(int)pac->pos.x]){
        case 0:
            pac->point += pointSt;
            Mstate[(int)pac->pos.y][(int)pac->pos.x] = -1;
            break;
        case 1:
        case 3:
        case 4:
            *pac = temp;
            return;
    }  
    Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
}