#ifndef RECORD_H
#define RECORD_H

typedef struct {
    char name[12];
    int score;
} person;

extern int rankSz[3];
extern person List[3][12];

void readList();
void drawRec();
void updRec();
void delRec();
void addRec(char name[12], int score, int def);

#endif