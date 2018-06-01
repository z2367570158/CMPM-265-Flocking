#pragma once
#include <vector>
#include "Vehicle.h"

class VehicleSystem
{
public:
	VehicleSystem(Vector2f windowSize);
	~VehicleSystem();
	void AddVehicle(float x, float y);
	void RemoveVehicle();
	void RemoveVehicle(int index);
	void Update();

	Vector2f target;
	bool hasTarget;

	float targetFactor;
	float separationFactor;
	float alignmentFactor;
	float cohesionFactor;


	float closeDistance;

	vector<Vehicle*> flock;


private:
	Vector2f windowSize;
	Vector2f SeekTarget(Vector2f target, Vector2f origin);
	Vector2f SeekSeparation(Vehicle* v);
	Vector2f SeekAlignment(Vehicle* v);
	Vector2f SeekCohesion(Vehicle* v);

};

