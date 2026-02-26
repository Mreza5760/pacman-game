#include "embedded_loader.h"
#include <stdio.h>

// Define global variables
Texture2D los;
Texture2D wel;
Font fontM;
Music musicM;
Music difSongs[3];
Texture2D Apple, Heart, Cherry, Pepper, Mushroom;
Texture2D gostex[9][9];
Texture2D pactex[5];
Texture2D deathtex[11];
char* rankContent;
int rankSize;

//=============================================================================
// PRIVATE HELPERS
//=============================================================================

static Texture2D LoadPngFromMemory(unsigned char* data, int size) {
    Image img = LoadImageFromMemory(".png", data, size);
    if (!img.data) {
        TraceLog(LOG_WARNING, "Failed to load PNG from memory");
        return (Texture2D){0};
    }
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

//=============================================================================
// PUBLIC INTERFACE
//=============================================================================

void LoadAllEmbeddedAssets(void) {
    printf("Loading embedded assets...\n");
    
    //-------------------------------------------------------------------------
    // Game state textures
    //-------------------------------------------------------------------------
    los = LoadPngFromMemory(gameover_png, gameover_png_size);
    wel = LoadPngFromMemory(pacmantext_png, pacmantext_png_size);
    
    //-------------------------------------------------------------------------
    // Font
    //-------------------------------------------------------------------------
    fontM = LoadFontFromMemory(".ttf", setbackt_ttf, setbackt_ttf_size, 64, NULL, 0);
    
    //-------------------------------------------------------------------------
    // Music
    //-------------------------------------------------------------------------
    musicM = LoadMusicStreamFromMemory(".mp3", s3_mp3, s3_mp3_size);
    difSongs[0] = LoadMusicStreamFromMemory(".mp3", s0_mp3, s0_mp3_size);
    difSongs[1] = LoadMusicStreamFromMemory(".mp3", s1_mp3, s1_mp3_size);
    difSongs[2] = LoadMusicStreamFromMemory(".mp3", s2_mp3, s2_mp3_size);
    
    //-------------------------------------------------------------------------
    // Items
    //-------------------------------------------------------------------------
    Apple = LoadPngFromMemory(apple_png, apple_png_size);
    Heart = LoadPngFromMemory(heart_png, heart_png_size);
    Cherry = LoadPngFromMemory(cherry_png, cherry_png_size);
    Pepper = LoadPngFromMemory(pepper_png, pepper_png_size);
    Mushroom = LoadPngFromMemory(mushroom_png, mushroom_png_size);
    
    //-------------------------------------------------------------------------
    // Ghost textures - gostex[9][9]
    //-------------------------------------------------------------------------
    // Blinky (type 0) - 9 frames
    gostex[0][0] = LoadPngFromMemory(blinky0_png, blinky0_png_size);
    gostex[0][1] = LoadPngFromMemory(blinky1_png, blinky1_png_size);
    gostex[0][2] = LoadPngFromMemory(blinky2_png, blinky2_png_size);
    gostex[0][3] = LoadPngFromMemory(blinky3_png, blinky3_png_size);
    gostex[0][4] = LoadPngFromMemory(blinky4_png, blinky4_png_size);
    gostex[0][5] = LoadPngFromMemory(blinky5_png, blinky5_png_size);
    gostex[0][6] = LoadPngFromMemory(blinky6_png, blinky6_png_size);
    gostex[0][7] = LoadPngFromMemory(blinky7_png, blinky7_png_size);
    gostex[0][8] = LoadPngFromMemory(blinky8_png, blinky8_png_size);
    
    // Clyde (type 1) - 9 frames
    gostex[1][0] = LoadPngFromMemory(clyde0_png, clyde0_png_size);
    gostex[1][1] = LoadPngFromMemory(clyde1_png, clyde1_png_size);
    gostex[1][2] = LoadPngFromMemory(clyde2_png, clyde2_png_size);
    gostex[1][3] = LoadPngFromMemory(clyde3_png, clyde3_png_size);
    gostex[1][4] = LoadPngFromMemory(clyde4_png, clyde4_png_size);
    gostex[1][5] = LoadPngFromMemory(clyde5_png, clyde5_png_size);
    gostex[1][6] = LoadPngFromMemory(clyde6_png, clyde6_png_size);
    gostex[1][7] = LoadPngFromMemory(clyde7_png, clyde7_png_size);
    gostex[1][8] = LoadPngFromMemory(clyde8_png, clyde8_png_size);
    
    // Inky (type 2) - 9 frames
    gostex[2][0] = LoadPngFromMemory(inky0_png, inky0_png_size);
    gostex[2][1] = LoadPngFromMemory(inky1_png, inky1_png_size);
    gostex[2][2] = LoadPngFromMemory(inky2_png, inky2_png_size);
    gostex[2][3] = LoadPngFromMemory(inky3_png, inky3_png_size);
    gostex[2][4] = LoadPngFromMemory(inky4_png, inky4_png_size);
    gostex[2][5] = LoadPngFromMemory(inky5_png, inky5_png_size);
    gostex[2][6] = LoadPngFromMemory(inky6_png, inky6_png_size);
    gostex[2][7] = LoadPngFromMemory(inky7_png, inky7_png_size);
    gostex[2][8] = LoadPngFromMemory(inky8_png, inky8_png_size);
    
    // Pinky (type 3) - 9 frames
    gostex[3][0] = LoadPngFromMemory(pinky0_png, pinky0_png_size);
    gostex[3][1] = LoadPngFromMemory(pinky1_png, pinky1_png_size);
    gostex[3][2] = LoadPngFromMemory(pinky2_png, pinky2_png_size);
    gostex[3][3] = LoadPngFromMemory(pinky3_png, pinky3_png_size);
    gostex[3][4] = LoadPngFromMemory(pinky4_png, pinky4_png_size);
    gostex[3][5] = LoadPngFromMemory(pinky5_png, pinky5_png_size);
    gostex[3][6] = LoadPngFromMemory(pinky6_png, pinky6_png_size);
    gostex[3][7] = LoadPngFromMemory(pinky7_png, pinky7_png_size);
    gostex[3][8] = LoadPngFromMemory(pinky8_png, pinky8_png_size);
    
    // Berrypie (type 4) - 9 frames
    gostex[4][0] = LoadPngFromMemory(berrypie0_png, berrypie0_png_size);
    gostex[4][1] = LoadPngFromMemory(berrypie1_png, berrypie1_png_size);
    gostex[4][2] = LoadPngFromMemory(berrypie2_png, berrypie2_png_size);
    gostex[4][3] = LoadPngFromMemory(berrypie3_png, berrypie3_png_size);
    gostex[4][4] = LoadPngFromMemory(berrypie4_png, berrypie4_png_size);
    gostex[4][5] = LoadPngFromMemory(berrypie5_png, berrypie5_png_size);
    gostex[4][6] = LoadPngFromMemory(berrypie6_png, berrypie6_png_size);
    gostex[4][7] = LoadPngFromMemory(berrypie7_png, berrypie7_png_size);
    gostex[4][8] = LoadPngFromMemory(berrypie8_png, berrypie8_png_size);
    
    // Rocky (type 5) - 9 frames
    gostex[5][0] = LoadPngFromMemory(rocky0_png, rocky0_png_size);
    gostex[5][1] = LoadPngFromMemory(rocky1_png, rocky1_png_size);
    gostex[5][2] = LoadPngFromMemory(rocky2_png, rocky2_png_size);
    gostex[5][3] = LoadPngFromMemory(rocky3_png, rocky3_png_size);
    gostex[5][4] = LoadPngFromMemory(rocky4_png, rocky4_png_size);
    gostex[5][5] = LoadPngFromMemory(rocky5_png, rocky5_png_size);
    gostex[5][6] = LoadPngFromMemory(rocky6_png, rocky6_png_size);
    gostex[5][7] = LoadPngFromMemory(rocky7_png, rocky7_png_size);
    gostex[5][8] = LoadPngFromMemory(rocky8_png, rocky8_png_size);
    
    // Snowwhite (type 6) - 9 frames
    gostex[6][0] = LoadPngFromMemory(snowwhite0_png, snowwhite0_png_size);
    gostex[6][1] = LoadPngFromMemory(snowwhite1_png, snowwhite1_png_size);
    gostex[6][2] = LoadPngFromMemory(snowwhite2_png, snowwhite2_png_size);
    gostex[6][3] = LoadPngFromMemory(snowwhite3_png, snowwhite3_png_size);
    gostex[6][4] = LoadPngFromMemory(snowwhite4_png, snowwhite4_png_size);
    gostex[6][5] = LoadPngFromMemory(snowwhite5_png, snowwhite5_png_size);
    gostex[6][6] = LoadPngFromMemory(snowwhite6_png, snowwhite6_png_size);
    gostex[6][7] = LoadPngFromMemory(snowwhite7_png, snowwhite7_png_size);
    gostex[6][8] = LoadPngFromMemory(snowwhite8_png, snowwhite8_png_size);
    
    // Blue ghost (type 7) - 4 frames
    gostex[7][0] = LoadPngFromMemory(blue0_png, blue0_png_size);
    gostex[7][1] = LoadPngFromMemory(blue1_png, blue1_png_size);
    gostex[7][2] = LoadPngFromMemory(blue2_png, blue2_png_size);
    gostex[7][3] = LoadPngFromMemory(blue3_png, blue3_png_size);
    
    // Eyes (type 8) - 4 frames
    gostex[8][0] = LoadPngFromMemory(eye0_png, eye0_png_size);
    gostex[8][1] = LoadPngFromMemory(eye1_png, eye1_png_size);
    gostex[8][2] = LoadPngFromMemory(eye2_png, eye2_png_size);
    gostex[8][3] = LoadPngFromMemory(eye3_png, eye3_png_size);
    
    //-------------------------------------------------------------------------
    // Pacman textures - pactex[5]
    //-------------------------------------------------------------------------
    pactex[0] = LoadPngFromMemory(pacclosed_png, pacclosed_png_size);
    pactex[1] = LoadPngFromMemory(pacnarrow_png, pacnarrow_png_size);
    pactex[2] = LoadPngFromMemory(pacnarrow2_png, pacnarrow2_png_size);
    pactex[3] = LoadPngFromMemory(pacwide_png, pacwide_png_size);
    pactex[4] = LoadPngFromMemory(pacwide2_png, pacwide2_png_size);
    
    //-------------------------------------------------------------------------
    // Death animation - deathtex[11]
    //-------------------------------------------------------------------------
    deathtex[0] = LoadPngFromMemory(death1_png, death1_png_size);
    deathtex[1] = LoadPngFromMemory(death2_png, death2_png_size);
    deathtex[2] = LoadPngFromMemory(death3_png, death3_png_size);
    deathtex[3] = LoadPngFromMemory(death4_png, death4_png_size);
    deathtex[4] = LoadPngFromMemory(death5_png, death5_png_size);
    deathtex[5] = LoadPngFromMemory(death6_png, death6_png_size);
    deathtex[6] = LoadPngFromMemory(death7_png, death7_png_size);
    deathtex[7] = LoadPngFromMemory(death8_png, death8_png_size);
    deathtex[8] = LoadPngFromMemory(death9_png, death9_png_size);
    deathtex[9] = LoadPngFromMemory(death10_png, death10_png_size);
    deathtex[10] = LoadPngFromMemory(death11_png, death11_png_size);
    
    //-------------------------------------------------------------------------
    // Rank file
    //-------------------------------------------------------------------------
    rankContent = (char*)rank_txt;
    rankSize = rank_txt_size;
    
    printf("All assets loaded successfully!\n");
}

void UnloadAllEmbeddedAssets(void) {
    // Game state
    UnloadTexture(los);
    UnloadTexture(wel);
    UnloadFont(fontM);
    
    // Music
    UnloadMusicStream(musicM);
    for (int i = 0; i < 3; i++) 
        UnloadMusicStream(difSongs[i]);
    
    // Items
    UnloadTexture(Apple);
    UnloadTexture(Heart);
    UnloadTexture(Cherry);
    UnloadTexture(Pepper);
    UnloadTexture(Mushroom);
    
    // Ghosts - gostex[9][9]
    for (int g = 0; g < 9; g++) {
        for (int f = 0; f < 9; f++) {
            if (gostex[g][f].id != 0) 
                UnloadTexture(gostex[g][f]);
        }
    }
    
    // Pacman textures - pactex[5]
    for (int i = 0; i < 5; i++)
        UnloadTexture(pactex[i]);
    
    // Death animation - deathtex[11]
    for (int i = 0; i < 11; i++)
        UnloadTexture(deathtex[i]);
    
    printf("All assets unloaded successfully!\n");
}