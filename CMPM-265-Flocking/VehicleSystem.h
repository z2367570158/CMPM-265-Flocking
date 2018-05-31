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

	vector<Vehicle*> flock;


private:
	Vector2f windowSize;

};

