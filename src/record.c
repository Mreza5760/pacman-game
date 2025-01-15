#include "map.h"
#include "menu.h"
#include <stdio.h>
#include "record.h"
#include "raylib.h"
#include <string.h>
#include <stdbool.h>

int rankSz[3];
person List[3][12];

void readList() {
    FILE *temp = fopen("../assets/rank.txt", "r");

    if (temp == NULL) {
        rankSz[0] = 0;
        rankSz[1] = 0;
        rankSz[2] = 0;
        return;
    }

    for (int j = 0; j < 3; j++) {
        fscanf(temp, "%d\n", rankSz+j);
        for (int i = 0; i < rankSz[j]; i++) {
            fgets(List[j][i].name, sizeof(List[j][i].name), temp);
            List[j][i].name[strcspn(List[j][i].name, "\n")] = '\0';
            fscanf(temp, "%d\n", &List[j][i].score);
        } 
    }

    fclose(temp);
}

void drawRec() {
    BeginDrawing();
    ClearBackground(BLACK);
    char* mod[] = {"Easy", "Normal", "Hard"};

    int x = MeasureTextEx(fontM, "Scoreboards", 60, 2).x;
    DrawTextEx(fontM, "Scoreboards", (Vector2){(ScW-x)/2, 30}, 60, 2, GOLD);  
    for (int j = 0; j < 3; j++) { // 370
        x = MeasureTextEx(fontM, mod[j], 50, 2).x;
        DrawTextEx(fontM, mod[j], (Vector2){(370*j)+((370-x)/2)+5, 130}, 50, 2, PURPLE); 
        for (int i = 0; i < rankSz[j]; i++)  {
            const char *str = TextFormat("%s %d", List[j][i].name, List[j][i].score);
            x = MeasureTextEx(fontM, str, 32, 2).x;
            DrawTextEx(fontM, str, (Vector2){(370*j)+((370-x)/2)+5, 220+i*45}, 32, 2, DARKGRAY);
        }
    }

    EndDrawing();
}

void addRec(char name[12], int score, int def) {
    person temp;
    strcpy(temp.name, name);
    temp.score = score;
    
    bool f = 0;
    for (int i = 0; i < rankSz[def]; i++) {
        if (score > List[def][i].score) {
            for (int j = rankSz[def]; j > i; j--)
                List[def][j] = List[def][j-1];
            List[def][i] = temp;
            f = 1;
            rankSz[def]++;
            break;
        }
    }
    
    if (!rankSz[def] || !f) List[def][rankSz[def]++] = temp;
    if (rankSz[def] > 10) rankSz[def] = 10;
}

void updRec() {
    FILE *temp = fopen("../assets/rank.txt", "w");

    for (int j = 0; j < 3; j++) {
        fprintf(temp, "%d\n", rankSz[j]);
        for (int i = 0; i < rankSz[j]; i++)
            fprintf(temp, "%s\n%d\n", List[j][i].name, List[j][i].score);
    }
    fclose(temp);
}

void delRec() {
    rankSz[0] = 0;
    rankSz[1] = 0;
    rankSz[2] = 0;
}