#pragma once
#include "Actor.h"
#include <Matrix.h>
using namespace MATH;

class CameraActor : public Actor {
	CameraActor(const CameraActor&) = delete;
	CameraActor(CameraActor&&) = delete;
	CameraActor& operator= (const CameraActor&) = delete;
	CameraActor& operator=(CameraActor&&) = delete;
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	unsigned int uboMatriciesID;
	unsigned int bindingPoint;
	bool isCreated;
public:
	CameraActor(Component* parent_);
	~CameraActor();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	Matrix4 GetProjectionMatrix() const { return projectionMatrix; }
	Matrix4 GetViewMatrix() const { return viewMatrix; }
	unsigned int GetMatriciesID() const { return uboMatriciesID; }
	void UpdateProjectionMatrix(const float fovy, const float aspectRatio, const float near, const float far);
	void UpdateViewMatrix();
};
