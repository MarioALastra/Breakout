#include "breakout.h"



void Ball::Init()
{
	size = { 8,8 };
	origin = { size.x / 2,size.y / 2 };
	position = { position.x - origin.x, position.y - origin.y };
	velocity = { 0,0 };
	colRect = { -100,-100,size.x,size.y };
	isLocked = true;
	hasBounced = false;
	frameCounter = 0;
}

void Ball::Update()
{
	if (isLocked)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			isLocked = false;
			velocity = { 0,-BALL_SPEED };
		}
	}
	else
	{
		if (position.y <= 0)
			velocity.y = -velocity.y;

		if (position.y >= SCREEN_HEIGHT)
			Init();

		if (position.x <= 0 || position.x >= SCREEN_WIDTH - size.x)
			velocity.x = -velocity.x;

		position.x += velocity.x;
		position.y += velocity.y;
		colRect.x = position.x + velocity.x;
		colRect.y = position.y + velocity.y;
	}

	if (hasBounced)
	{
		if (frameCounter < 5)
			frameCounter++;
		else
		{
			hasBounced = false;
			frameCounter = 0;
		}
	}
}

void Ball::Draw()
{
	DrawTexture(sprite, position.x, position.y, WHITE);
	//DrawRectangle(position.x, position.y, size.x, size.y, GREEN);
	//DrawRectangle(colRect.x, colRect.y, colRect.width, colRect.height, BLACK);
}