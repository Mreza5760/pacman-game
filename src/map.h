#ifndef MAP_H
#define MAP_H

#define Row 19
#define Col 25
#define Cellsz 32

extern const char map[3][Row][Col];
extern Mstate[Row][Col];
extern int Mapnum;

int randomMap();
void DrawMap(int x);

#endif