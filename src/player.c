#include "player.h"
#include "map.h"
#include "raylib.h"

Player Pacman;
int changeFrame = 0;

const char *pactex[5] = {
    "../assets/sprites/pac/pacClosed.png",
    "../assets/sprites/pac/pacNarrow.png",
    "../assets/sprites/pac/pacNarrow2.png", 
    "../assets/sprites/pac/pacWide.png",
    "../assets/sprites/pac/pacWide2.png"
};

void pacDef(Player *pac, Vector2 strpos) {
    pac->pos = strpos;
    pac->heart = 3;
    pac->point = 0;
    pac->speed = 0.25;
    pac->dir = 0;
    pac->frame = 0;
    pac->tex = LoadTexture(pactex[pac->frame]);
}

void pacUpd(Player *pac) {
    Player temp = *pac;
    
    if (changeFrame % 15 == 0) {
        UnloadTexture(pac->tex);
        pac->frame = (pac->frame+1)%5;
        pac->tex = LoadTexture(pactex[pac->frame]); 
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
            pac->point += Starp;
            Mstate[(int)pac->pos.y][(int)pac->pos.x] = -1;
            break;
        case 1:
            *pac = temp;
            return;
        case 3:
            pac->heart--;
            // if (!pac->heart)
            break;
    }  
    Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
}