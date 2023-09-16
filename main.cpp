#include<iostream>
#include<easyx.h>
#include<conio.h>
#include<random>
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAX_SNAKE 100
using namespace std;
enum Dir {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake {
	int num;
	int dir;
	int score;
	int size;
	POINT coor[MAX_SNAKE];
}snake;
struct Food {
	POINT fd;
	int flag;
	DWORD color;
}food;
void Gameinit() {
	snake.num = 3;
	snake.size = 10;
	snake.score = 0;
	snake.dir = RIGHT;
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[1].x = snake.size;
	snake.coor[1].y = 0;
	snake.coor[0].x = 2 * snake.size;
	snake.coor[0].y = 0;
	food.fd.x = rand()%(WIN_WIDTH / 10) * 10;
	food.fd.y = rand() % (WIN_HEIGHT / 10) * 10;
	food.flag = 1;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
}
void Gamedrow() {
	setbkcolor(RGB(100, 250, 212));
	cleardevice();
	setfillcolor(RGB(20, 50, 70));
	for (int i = 0; i < snake.num; i++) {
		setlinecolor(BLACK);
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
	}
	if (food.flag == 1) {
		setfillcolor(food.color);
		fillellipse(food.fd.x, food.fd.y, food.fd.x+10,food.fd.y+10);
	}
}
void snakemove() {
	for (int i = snake.num - 1; i > 0; i--) {
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch (snake.dir) {
	case UP:
		snake.coor[0].y -= snake.size;
		if (snake.coor[0].y <= 0) {
			snake.coor[0].y = WIN_HEIGHT;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.size;
		if (snake.coor[0].y >= WIN_HEIGHT) {
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.size;
		if (snake.coor[0].x <= 0) {
			snake.coor[0].x = WIN_WIDTH;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.size;
		if (snake.coor[0].x >= WIN_WIDTH) {
			snake.coor[0].x = 0;
		}
		break;
	default:
		break;
	}
}
void Keycontrol() {
	if (GetAsyncKeyState(VK_UP)&&snake.dir!=DOWN) {
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN)&&snake.dir!=UP) {
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT)&&snake.dir!=RIGHT) {
		snake.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT)&&snake.dir!=LEFT) {
		snake.dir = RIGHT;
	}
}
void eatfood() {
	if (snake.coor[0].x == food.fd.x && snake.coor[0].y == food.fd.y && food.flag == 1) {
		snake.num++;
		snake.score += 10;
		food.flag = 0;
	}
	if (food.flag == 0) {
		food.fd.x = rand() % (WIN_WIDTH / 10) * 10;
		food.fd.y = rand() % (WIN_HEIGHT / 10) * 10;
		food.flag = 1;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
void self() {
	for (int i = 4; i < snake.num; i++) {
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y) {
			cout<< "ÓÎÏ·½áÊø" << endl;
			exit(666);
		}
	}
}
int main() {
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	Gameinit();
	while (1) {
		snakemove();
		Gamedrow();
		eatfood();
		Keycontrol();
		self();
		Sleep(100);
	}
	closegraph();
	return 0;
}