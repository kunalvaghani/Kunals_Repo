#include "KinematicBody.h"

void KinematicBody::Update( float deltaTime, SteeringOutput *steering )
{
    // Update position, call Update from parent class
    // Note that would update velocity too, but the acceleration in the member object is 0.0!
    Body::Update( deltaTime );

    // TODO Body reaching edge of scene needs to be handled somewhere
    // especially if implementing the flee behaviour

    // Adjust velocity and rotation according to steering input
    if ( steering )
    {
        accel = steering->linear;
        angular = steering->angular ;
    }

}
