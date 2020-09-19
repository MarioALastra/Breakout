#include "breakout.h"
#include <fstream>
#include <iostream>

enum GameState{MAIN, EDIT, GAME, WIN, LOSE};

static int playerScore = 0;

void Init();
void Update();
void Draw();
void UpdateDraw();

Padel padel;
Ball ball;
Brick* brick[MAX_BRICKS];
Brick rick[MAX_BRICKS] = {};
Texture2D padel_spr;
Texture2D ball_spr;
Texture2D brick_spr;

GameState state = EDIT;



int main()
{
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Breakout");
	SetTargetFPS(60);
	padel_spr = LoadTexture("assets/breakout_padel.png");
	ball_spr = LoadTexture("assets/breakout_ball.png");
	brick_spr = LoadTexture("assets/breakout_brick.png");
	Init();

	//Game Loop
	while (!WindowShouldClose())
	{
		UpdateDraw();
	}

	CloseWindow();
	return 0;
}

void Init()
{
	padel.Init();
	ball.Init();

	padel.sprite = padel_spr;
	ball.sprite = ball_spr;

	if (FileExists("Level.ass"))
	{
		std::ifstream ifs("Level.ass");

		for (int i = 0; i < MAX_BRICKS; i++)
		{
			if (ifs >> rick[i])
			{
			
			}
		}

		for (int i = 0; i < MAX_BRICKS; i++)
		{
			brick[i] = new Brick();
			*brick[i] = rick[i];
			brick[i]->sprite = brick_spr;
		}
	}

	/*
	int brickCount = 0;
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 25; i++)
		{
			brick[brickCount] = new Brick(32 * i, 16*j);
			brick[brickCount]->sprite = brick_spr;
			brickCount++;
		}
	}
	*/
}

void Update()
{
	switch (state)
	{
		case MAIN:
		break;
		case EDIT:
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				for (int i = 0; i < MAX_BRICKS; i++)
				{
					if (brick[i] == nullptr)
					{
						brick[i] = new Brick(GetMouseX(), GetMouseY());
						brick[i]->sprite = brick_spr;
						break;
					}
				}
			}

			if (IsKeyPressed(KEY_SPACE))
			{
				state = GAME;
				std::ofstream ofs("Level.ass");

				for (int i = 0; i < MAX_BRICKS; i++)
				{
					if (brick[i] != nullptr)
						ofs << *brick[i] << std::endl;
					else
						ofs << NULL << std::endl;
				}
			}
		break;
		case GAME:
			ball.Update();
			padel.Update();

			if (ball.isLocked)
			{
				ball.position = { padel.position.x + padel.origin.x - (ball.size.x / 2), padel.position.y - 20 };
			}
			else
			{
				if (CheckCollisionRecs(ball.colRect, padel.colRect))
				{
					padel.Bounce(&ball);
				}

				for (int i = 0; i < MAX_BRICKS; i++)
				{
					if (brick[i] != nullptr)
					{
						if (CheckCollisionRecs(ball.colRect, brick[i]->colRect))
						{
							if (!ball.hasBounced)
							{
								brick[i]->Bounce(&ball);
								delete brick[i];
							}
						}
					}
				}
			}
		break;
	}
	

}

void Draw()
{
	BeginDrawing();
	ClearBackground(WHITE);
	switch (state)
	{
		case EDIT:
			DrawTexture(brick_spr, GetMouseX(), GetMouseY(), WHITE);
			for (int i = 0; i < MAX_BRICKS; i++)
			{
				if(brick[i] != nullptr)
					brick[i]->Draw();
			}
		break;
		case GAME:
			ball.Draw();
			padel.Draw();

			for (int i = 0; i < MAX_BRICKS; i++)
			{
				if (brick[i] != nullptr)
					brick[i]->Draw();
			}
		break;
	}

	EndDrawing();
}

void UpdateDraw()
{
	Update();
	Draw();
}