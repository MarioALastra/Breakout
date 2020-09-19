#include "breakout.h"

void Padel::Init()
{
	size = { 64,16 };
	origin = { (size.x / 2), (size.y / 2) };
	position = {(SCREEN_WIDTH/2)-origin.x, 550-origin.y};
	colRect = { position.x,position.y,size.x,size.y};
}

void Padel::Update()
{
	position.x = Clamp<int>(GetMouseX()-origin.x,0,SCREEN_WIDTH-size.x);
	colRect.x = position.x;
	colRect.y = position.y;
}

void Padel::Draw()
{
	DrawTexture(sprite, position.x, position.y, WHITE);
	//DrawRectangle(position.x, position.y, size.x, size.y, BLACK);
	//DrawRectangle(colRect.x, colRect.y, colRect.width, colRect.height, GREEN);
}

void Padel::Bounce(Ball* ball)
{
	float padelOriginX = position.x + origin.x;
	float ballOriginX = ball->position.x + ball->size.x;

	ball->velocity.x = Clamp((ballOriginX - padelOriginX)/20 * BALL_SPEED,-BALL_SPEED,BALL_SPEED);
	ball->velocity.y = -ball->velocity.y;
	ball->hasBounced = true;
}