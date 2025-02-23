#include "KinematicSteeringOutput.h"


KinematicSteeringOutput::KinematicSteeringOutput()
{
	velocity = Vec3();
	rotation = 0.0f;
}

KinematicSteeringOutput::KinematicSteeringOutput(Vec3 velocity_, float rotation_)
{
	velocity = velocity_;
	rotation = rotation_;
}