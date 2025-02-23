#include <iostream>
#include <glew.h>
#include "Scene4.h"
#include "Debug.h"

Scene4::Scene4() {
	Debug::Info("Created Scene4: ", __FILE__, __LINE__);
}


Scene4::~Scene4() {
	
}

bool Scene4::OnCreate() {
	return true;
}

void Scene4::OnDestroy() {}

void Scene4::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene4::Update(const float deltaTime) {}

void Scene4::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




}
