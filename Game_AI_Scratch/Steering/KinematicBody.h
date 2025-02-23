#ifndef KINEMATIC_BODY_H
#define KINEMATIC_BODY_H

#include "Body.h"
#include "SteeringOutput.h"

class KinematicBody :
		public Body
{
protected:

public:
	KinematicBody() : Body{}
	{}

	KinematicBody(
		Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_,
		float radius_,
		float orientation_ = 0.0f,
		float rotation_ = 0.0f,
		float angular_ = 0.0f,
		float maxSpeed_ = 1.0f,
		float maxAcceleration_ = 1.0f,
		float maxRotation_ = 1.0f,
		float maxAngular_ = 1.0f
	) : Body{ pos_, vel_, accel_, mass_ 
		, radius_
		, orientation_
		, rotation_
		, angular_
		, maxSpeed_
		, maxAcceleration_
		, maxRotation_
		, maxAngular_
		
	}
    {}

	void Update( float deltaTime, SteeringOutput *steering );
};

#endif
