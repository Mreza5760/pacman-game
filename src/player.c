#include "player.h"
#include "map.h"
#include "raylib.h"

void pacdef(Player *pac, Vector2 strpos) {
    pac->pos = strpos;
    pac->pixpos.x = strpos.x*Cellsz+Cellsz/2, pac->pixpos.y = strpos.y*Cellsz+Cellsz/2;
    pac->rad = Cellsz/2;
    pac->helth = 3;
    pac->point = 0;
    pac->speed = 10;
}

void pacupd(Player *pac) {
    if (IsKeyDown(KEY_RIGHT)) 
        pac->pixpos.x += pac->speed;
    if (IsKeyDown(KEY_DOWN)) 
        pac->pixpos.y += pac->speed;
    if (IsKeyDown(KEY_LEFT)) 
        pac->pixpos.x -= pac->speed;
    if (IsKeyDown(KEY_UP)) 
        pac->pixpos.y -= pac->speed;

    Vector2 temp = {(int)((pac->pixpos.x-Cellsz/2)/Cellsz), (int)((pac->pixpos.y-Cellsz/2)/Cellsz)};
    switch (Mstate[(int)temp.y][(int)temp.x]){
        case 0:
            pac->point += Starp;
            Mstate[(int)temp.y][(int)temp.x] = -1;
            break;
        case 1:
            pac->pixpos.x = pac->pos.x*Cellsz + Cellsz/2;
            pac->pixpos.y = pac->pos.y*Cellsz + Cellsz/2;
            return;
    }  
    Mstate[(int)pac->pos.y][(int)pac->pos.x] = -1; 
    Mstate[(int)temp.y][(int)temp.x] = 2;
    pac->pos = temp;
}