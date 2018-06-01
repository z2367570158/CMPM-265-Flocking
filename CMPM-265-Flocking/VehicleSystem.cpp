#include "VehicleSystem.h"

VehicleSystem::VehicleSystem(Vector2f windowSize)
{
	this->windowSize = windowSize;
	hasTarget = false;
	target = 0.5f*windowSize;


	targetFactor = 0;
	separationFactor = 0;
	alignmentFactor = 0;
	cohesionFactor = 0;

	closeDistance = 10;
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
		Vector2f targetDesired = SeekTarget(target, v->shape.getPosition());
		Vector2f separationDesired = SeekSeparation(v);
		Vector2f alignmentDesired = SeekAlignment(v);
		
		v->desired = separationFactor * separationDesired + alignmentDesired* alignmentFactor;

		if (targetFactor == 0)
			v->desired += v->velocity;
		else
			v->desired += targetFactor * targetDesired;

		v->Update();
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


Vector2f VehicleSystem::SeekTarget(Vector2f target, Vector2f origin)
{
	Vector2f desired = target - origin;
	float mag = Magnitude(desired);
	if (mag< 30)
		desired *= mag / 30;
	else
		desired = Normalize(desired);

	return desired;
}


Vector2f VehicleSystem::SeekSeparation(Vehicle* v)
{
	float separationCount = 0;
	Vector2f separationDesired = Vector2f(0, 0);

	for (Vehicle* other : flock)
	{
		if (v == other)
			continue;

		Vector2f dir = v->shape.getPosition() - other->shape.getPosition();
		if (MagnitudeSquare(dir) < closeDistance*closeDistance)
		{
			dir = Normalize(dir);
			separationDesired += dir;
			separationCount++;
		}
	}

	if(separationCount>0)
		separationDesired *= 1 / separationCount;

	return separationDesired;
}



Vector2f VehicleSystem::SeekAlignment(Vehicle* v)
{
	float alignmentCount = 0;
	Vector2f alignmentDesired = Vector2f(0, 0);

	for (Vehicle* other : flock)
	{
		if (v == other)
			continue;

		if (MagnitudeSquare(v->shape.getPosition() - other->shape.getPosition()) < closeDistance*closeDistance)
		{
			alignmentDesired += Normalize(other->velocity);
			alignmentCount++;
		}
	}

	if (alignmentCount>0)
		alignmentDesired *= 1 / alignmentCount;

	return alignmentDesired;
}


Vector2f VehicleSystem::SeekCohesion(Vehicle* v)
{
	float CohesionCount = 0;
	Vector2f cohesionDesired = Vector2f(0, 0);

	for (Vehicle* other : flock)
	{
		if (v == other)
			continue;

		if (MagnitudeSquare(v->shape.getPosition() - other->shape.getPosition()) < closeDistance*closeDistance)
		{
			cohesionDesired += other->shape.getPosition();
			CohesionCount++;
		}
	}

	if (CohesionCount > 0)
	{
		cohesionDesired *= 1 / CohesionCount;
		cohesionDesired -= v->shape.getPosition();
		return cohesionDesired;
	}
	else
		return Vector2f(0, 0);



}
