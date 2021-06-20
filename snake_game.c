#include "snake_game.h"

void gotoXY(int x, int y) {
	COORD cur;
	
	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void drawBackground() {
	setColor(WHITE);
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (i == 0 || i == MAP_SIZE - 1) {
				printf("бр");
			}
			else if (j == 0 || j == MAP_SIZE - 1) {
				printf("бр");
			}
			else {
				printf("  ");
			}
		}

		printf("\n");
	}
}

void sizeUp() {


	size++;
}

void printSnake(Position position, char isRemove) {
	gotoXY(position.x, position.y);
	setColor(GREEN);

	if (isRemove) {
		printf("  ");
	} else {
		printf("бр");
	}
}

void initSnake() {
	for (int i = 0; i < 4; i++) {
		positions[size] = (Position){ 16 - (i * 2), 8, RIGHT };
		printSnake(positions[size], 0);
		size++;
	}
}

void moveSnake() {
	for (int i = 0; i < size; i++) {
		Position position = positions[i];

		setPositionDegree(&position);

		if (!isWallCrash(position.x, position.y)) {
			printSnake(positions[i], 1);
			printSnake(position, 0);
			positions[i] = position;
		}
		else {
			break;
			//exit(1);
		}
	}

	for (int i = size - 1; i > 0; i--) {
		previousDegree(i, i - 1);
	}
}

char isWallCrash(int x, int y) {
	return wallX(x) || wallY(y);
}

char wallX(int x) {
	if (0 < x && x < MAP_SIZE * 2 - 2) {
		return 0;
	}
	else {
		return 1;
	}
}

char wallY(int y) {
	if (0 < y && y < MAP_SIZE - 1) {
		return 0;
	}
	else {
		return 1;
	}
}

void setPositionDegree(Position* position) {
	switch (position->degree)
	{
	case UP:
		position->y--;
		break;
	case DOWN:
		position->y++;
		break;
	case LEFT:
		position->x -= 2;
		break;
	case RIGHT:
		position->x += 2;
		break;
	}
}

void setColor(int color) {
	SetConsoleTextAttribute(COUT, color);
}

void previousDegree(int cur, int pre) {
	if (positions[cur].degree != positions[pre].degree) {
		positions[cur].degree = positions[pre].degree;
	}
}