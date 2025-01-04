#include "player.h"
#include "map.h"
#include "raylib.h"

Player Pacman;

void pacdef(Player *pac, Vector2 strpos) {
    pac->pos = strpos;
    pac->rad = Cellsz/2;
    pac->helth = 3;
    pac->point = 0;
    pac->speed = 0.3;
}

void pacupd(Player *pac) {
    Player temp = *pac;
    if (IsKeyDown(KEY_RIGHT)) 
        pac->pos.x += pac->speed;
    if (IsKeyDown(KEY_DOWN)) 
        pac->pos.y += pac->speed;
    if (IsKeyDown(KEY_LEFT)) 
        pac->pos.x -= pac->speed;
    if (IsKeyDown(KEY_UP)) 
        pac->pos.y -= pac->speed;

    switch (Mstate[(int)pac->pos.y][(int)pac->pos.x]){
        case 0:
            pac->point += Starp;
            Mstate[(int)pac->pos.y][(int)pac->pos.x] = -1;
            break;
        case 1:
            *pac = temp;
            return;
    }  
    Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
}