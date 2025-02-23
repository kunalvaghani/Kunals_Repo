#include "SteeringOutput.h"

SteeringOutput::SteeringOutput()
{
	linear = Vec3( 0, 0, 0 );
	angular = 0.0f;
}

SteeringOutput::SteeringOutput( Vec3 linear_, float angular_ )
{
	linear = linear_;
	angular = angular_;
}
