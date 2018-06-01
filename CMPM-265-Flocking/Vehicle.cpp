#include "Vehicle.h"

Vehicle::Vehicle(float x, float y, Vector2f windowSize)
{
	this->windowSize = windowSize;
	shape.setPointCount(3);
	shape.setPosition(x, y);
	radius = 10;
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	
	velocity = Vector2f(0, 0);
	acceleration = Vector2f(0,0);

	maxSpeed = 3;
	maxForce = 0.3f;
}

// Our seek steering force algorithm
void Vehicle::Update() {

	desired = Normalize(desired)*maxSpeed;

	if (shape.getPosition().x < 30)
	{
		desired.x = maxSpeed;
	}
	else if (shape.getPosition().x > windowSize.x - 30)
	{
		desired.x = -maxSpeed;
	}
	
	if (shape.getPosition().y < 30)
	{
		desired.y = maxSpeed;
	}
	else if (shape.getPosition().y > windowSize.y - 30)
	{
		desired.y = -maxSpeed;
	}

	Vector2f steer = desired - velocity;

	if (MagnitudeSquare(steer) > maxForce*maxForce)
		steer = Normalize(steer)*maxForce;
	
	acceleration = steer;

	velocity += acceleration;
	if (MagnitudeSquare(velocity) > maxSpeed*maxSpeed)
		velocity = Normalize(velocity)*maxSpeed;

	shape.setRotation(atan2f(velocity.y, velocity.x) * 180 / PI+90);
	shape.move(velocity);
}
