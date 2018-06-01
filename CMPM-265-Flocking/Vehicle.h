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
	Vector2f velocity;

	Vehicle(float x, float y, Vector2f windowSize);

	void Update();

private:
	Vector2f windowSize;
	Vector2f acceleration;
	float radius;
	float maxForce;
	float maxSpeed;
	

};