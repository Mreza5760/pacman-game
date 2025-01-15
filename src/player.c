#include "map.h"
#include "draw.h"
#include "menu.h"
#include <time.h>
#include "ghost.h"
#include "record.h"
#include "player.h"
#include "raylib.h"

Player Pacman;
double pepperT;
int changeFrame = 0, pepperE;

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
    pepperE = 0;
    pac->dir = 0;
    pac->frame = 0;
    pac->heart = 3;
    pac->point = 0;
    pac->speed = 0.15;
    pac->pos = pac->startPos;
    pac->tex = LoadTexture(pactex[pac->frame]);
}

void pacUpd(Player *pac) {
    Player temp = *pac;
    
    if (GetTime() - pepperT > 7.0 && pepperE)
        pac->speed -= 0.05, pepperE--;

    if (changeFrame % 8 == 0) {
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

    int ty = Mstate[(int)pac->pos.y][(int)pac->pos.x]-3;
    switch (Mstate[(int)pac->pos.y][(int)pac->pos.x]){
        case 0:
            sCn--;
            pac->point += pointSt;
            break;
        case 1:
            *pac = temp;
            return;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            *pac = temp;
            if (!ghost[ty].mode) {
                Rage[ty] = 1;
                randTar[ty] = pac->pos;
                gosUpd(&ghost[ty], ty+3);
            } else if (ghost[ty].mode == 1) {
                pac->point += 25;
                ghost[ty].mode = 2;
                ghost[ty].speed = 0.2;

                updDes((int)Pacman.pos.x, (int)Pacman.pos.y, 0);
                Vector2 temp = newCell();
                while (desTar[(int)temp.y][(int)temp.x] < 13) 
                    temp = newCell();
                ghost[ty].startPos = temp;

                randCell(ty+3);
                gosUpd(&ghost[ty], ty+3);
            }
            return;
        case 10:
            aCn--;
            if (pac->heart < 5)
                pac->heart++;
            break;
        case 11:
            mCn--;
            Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
            Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
            death();
            break;
        case 12:
            pCn--;
            pepperE++;
            pac->speed += 0.05;
            pepperT = GetTime();
            break;
        case 13:
            cCn--;
            for (int i = 0; i < gosSz; i++) {
                ghost[i].mode = 1;
                blueT[i] = GetTime();
            }
            break;
    }  
    Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
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
    Pacman.heart--;
    if (!Pacman.heart) {
        Gs = 5;
        Ls = 0;
        addRec(playerName, Pacman.point * (Df+1));
        return;
    }

    Vector2 temp = newCell();
    Pacman.startPos = temp;
    Mstate[(int)Pacman.pos.y][(int)Pacman.pos.x] = -1;
    Pacman.pos = Pacman.startPos;
    updDes((int)temp.x, (int)temp.y, 0);

    for (int i = 0; i < gosSz; i++) {
        Rage[i] = 0;
        Mstate[(int)ghost[i].pos.y][(int)ghost[i].pos.x] = ghost[i].beh;
        
        temp = newCell();
        while (desTar[(int)temp.y][(int)temp.x] < 13) 
            temp = newCell();
        ghost[i].startPos = temp;

        ghost[i].beh = Mstate[(int)ghost[i].startPos.y][(int)ghost[i].startPos.x];
        Mstate[(int)ghost[i].startPos.y][(int)ghost[i].startPos.x] = i+3;
        ghost[i].pos = ghost[i].startPos;
        ghost[i].mode = 0;
        ghost[i].speed = 0.05 + Df*0.025;
    }
}