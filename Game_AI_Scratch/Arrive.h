#ifndef ARRIVE_H
#define ARRIVE_H
#include "SteeringBehaviour.h"

class Arrive:
    public SteeringBehaviour
{
protected:
    Vec3 target;
    // The radius for arriving at the 
    float targetRadius=1;
    // The radius for beginning to 
    float slowRadius=3;
     // The time over which to achieve target 
    float timeToTarget = 0.1;

public:
    Arrive( Body* npc_, Vec3 target_);
    virtual ~Arrive();
    SteeringOutput* getSteering();

};

#endif

