#ifndef FLEE_H
#define FLEE_H
#include "SteeringBehaviour.h"

class Flee :
    public SteeringBehaviour
{
protected:
    Vec3 target;

public:
    Flee(Body* npc_, Vec3 target_);
    virtual ~Flee();
    SteeringOutput* getSteering();

};

#endif

