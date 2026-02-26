#ifndef EMBEDDED_LOADER_H
#define EMBEDDED_LOADER_H

#include "raylib.h"
#include "embedded_assets.h"

// Game state textures (from main.c)
extern Texture2D los;        // gameover.png
extern Texture2D wel;        // pacmantext.png
extern Font fontM;           // setbackt.ttf
extern Music musicM;         // s3.mp3

// Music array (from map.c)
extern Music difSongs[3];    // s0.mp3, s1.mp3, s2.mp3

// Item textures (from map.c)
extern Texture2D Apple, Heart, Cherry, Pepper, Mushroom;

// Ghost textures (from ghost.c)
extern Texture2D gostex[9][9];  // [ghost type][frame]

// Pacman textures (from player.h/c)
extern Texture2D pactex[5];      // pacman animation frames
extern Texture2D deathtex[11];    // death animation frames

// Rank.txt content (from record.c)
extern char* rankContent;
extern int rankSize;

// Load/unload functions
void LoadAllEmbeddedAssets(void);
void UnloadAllEmbeddedAssets(void);

#endif