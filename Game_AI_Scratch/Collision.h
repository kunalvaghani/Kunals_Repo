
#ifndef COLLISION_H
#define COLLISION_H
#include "Body.h"
class Collision
{
private:
	Body* body1;
	Body* body2;
public:
	Collision();
	~Collision();

	bool CollisionOccured(Body* body1_, Body* body2_);
};

#endif
