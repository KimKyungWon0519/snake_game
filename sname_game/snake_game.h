#ifndef __SNAMKE_GAME__
#define __SNAMKE_GAME__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAP_SIZE 6
#define SNMAKE_LEN (MAP_SIZE - 2) * (MAP_SIZE - 2)
#define COUT GetStdHandle(STD_OUTPUT_HANDLE)

typedef struct _Position {
	int x;
	int y;
	int degree;
} Position;

enum {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

typedef enum _Color {
	YELLOW = 6,
	GREEN = 2,
	WHITE = 7,
	RED = 4
} Color;

Position positions[SNMAKE_LEN];
int size;
Position food;

void gotoXY(int, int);
void drawBackground();
void sizeUp();
void initSnake();
void moveSnake();
char isWallCrash(int, int);
char wallY(int);
char wallX(int);
void setPositionDegree(Position*);
void setColor(int);
void previousDegree(int, int);
void createFood();

#endif // !__SNAMKE_GAME__