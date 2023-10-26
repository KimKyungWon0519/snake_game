#include "snake_game.h"

Position food = { 0, 0 };

char isInsidePosition(Position);
void removeBlock(Position);
void printBlock(Position, Color);
char isOverlaySnakeAndNewFood(Position);
char isAteFood();
short moveHead();
void moveBody();
short isCrashBody(Position position);
void finishGame();

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
				printf("□");
			}
			else if (j == 0 || j == MAP_SIZE - 1) {
				printf("□");
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
	Position newTail = positions[size - 2];
	
	while (1) {
		Position tempPose = newTail;

		switch (tempPose.degree)
		{
		case UP:
			tempPose.y++;
			break;
		case DOWN:
			tempPose.y--;
			break;
		case LEFT:
			tempPose.x++;
			break;
		case RIGHT:
			tempPose.x--;
			break;
		}

		if (isWallCrash(tempPose.x, tempPose.y) || isCrashBody(tempPose)) {
			newTail.degree++;

			if (newTail.degree > RIGHT) {
				newTail.degree = UP;
			}
		}
		else {
			newTail = tempPose;
			break;
		}
	} 

	positions[size - 1] = newTail;
}

void removeBlock(Position position) {
	gotoXY(position.x * 2, position.y);
	printf("  ");
}

void printBlock(Position position, Color color) {
	gotoXY(position.x * 2, position.y);
	setColor(color);

	printf("□");
}

void initSnake() {
	for (int i = 0; i < 4; i++) {
		positions[size] = (Position){ ((MAP_SIZE - 2) / 2) - i, ((MAP_SIZE - 2) / 2), RIGHT};
		printBlock(positions[size], GREEN);
		size++;
	}
}

short moveHead() {
	Position position = positions[0];

	setPositionDegree(&position);

	if (!isWallCrash(position.x, position.y) && !isCrashBody(position)) {
		removeBlock(position);
		printBlock(position, GREEN);
		positions[0] = position;

		return 1;
	}
	else {
		return 0;
	}
}

void moveBody() {
	for (int i = 1; i < size; i++) {
		Position position = positions[i];

		setPositionDegree(&position);

		removeBlock(positions[i]);
		printBlock(position, GREEN);
		positions[i] = position;
	}
}

void moveSnake() {
	short isMove = moveHead();
	short isCreateFood = 0;


	if (isAteFood()) {
		sizeUp();

		isCreateFood = 1;
	}

	if (isMove) {
		moveBody();

		for (int i = size - 1; i > 0; i--) {
			previousDegree(i, i - 1);
		}
	}
	else {
		// TODO: program exit
	}

	if (size == SNMAKE_LEN) {
		finishGame();
	}

	if (isCreateFood) {
		createFood();
	}
}

char isWallCrash(int x, int y) {
	return wallX(x) || wallY(y);
}

short isCrashBody(Position position) {
	for (int i = 1; i < size; i++) {
		if (position.x == positions[i].x && position.y == positions[i].y) {
			return 1;
		}
	} 

	return 0;
}

char wallX(int x) {
	if (0 < x && x < MAP_SIZE - 1) {
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
		position->x--;
		break;
	case RIGHT:
		position->x++;
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

void createFood() {
	while (1) {
		food.x = rand() % (MAP_SIZE - 2) + 1;
		food.y = rand() % (MAP_SIZE - 2) + 1;
		printBlock(food, YELLOW);
		if (isInsidePosition(food) && !isOverlaySnakeAndNewFood(food)) {
			printBlock(food, RED);
			break;
		}
	}
}

char isInsidePosition(Position position) {
	char isX = 0 < position.x && position.x < (MAP_SIZE - 2) * 2 + 1;
	char isY = 0 < position.y && position.y < MAP_SIZE - 1;

	return isX & isY;
}

char isOverlaySnakeAndNewFood(Position position) {
	char isOverlay = 0;

	for (int i = 0; i < size; i++) {
		Position snakeBlock = positions[i];

		if (position.x == snakeBlock.x && position.y == snakeBlock.y) {
			isOverlay = 1;
			break;
		}
	}

	return isOverlay;
}

char isAteFood() {
	return positions[0].x == food.x & positions[0].y == food.y;
}

void finishGame() {
	gotoXY(0, MAP_SIZE + 2);
	setColor(YELLOW);
	system("pause");
	exit(0);
}