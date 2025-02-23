#ifndef KINEMATIC_SEEK_H
#define KINEMATIC_SEEK_H

#include <Vector.h>
#include <VMath.h>
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicSeek
{
private:
	KinematicSteeringOutput* result;
	Body* character;
	Body* target;

public:
	KinematicSeek(Body* character_, Body* target_);
	virtual ~KinematicSeek();


	KinematicSteeringOutput* getSteering();
};

#endif