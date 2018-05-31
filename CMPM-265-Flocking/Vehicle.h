#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "VectorMath.h"

using namespace std;
using namespace sf;



class Vehicle {
public:
	CircleShape shape;
	Vector2f desired;

	Vehicle(float x, float y, Vector2f windowSize);

	void Update(Vector2f target, bool hasTarget);

private:
	Vector2f windowSize;
	Vector2f velocity;
	Vector2f acceleration;
	float radius;
	float maxForce;
	float maxSpeed;


	Vector2f SeekTarget(Vector2f target);

};