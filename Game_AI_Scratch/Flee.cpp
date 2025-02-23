#include "Flee.h"
Flee::Flee(Body* npc_, Vec3 target_)
{
	npc = npc_;
	target = target_;
}

Flee::~Flee()
{
}

SteeringOutput* Flee::getSteering()
{
	//std::cout << "flee is happening" << std::endl;
	result->linear = npc->getPos()- target;

	// accelerate in that direction
	result->linear = VMath::normalize(result->linear) * npc->getMaxAcceleration();
	result->angular = 0.0f;

	return result;
}