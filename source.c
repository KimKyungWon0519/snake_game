#include <stdio.h>
#include "snake_game.h"

void keyInput();

int main() {
	drawBackground();
	initSnake();

	while (1) {
		keyInput();
		moveSnake();
		Sleep(100);
		//sizeUp(positions[size]);
		//positions[0].degree = UP;
	}
}

void keyInput() {
	if (GetAsyncKeyState('W')) {
		if (positions[0].degree != DOWN) {
			positions[0].degree = UP;
		}
	}
	else if (GetAsyncKeyState('S')) {
		if (positions[0].degree != UP) {
			positions[0].degree = DOWN;
		}
	}
	else if (GetAsyncKeyState('A')) {
		if (positions[0].degree != RIGHT) {
			positions[0].degree = LEFT;
		}
	}
	else if (GetAsyncKeyState('D')) {
		if (positions[0].degree != LEFT) {
			positions[0].degree = RIGHT;
		}
	}
}