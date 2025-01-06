#include "ghost.h"
#include "map.h"
#include "raylib.h"

Ghost Blinky;

void blidef(Ghost *bli, Vector2 strpos) {
    bli->pos = strpos;
    bli->speed = 0.2;
    bli->beh = -1;
    bli->tex = LoadTexture("../assets/sprites/blinky.png");
}

// void pacupd(Player *pac) {
//     Player temp = *pac;
    
//     if (changeFrame % 7 == 0) {
//         UnloadTexture(pac->tex);
//         pac->frame = (pac->frame+1)%5;
//         pac->tex = LoadTexture(pactex[pac->frame]); 
//     }
//     changeFrame++;
    
//     if (IsKeyDown(KEY_RIGHT)) 
//         pac->pos.x += pac->speed, pac->dir = 0;
//     if (IsKeyDown(KEY_DOWN)) 
//         pac->pos.y += pac->speed, pac->dir = 1;
//     if (IsKeyDown(KEY_LEFT)) 
//         pac->pos.x -= pac->speed, pac->dir = 2;
//     if (IsKeyDown(KEY_UP)) 
//         pac->pos.y -= pac->speed, pac->dir = 3;

//     switch (Mstate[(int)pac->pos.y][(int)pac->pos.x]){
//         case 0:
//             pac->point += Starp;
//             Mstate[(int)pac->pos.y][(int)pac->pos.x] = -1;
//             break;
//         case 1:
//             *pac = temp;
//             return;
//     }  
//     Mstate[(int)temp.pos.y][(int)temp.pos.x] = -1; 
//     Mstate[(int)pac->pos.y][(int)pac->pos.x] = 2;
// }