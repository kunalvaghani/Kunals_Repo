#include "Collision.h"

Collision::Collision()
{
	body1 = new Body();
	body2 = new Body();
}

Collision::~Collision()
{
}



bool Collision::CollisionOccured(Body* body1_, Body* body2_)
{
    body1_ = body1;
    body2_ = body2;
    // Assuming Body objects have positions and sizes
    const float body1X = body1_->getPos().x;
    const float body1Y = body1_->getPos().y;


    const float body2X = body2_->getPos().x;
    const float body2Y = body2_->getPos().y;


    // Check for AABB collision
    return (body1X < body2X &&
        body1X  > body2X && body1Y < body2Y && body1Y > body2Y);
}
