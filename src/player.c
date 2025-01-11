#include "map.h"
#include "menu.h"
#include <time.h>
#include "ghost.h"
#include "record.h"
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
    pac->dir = 0;
    pac->frame = 0;
    pac->heart = 3;
    pac->point = 0;
    pac->speed = 0.25;
    pac->pos = pacStartPos;
    pac->tex = LoadTexture(pactex[pac->frame]);
}

void death() {
    Pacman.heart--;
    Pacman.dir = 0;
    for (int i = 0; i < 11; i++) {
        UnloadTexture(Pacman.tex);
        Pacman.tex = LoadTexture(deathtex[i]);

        DrawMap();

        double T = GetTime();
        while (GetTime() - T < 0.08);
    }
    Rage = 0;
    if (!Pacman.heart) {
        Gs = 5;
        Ls = 0;
        addRec(playerName, Pacman.point * (Df+1));
        return;
    }
    Vector2 tempbli = ghost[3].pos, tempink = ghost[4].pos;
    Mstate[(int)tempbli.y][(int)tempbli.x] = ghost[3].beh;
    Mstate[(int)tempink.y][(int)tempink.x] = ghost[4].beh;

    Mstate[(int)Pacman.pos.y][(int)Pacman.pos.x] = -1;
    Pacman.pos = pacStartPos;
    ghost[3].pos = ghost[3].startPos;
    ghost[4].pos = ghost[4].startPos;
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
    else if (IsKeyDown(KEY_DOWN)) 
        pac->pos.y += pac->speed, pac->dir = 1;
    else if (IsKeyDown(KEY_LEFT)) 
        pac->pos.x -= pac->speed, pac->dir = 2;
    else if (IsKeyDown(KEY_UP)) 
        pac->pos.y -= pac->speed, pac->dir = 3;

    switch (Mstate[(int)pac->pos.y][(int)pac->pos.x]){
        case 0:
            pac->point += pointSt;
            break;
        case 1:
        case 3:
            *pac = temp;
            return;
        case 4:
            Rage = 1;
            *pac = temp;
            randTar = pac->pos;
            gosUpd(&ghost[4], pac->pos, 4);
            return;
        case 7:
            pac->heart++;
            break;
        case 8:
            death();
            break;
        case 9:
            pac->speed += 0.08;
            break;
    }  
    Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
}