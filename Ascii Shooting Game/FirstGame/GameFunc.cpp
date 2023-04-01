#include "GameFunc.h"
#include <vector>
#include <iostream>
#include <windows.h>

extern bool g_flag_running;

int f_state;  // 0 : stop, 1 : moving leftward, 2 : moving rightward, 3 : moving upward, 4 : moving downward
int m_state; // 0 : in Flight, 1 : Flying

int f_pos_x;
int f_pos_y;
int m_pos_x;
int m_pos_y;

int f_x;
int f_y;

double g_time;


struct Missle {
	int x;
	int y;
	Missle(int x, int y) : x(x), y(y) { isDestroyed = false; }
	bool isDestroyed;
};

std::vector<Missle*> missles;

void InitGame()
{
	g_flag_running = true;

	// 비행기의 위치
	f_state = 0;
	f_pos_x = 15;
	f_pos_y = 17;

	g_time = 0.0;

	// Clear the console screen.
	// 표준출력 화면을 깨끗히 지운다.
	system("cls");
}

void Update()
{
	g_time += 0.03;

	// 비행기의 위치 이동.
	if (f_state == 0) { // stop
		f_x = f_pos_x;
		f_y = f_pos_y;
	}

	if (f_state == 1) { // moving leftward
		f_x -= 1;
	}
	else if (f_state == 2) { // moving rightward
		f_x += 1;
	}
	else if (f_state == 3) { // moving upward
		f_y += 1;
	}
	else if (f_state == 4) { // moving downward
		f_y -= 1;
	}

	for (size_t i = 0; i < missles.size(); i++) {
		if (missles[i]->y > 0 && missles[i]->isDestroyed == false)
			missles[i]->y -= 1;
		else
			missles[i]->isDestroyed = true;
	}

	// 비행기의 위치가 경계에 닿으면 경계에서 멈춘다.  
	if (f_pos_x <= 0) f_pos_x = 0;
	if (f_pos_x >= 29) f_pos_x = 29;
	if (f_pos_y <= 0) f_pos_y = 0;
	if (f_pos_y >= 19) f_pos_y = 19;

}


void Render()
{
	COORD cur;

	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	for (int i = 0; i<20; i++)
	{
		for (int j = 0; j<30; j++)
		{
			std::cout << "_";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Elapsed Time: " << g_time << std::endl;
	std::cout << "Ascii Shooting Game" << std::endl;

	cur.X = f_pos_x;
	cur.Y = f_pos_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);


	if (f_state == 0 || f_state == 1 || f_state == 2 || f_state == 3 || f_state == 4)
	{
		std::cout << "▲";
	}

	for (size_t i = 0; i < missles.size(); i++) {
		if (missles[i]->isDestroyed == false) {
			cur.X = missles[i]->x;
			cur.Y = missles[i]->y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
			std::cout << "†";
		}
	}
}

void HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_LEFT)
			{
				f_state = 1;
				f_pos_x -= 1;
			}

			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				f_state = 2;
				f_pos_x += 1;
			}

			if (event.key.keysym.sym == SDLK_UP)
			{
				f_state = 3;
				f_pos_y -= 1;
			}

			if (event.key.keysym.sym == SDLK_DOWN)
			{
				f_state = 4;
				f_pos_y += 1;
			}


			if (event.key.keysym.sym == SDLK_SPACE)
			{
				missles.push_back(new Missle(f_pos_x, f_pos_y));
			}

			break;

		case SDL_KEYUP:

			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT ||
				event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
			{
				f_state = 0;
			}

			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
			}
			break;

		default:
			break;
		}
	}
}


void ClearGame()
{
}

