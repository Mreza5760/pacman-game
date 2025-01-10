#include <stdio.h>
#include "record.h"
#include "raylib.h"
#include <string.h>
#include <stdbool.h>

int rankSz;
person List[12];

void readList() {
    FILE *temp = fopen("../assets/rank.txt", "r");

    fscanf(temp, "%d\n", &rankSz);
    for (int i = 0; i < rankSz; i++) {
        fgets(List[i].name, sizeof(List[i].name), temp);
        List[i].name[strcspn(List[i].name, "\n")] = '\0';
        fscanf(temp, "%d\n", &List[i].score);
    } 

    fclose(temp);
}

void drawRec() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Scoreboard", 200, 50, 50, GOLD);
    for (int i = 0; i < rankSz; i++) 
        DrawText(TextFormat("%d. %s %d", i+1, List[i].name, List[i].score), 100, 150+i*40, 40, GRAY);

    EndDrawing();
}

void addRec(char name[12], int score) {
    person temp;
    strcpy(temp.name, name);
    temp.score = score;
    
    bool f = 0;
    for (int i = 0; i < rankSz; i++) {
        if (score > List[i].score) {
            for (int j = rankSz; j > i; j--)
                List[j] = List[j-1];
            List[i] = temp;
            f = 1;
            rankSz++;
            break;
        }
    }
    
    if (!rankSz || !f) List[rankSz++] = temp;
    if (rankSz > 10) rankSz = 10;
}

void updRec() {
    FILE *temp = fopen("../assets/rank.txt", "w");
    fprintf(temp, "%d\n", rankSz);
    for (int i = 0; i < rankSz; i++)
        fprintf(temp, "%s\n%d\n", List[i].name, List[i].score);
    fclose(temp);
}