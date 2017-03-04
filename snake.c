/*******************************/
/*      Snake                  */
/*      Author: Yu Lin         */
/*******************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 10
#define WIDTH 30

//  using (x, y) to record snake
struct Snake {
	int x;
	int y;
};

struct Snake snake[HEIGHT * WIDTH];// store snake locations
int length;// snake length
int map[HEIGHT][WIDTH];//  game scene
int bx, by;// bonus location (x, y)
int score;// current score
char key;
int level;// current level
int speed;// current speed of the snake

// randomly generate the location of a bonus
void getBonusPosition() {
	int i, flag = 1;
	while (flag) {
		flag = 0;
		bx = (rand() % (HEIGHT - 2)) + 1;
		by = (rand() % (WIDTH - 2)) + 1;

		// make sure that the bonus is not in the snake
		for (i = 0; i < length; ++i) {
			if (bx == snake[i].x && by == snake[i].y) {
				flag = 1;
				break;
			}
		}
	}
}

// the snake is like
// XXXXH ----> (11112)
// 'H' is head, 'X' is body
void initSnake() {
	length = 5;// initial length
	int i, x = 1, y = 1;
	for (i = 0; i < length; ++i) {
		snake[i].x = x;
		snake[i].y = y++;
	}
}

// the map is like
// -1 -1 -1 -1 -1
// -1  0  0  0 -1
// -1  0  0  0 -1
// -1  0  0  0 -1
// -1  0  0  0 -1
// -1  0  0  0 -1
// -1 -1 -1 -1 -1
void initMap() {
	int i, j;
	for (i = 0; i < HEIGHT; ++i) {
		for (j = 0; j < WIDTH; ++j) {
			if (i == 0 || i == HEIGHT - 1) map[i][j] = -1;
			else if (j == 0 || j == WIDTH - 1) map[i][j] = -1;
			else map[i][j] = 0;
		}
	}
}

void setMap() {
	initMap();
	int i;
	for (i = 0; i < length - 1; ++i) {
		map[snake[i].x][snake[i].y] = 1;
	}
	map[snake[length - 1].x][snake[length - 1].y] = 2;
	map[bx][by] = 3;
}

void initGame() {
    srand(time(NULL));
	initSnake();
	getBonusPosition();
	setMap();
	score = 0;
	key = 'd';
	level = 1;
	speed = 200;
}

void printMap() {
	int i, j;
	setMap();
	system("cls");
	for (i = 0; i < HEIGHT; ++i) {
		for (j = 0; j < WIDTH; ++j) {
			if (map[i][j] == -1) printf("%c", '*');// wall
			else if (map[i][j] == 0) printf("%c", ' ');// space
			else if (map[i][j] == 1) printf("%c", 'X');// snake's body
			else if (map[i][j] == 2) printf("%c", 'H');// snake's head
			else if (map[i][j] == 3) printf("%c", '$');// bonus
		}
		printf("\n");
	}
	printf("Level: %d\n", level);
	printf("Score: %d\n", score);
}

// using for moving forward or inscresing the length
void add(int nx, int ny) {
	// get the bonus
	if (nx == bx && ny == by) {
		length++;
		score++;
		getBonusPosition();
		if (score % 5 == 0 && speed > 20){
			speed -= 20;
			level++;
		}
	}
	// otherwise
	else {
		int i;
		for (i = 0; i < length - 1; ++i) {
			snake[i] = snake[i + 1];
		}
	}
	snake[length - 1].x = nx;
	snake[length - 1].y = ny;
}

// changing invalid direction
int canMove() {
	int xTemp, yTemp;
	int flag = 1;
	xTemp = snake[length - 1].x - snake[length - 2].x;
	yTemp = snake[length - 1].y - snake[length - 2].y;
	if (xTemp == 1) {
		if (key == 'w' || key == 'W') {
			// flag = 0;
			key = 's';
		}
	}
	else if (xTemp == -1) {
		if (key == 's' || key == 'S'){
			// flag = 0;
			key = 'w';
		}
	}
	else if (yTemp == 1) {
		if (key == 'a' || key == 'A') {
			// flag = 0;
			key = 'd';
		}
	}
	else if (yTemp == -1) {
		if (key == 'd' || key == 'D') {
			// flag = 0;
			key = 'a';
		}
	}
	return flag;
}

void move() {
	if (canMove()) {
		int x = snake[length - 1].x;
		int y = snake[length - 1].y;
		switch (key) {
			case 'a':
			case 'A':
				add(x, y - 1);
				break;
			case 's':
			case 'S':
				add(x + 1, y);
				break;
			case 'd':
			case 'D':
				add(x, y + 1);
				break;
			case 'w':
			case 'W':
				add(x - 1, y);
				break;
			default:
				break;
		}
	}
}

// check if a player loses the game
int isLose() {
	int flag = 0;
	int x, y, i;
	x = snake[length - 1].x;
	y = snake[length - 1].y;
	if (x * y == 0 || x >= HEIGHT - 1 || y >= WIDTH - 1) {
		flag = 1;
	}
	for (i = 0; i < length - 1; ++i) {
		if (x == snake[i].x && y == snake[i].y) {
			flag = 1;
			break;
		}
	}
	return flag;
}

void restart() {
	initGame();
}

void loop() {
	clock_t start = clock();
	initGame();
	while (1) {
		printMap();
		if (!isLose()) {
			// make sure the snake can move automatically
			if (!kbhit()) {
				while(clock() - start >= speed) {
					move();
					start = clock();
				}
			}
			// changing the direction
			else {
				key = getch();
			}
		}
		else {
		    printf("You Lose!\nPress [Enter] twice to restart!\n");
			key = getch();
			key = getch();
			restart();
			start = clock();
			continue;
		}
	}
}

int main() {
	loop();
	return 0;
}
