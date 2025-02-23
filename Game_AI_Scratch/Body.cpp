#include "Body.h"

Body::Body()
{
    pos = Vec3();
    vel = Vec3();
    accel = Vec3();
	mass = 1.0f;
    radius = 0.0f;
    orientation = 0.0f;
    rotation = 0.0f;
    angular = 0.0f;
    maxSpeed = 0.0f;
    maxAcceleration = 0.0f;
    maxRotation = 0.0f;
    maxAngular = 0.0f;
	image = nullptr;

}

Body::Body(
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_,
    float radius_ = 0.0f,
    float orientation_ = 0.0f,
    float rotation_ = 0.0f,
    float angular_ = 0.0f,
    // These are not very good defaults, but they will prevent compiler warnings.
    float maxSpeed_ = 5.0f,
    float maxAcceleration_ = 1.0f,
    float maxRotation_ = 1.0f,
    float maxAngular_ = 1.0f
)
{
    pos = pos_;
    vel = vel_;
    accel = accel_;
    mass = mass_;
    radius = radius_;
    orientation = orientation_;
    rotation = rotation_;
    angular = angular_;
    maxSpeed = maxSpeed_;
    maxAcceleration = maxAcceleration_;
    maxRotation = maxRotation_;
    maxAngular = maxAngular_;

    image = nullptr;
}


Body::~Body(){
}

void Body::ApplyForce( Vec3 force_ ) {
    accel = force_ / mass;
}

void Body::Update( float deltaTime ){
    pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);
    vel = vel + accel * deltaTime;

    // Update orientation
    orientation += rotation * deltaTime;
    rotation += angular * deltaTime;

    // Clip to maxspeed, if speed exceeds max
    if (VMath::mag(vel) > maxSpeed)
    {
        vel = VMath::normalize(vel) * maxSpeed;
    }

    // Clip to maxrotation, if needed
    if (rotation > maxRotation) rotation = maxRotation;

    // Could introduce dampening, of velocity and/or rotation, to simulate friction
    //vel -= 0.05 * vel;
    //rotation -= 0.05 * rotation;

}

void Body::HandleEvents( const SDL_Event& event )
{
    if ( event.type == SDL_MOUSEBUTTONDOWN )
    {
        printf("Mousedown\n");
    }
    else if ( event.type == SDL_KEYDOWN )
    {
        if ( event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            printf("Space\n");
        }
    }
    // etc
}

void Body::setPos( Vec3 pos_ )
{
    pos = pos_;
}
