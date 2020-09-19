#include "breakout.h";

Brick::Brick()
{
	position = { (float)0,(float)0 };
	size = { 32,16 };
	colRect = { position.x, position.y, size.x, size.y };
	origin = { position.x + (size.x / 2), position.y + (size.y / 2) };
}

Brick::Brick(int x, int y)
{
	position = { (float)x,(float)y };
	size = { 32,16 };
	colRect = { position.x, position.y, size.x, size.y };
	origin = { position.x+(size.x/2), position.y + (size.y / 2) };
}

void Brick::Update()
{

}

void Brick::Draw()
{
	DrawTexture(sprite, position.x, position.y, WHITE);
	//DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
}

void Brick::Bounce(Ball* ball)
{

	//ball->velocity.x = ((ball->position.x + ball->origin.x) - origin.x)/100 * BALL_SPEED;
	//ball->velocity.x = Sign((ball->position.x+ball->origin.x) -origin.x)*BALL_SPEED;
	ball->velocity.y = -ball->velocity.y;
	ball->hasBounced = true;
}

