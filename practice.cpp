#include<iostream>
#include<conio.h>
#include<easyx.h>
#include<graphics.h>
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define _CRT_SECURE_NO_DEPRECATE
#define WIN_HEIGHT 480
#define WIN_WIDTH 640
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
	int size;
	int score;
	int dir;
	POINT coor[MAX_SNAKE];
}snake;
struct Food {
	int flag;
	POINT fd;
	DWORD color;
}food[10];
void initGame() {
	snake.num = 3;
	snake.size = 10;
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[1].x = snake.size;
	snake.coor[1].y = 0;
	snake.coor[0].x = 2 * snake.size;
	snake.coor[0].y = 0;
	snake.score = 0;
	snake.dir = RIGHT;
	for (int i = 0; i < 10; i++) {
		food[i].flag = 1;
		food[i].fd.x = rand() % (WIN_WIDTH / 10) * 10;
		food[i].fd.y = rand() % (WIN_HEIGHT / 10) * 10;
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
void eatfood() {
	for (int i = 0; i < 10; i++) {
		if (snake.coor[0].x == food[i].fd.x && snake.coor[0].y == food[i].fd.y && food[i].flag == 1) {
			snake.score += 10;
			snake.num++;
			food[i].flag = 0;
		}
		if (food[i].flag == 0) {
			food[i].flag = 1;
			food[i].fd.x = rand() % (WIN_WIDTH / 10) * 10;
			food[i].fd.y = rand() % (WIN_HEIGHT / 10) * 10;
			food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		}
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
		if (snake.coor[0].y < 0) {
			snake.coor[0].y = WIN_HEIGHT;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.size;
		if (snake.coor[0].y > WIN_HEIGHT) {
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.size;
		if (snake.coor[0].x < 0) {
			snake.coor[0].x = WIN_WIDTH;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.size;
		if (snake.coor[0].x > WIN_WIDTH) {
			snake.coor[0].x = 0;
		}
		break;
	default:
		break;
	}
}
void GameDrow() {
	setbkcolor(RGB(20, 250, 250));
	cleardevice();
	setlinecolor(BLACK);
	for (int i = 0; i < snake.num; i++) {
		setfillcolor(RGB(10, 55, 49));
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
		if (food[i] .flag == 1&&i<10) {
			setfillcolor(food[i].color);
			fillellipse(food[i].fd.x, food[i].fd.y, food[i].fd.x + 10, food[i].fd.y + 10);
		}
	}
}
void KeyControl() {
	if (GetAsyncKeyState(VK_UP) && snake.dir != DOWN) {
		snake.dir = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && snake.dir != UP) {
		snake.dir = DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) && snake.dir != RIGHT) {
		snake.dir = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && snake.dir != LEFT) {
		snake.dir = RIGHT;
	}
}
void end() {
	for (int i = 4; i < snake.num; i++) {
		if (snake.coor[i].x == snake.coor[0].x && snake.coor[i].y == snake.coor[0].y) {
			exit(666);
		}
	}
}
int main() {
	PlaySound("Alarm02.wav", NULL, SND_ASYNC | SND_LOOP);
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	initGame();
	while (1) {
		snakemove();
		GameDrow();
		eatfood();
		KeyControl();
		end();
		Sleep(100);
	}
	closegraph();
	return 0;
}