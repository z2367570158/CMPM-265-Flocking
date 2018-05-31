#pragma once
#include <SFML/System.hpp>
#include <math.h>

using namespace sf;

static float PI = 3.1415926f;

static inline float Dot(Vector2f a, Vector2f b)
{
	return a.x*b.x + a.y*b.y;
}

static inline float Magnitude(Vector2f v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

static inline float MagnitudeSquare(Vector2f v)
{
	return v.x*v.x + v.y*v.y;
}
static inline Vector2f Normalize(Vector2f v)
{
	float mag = Magnitude(v);
	Vector2f result = (mag == 0) ? Vector2f(0, 0) : Vector2f(v.x / mag, v.y / mag);
	return result;
}