#pragma once
#include "Matrix.h"
using namespace MATH;
class Camera {
private:
	Matrix4 projection;
	Matrix4 view;
	Matrix4 rotation;
	Matrix4 translate;

public:
	Camera();
	~Camera();
	void Perspective(const float fovy_, const float aspectRatio_, const float near_, const float far_);
	void LookAt(const Vec3& eye, const Vec3& at, const Vec3& up);
	inline Matrix4 GetProjectionMatrix() { return projection; }
	inline Matrix4 GetViewMatrix() { return view; }
};

