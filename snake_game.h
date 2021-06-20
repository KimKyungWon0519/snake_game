#ifndef __SNAMKE_GAME__
#define __SNAMKE_GAME__

#include <stdio.h>
#include <Windows.h>

#define MAP_SIZE 18
#define SNMAKE_LEN 324
#define COUT GetStdHandle(STD_OUTPUT_HANDLE)

#define YELLOW 6
#define GREEN 2
#define WHITE 7

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

Position positions[SNMAKE_LEN];
int size;

void gotoXY(int, int);
void drawBackground();
void sizeUp();
void printSnake(Position, char);
void initSnake();
void moveSnake();
char isWallCrash(int, int);
char wallY(int);
char wallX(int);
void setPositionDegree(Position*);
void setColor(int);
void previousDegree(int, int);

#endif // !__SNAMKE_GAME__
