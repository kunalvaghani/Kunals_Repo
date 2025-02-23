#include "KinematicSeek.h"


KinematicSeek::KinematicSeek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
	
}

KinematicSeek::~KinematicSeek()
{
	if (result)
		delete result;
	
}
KinematicSteeringOutput* KinematicSeek::getSteering()
{
	result->velocity = target->getPos() - character->getPos();
	

	// go full speed
	result->velocity = VMath::normalize(result->velocity) * character->getMaxSpeed();
	result->rotation = 0.0;
	return result;

	
}