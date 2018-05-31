#include "VehicleSystem.h"

VehicleSystem::VehicleSystem(Vector2f windowSize)
{
	this->windowSize = windowSize;
	hasTarget = false;
	target = 0.5f*windowSize;
}

VehicleSystem::~VehicleSystem()
{
	for (int i=0; i<flock.size(); i++)
	{
		delete flock[i];
		flock[i] = nullptr;
	}

	flock.clear();
}

void VehicleSystem::Update()
{
	for (Vehicle* v : flock)
	{
		v->Update(target, hasTarget);
	}
}


void VehicleSystem::AddVehicle(float x, float y)
{
	Vehicle* v = new Vehicle(x, y, windowSize);
	flock.push_back(v);

}

void VehicleSystem::RemoveVehicle(int index)
{
	if (index < flock.size() && index >= 0)
	{
		delete flock[index];
		flock[index] = nullptr;
		flock.erase(flock.begin() + index);
	}
}

void VehicleSystem::RemoveVehicle()
{
	if (flock.size() > 0)
	{
		delete flock[flock.size() - 1];
		flock[flock.size() - 1] = nullptr;
		flock.pop_back();
	}
}