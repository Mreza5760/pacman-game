#include "map.h"
#include "menu.h"
#include <time.h>
#include <stdio.h>
#include "record.h"
#include "raylib.h"
#include "embedded_loader.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
#endif

int rankSz[3];
person List[3][12];

//=============================================================================
// PLATFORM-SPECIFIC WRITABLE PATH
//=============================================================================
static const char* GetRankFilePath() {
    static char path[512];
    
#ifdef _WIN32
    const char* appData = getenv("APPDATA");
    if (appData) {
        snprintf(path, sizeof(path), "%s\\Pacman\\rank.txt", appData);
        char dir[512];
        snprintf(dir, sizeof(dir), "%s\\Pacman", appData);
        mkdir(dir); // ignore failure (directory may already exist)
    } else {
        snprintf(path, sizeof(path), "rank.txt");
    }
#elif defined(__APPLE__)
    const char* home = getenv("HOME");
    if (home) {
        snprintf(path, sizeof(path), "%s/Library/Application Support/Pacman/rank.txt", home);
        char dir[512];
        snprintf(dir, sizeof(dir), "%s/Library/Application Support/Pacman", home);
        mkdir(dir, 0755);
    } else {
        snprintf(path, sizeof(path), "rank.txt");
    }
#else
    const char* home = getenv("HOME");
    if (home) {
        snprintf(path, sizeof(path), "%s/.local/share/pacman/rank.txt", home);
        char dir[512];
        snprintf(dir, sizeof(dir), "%s/.local/share/pacman", home);
        mkdir(dir, 0755);
    } else {
        snprintf(path, sizeof(path), "rank.txt");
    }
#endif
    
    return path;
}

//=============================================================================
// PARSE EMBEDDED RANK.TXT
//=============================================================================
static void LoadEmbeddedDefaults() {
    if (rankContent && rankSize > 0) {
        char* buffer = (char*)malloc(rankSize + 1);
        if (!buffer) return;
        memcpy(buffer, rankContent, rankSize);
        buffer[rankSize] = '\0';
        
        char* line = buffer;
        char* next;
        
        for (int j = 0; j < 3; j++) {
            rankSz[j] = atoi(line);
            next = strchr(line, '\n');
            if (!next) break;
            line = next + 1;
            
            for (int i = 0; i < rankSz[j]; i++) {
                // Name
                next = strchr(line, '\n');
                if (!next) break;
                int len = next - line;
                if (len >= (int)sizeof(List[j][i].name))
                    len = sizeof(List[j][i].name) - 1;
                strncpy(List[j][i].name, line, len);
                List[j][i].name[len] = '\0';
                line = next + 1;
                
                // Score
                List[j][i].score = atoi(line);
                next = strchr(line, '\n');
                if (!next) break;
                line = next + 1;
                
                // Time
                List[j][i].timeP = atoll(line);
                next = strchr(line, '\n');
                if (!next) break;
                line = next + 1;
            }
        }
        
        free(buffer);
    } else {
        for (int j = 0; j < 3; j++) {
            rankSz[j] = 0;
        }
    }
}

//=============================================================================
// PUBLIC FUNCTIONS
//=============================================================================

void readList() {
    const char* path = GetRankFilePath();
    FILE* file = fopen(path, "r");
    
    if (file) {
        for (int j = 0; j < 3; j++) {
            if (fscanf(file, "%d\n", &rankSz[j]) != 1) {
                rankSz[j] = 0;
                break;
            }
            for (int i = 0; i < rankSz[j]; i++) {
                if (!fgets(List[j][i].name, sizeof(List[j][i].name), file)) break;
                List[j][i].name[strcspn(List[j][i].name, "\n")] = '\0';
                if (fscanf(file, "%d\n%lld\n", &List[j][i].score, &List[j][i].timeP) != 2) break;
            }
        }
        fclose(file);
    } else {
        LoadEmbeddedDefaults();
    }
}

void addRec(char name[12], int score, int def) {
    person temp;
    strcpy(temp.name, name);
    temp.score = score;
    temp.timeP = time(0);
    
    int pos = rankSz[def];
    for (int i = 0; i < rankSz[def]; i++) {
        if (score > List[def][i].score) {
            pos = i;
            break;
        }
    }
    
    if (pos < rankSz[def]) {
        for (int i = rankSz[def]; i > pos; i--) {
            List[def][i] = List[def][i-1];
        }
    }
    
    List[def][pos] = temp;
    if (rankSz[def] < 10) rankSz[def]++;
    
    updRec(); // save immediately
}

void updRec() {
    const char* path = GetRankFilePath();
    FILE* file = fopen(path, "w");
    if (!file) return;
    
    for (int j = 0; j < 3; j++) {
        fprintf(file, "%d\n", rankSz[j]);
        for (int i = 0; i < rankSz[j]; i++) {
            fprintf(file, "%s\n%d\n%lld\n", List[j][i].name, List[j][i].score, List[j][i].timeP);
        }
    }
    fclose(file);
}

void delRec() {
    for (int j = 0; j < 3; j++) {
        rankSz[j] = 0;
    }
    const char* path = GetRankFilePath();
    remove(path);
}

void drawRec() {
    BeginDrawing();
    ClearBackground(BLACK);
    char* mod[] = {"Easy", "Normal", "Hard"};

    int x = MeasureTextEx(fontM, "Scoreboards", 60, 2).x;
    DrawTextEx(fontM, "Scoreboards", (Vector2){((ScW-x)/2)+5, 10}, 60, 2, GOLD);
    
    for (int j = 0; j < 3; j++) {
        x = MeasureTextEx(fontM, mod[j], 50, 2).x;
        DrawTextEx(fontM, mod[j], (Vector2){(370*j)+((370-x)/2)+5, 80}, 50, 2, PURPLE);
        
        for (int i = 0; i < rankSz[j]; i++) {
            const char *str = TextFormat("%s %d", List[j][i].name, List[j][i].score);
            x = MeasureTextEx(fontM, str, 30, 2).x;
            DrawTextEx(fontM, str, (Vector2){(370*j)+((370-x)/2)+5, 150+i*55}, 30, 2, DARKBLUE);

            struct tm *Time = localtime(&List[j][i].timeP);
            Time->tm_mon++;

            str = TextFormat("%d/%02d/%02d %02d:%02d",
                Time->tm_year%100, Time->tm_mon, Time->tm_mday,
                Time->tm_hour, Time->tm_min);
            x = MeasureTextEx(fontM, str, 15, 2).x;
            DrawTextEx(fontM, str, (Vector2){(370*j)+((370-x)/2)+5, 185+i*55}, 15, 2, DARKGRAY);
        }
    }

    EndDrawing();
}