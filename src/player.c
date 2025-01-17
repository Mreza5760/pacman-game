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
Texture2D pactex[5], deathtex[11];

void pacDef(Player *pac) {
    pactex[0] = LoadTexture("../assets/sprites/pac/pacClosed.png");
    pactex[1] = LoadTexture("../assets/sprites/pac/pacNarrow.png");
    pactex[2] = LoadTexture("../assets/sprites/pac/pacNarrow2.png");
    pactex[3] = LoadTexture("../assets/sprites/pac/pacWide.png");
    pactex[4] = LoadTexture("../assets/sprites/pac/pacWide2.png");
    for (int i = 1; i <= 11; i++)
        deathtex[i-1] = LoadTexture(TextFormat("../assets/sprites/pac/deathAnim/death%d.png", i)); 

    pepperE = 0;
    pac->dir = 0;
    pac->frame = 0; 
    pac->heart = 3;
    pac->point = 0;
    pac->speed = 0.135;
    pac->pos = pac->startPos;
    pac->tex = pactex[pac->frame];
}

void pacUpd(Player *pac) {
    Player temp = *pac;
    
    if (GetTime() - pepperT > 7.0 && pepperE)
        pac->speed -= 0.04, pepperE--;

    if (changeFrame % 8 == 0) {
        pac->frame = (pac->frame+1)%5;
        pac->tex = pactex[pac->frame]; 
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
                gosUpd(&ghost[ty], ty+3);
            } else if (ghost[ty].mode == 1) {
                pac->point += 25;
                ghost[ty].mode = 2;
                ghost[ty].speed = 0.18;

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
            if (pac->heart < 6-Df)
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
            pac->speed += 0.04;
            pepperT = GetTime();
            break;
        case 13:
            cCn--;
            for (int i = 0; i < gosSz; i++) {
                if (ghost[i].mode != 2) {
                    ghost[i].mode = 1;
                    blueT[i] = GetTime();
                }
            }
            break;
    }  
    Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
}

void death() {
    Pacman.dir = 0;
    for (int i = 0; i < 11; i++) {
        Pacman.tex = deathtex[i];

        DrawMap();

        double T = GetTime();
        while (GetTime() - T < 0.08) {
            UpdateMusicStream(difSongs[Df]);
            ResumeMusicStream(difSongs[Df]);
        }
    }
    Pacman.heart--;
    if (!Pacman.heart) {
        Gs = 5;
        Ls = 0;
        addRec(playerName, Pacman.point, Df);
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