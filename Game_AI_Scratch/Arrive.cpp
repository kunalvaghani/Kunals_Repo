#include "Arrive.h"
Arrive::Arrive(Body* npc_, Vec3 target_)
{
	npc = npc_;
	target = target_;
}

Arrive::~Arrive()
{
}

SteeringOutput* Arrive::getSteering()
{
	float targetSpeed;
	Vec3 targetVelocity;
	//std::cout << "Arrive is happening" << std::endl;
	Vec3 direction = target - npc->getPos();
	float distance = VMath::mag(direction);

	if (distance < targetRadius) {
		return NULL;
	}
	if (distance > slowRadius) {
		 targetSpeed= npc->getMaxSpeed();
	}
	else {
		// use scaled speed
		targetSpeed = npc->getMaxSpeed() * distance / slowRadius;
	}
	targetVelocity = direction;
	targetVelocity = VMath::normalize(targetVelocity);
	targetVelocity *= targetSpeed;

	// Acceleration tries to get to the target velocity
	result->linear = targetVelocity - npc->getVel();
	result->linear /= timeToTarget;

	result->angular = 0;
	return result;
}