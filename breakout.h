#pragma once
#include <fstream>
#include <iostream>
#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float BALL_SPEED = 10;
const int MAX_BRICKS = 250;

enum AssetType{EMPTY, BRICK};

class Ball
{
public:
	Vector2 position;
	Vector2 size;
	Vector2 velocity;
	Vector2 origin;
	Rectangle colRect;
	Texture2D sprite;
	int frameCounter;
	bool isLocked;
	bool hasBounced;
	void Init();
	void Update();
	void Draw();
};

class Padel
{
public:
	Vector2 position;
	Vector2 size;
	Vector2 origin;
	Rectangle colRect;
	Texture2D sprite;
	void Init();
	void Update();
	void Draw();
	void Bounce(Ball* ball);
};

class Brick
{
public:
	Brick(int x, int y);
	Brick();
	Vector2 position;
	Vector2 size;
	Vector2 origin;
	Rectangle colRect;
	Texture2D sprite;
	void Update();
	void Draw();
	void Bounce(Ball* ball);

	friend std::ostream& operator<<(std::ostream& os, const Brick& b)
	{
		// write out individual members of s with an end of line between each one
		os << b.position.x << '\n';
		os << b.position.y << '\n';
		os << b.size.x << '\n';
		os << b.size.y << '\n';
		os << b.origin.x << '\n';
		os << b.origin.y << '\n';
		os << b.colRect.x << '\n';
		os << b.colRect.y << '\n';
		os << b.colRect.width << '\n';
		os << b.colRect.height << '\n';
		os << b.sprite.format << '\n';
		os << b.sprite.height << '\n';
		os << b.sprite.id << '\n';
		os << b.sprite.mipmaps << '\n';
		os << b.sprite.width;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Brick& b)
	{
		// read in individual members of s
		is >> b.position.x >> b.position.y >> b.size.x >> b.size.y >> b.origin.x >> b.origin.y;
		is >> b.colRect.x >> b.colRect.y >> b.colRect.width >> b.colRect.height;
		is >> b.sprite.format >> b.sprite.height >> b.sprite.id>> b.sprite.mipmaps >> b.sprite.width;
		return is;
	}
};

class Level
{
public:
	void LoadLevel();
	void SaveLevel();
};

template <class T>
T Clamp(T value, T min, T max)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;
	else
		return value;
}

template <class T>
T Sign(T value)
{
	if (value > 0)
		return 1;
	else if (value < 0)
		return -1;
	else
		return 0;
}
