#include "Camera.h"
#include "MMath.h"


Camera::Camera() {
	projection.loadIdentity();/// it did it autamatically; but this just reminds me
	view.loadIdentity();
}

Camera::~Camera() {
	/// There's nothing to do here yet
}

void Camera::Perspective(const float fovy, const float aspectRatio, const float near, const float far) {
	projection = MMath::perspective(fovy, aspectRatio, near, far);
}
void Camera::LookAt(const Vec3& eye, const Vec3& at, const Vec3& up) {
	view = MMath::lookAt(eye,at,up);
}
