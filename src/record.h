#ifndef RECORD_H
#define RECORD_H

typedef struct {
    char name[12];
    int score;
} person;

extern int rankSz;
extern person List[12];

void readList();
void drawRec();
void addRec(char name[12], int score);
void updRec();
void delRec();

#endif