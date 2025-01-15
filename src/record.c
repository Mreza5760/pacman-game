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

    for (int j = 0; j < 3; j++) {
        DrawText("Scoreboard", 200+j*400, 50, 50, GOLD);  
        for (int i = 0; i < rankSz[j]; i++) 
            DrawText(TextFormat("%d. %s %d", i+1, List[j][i].name, List[j][i].score), 100+j*400, 150+i*40, 40, GRAY);
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