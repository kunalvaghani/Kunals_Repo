#include <iostream>
#include <glew.h>
#include "Scene3.h"
#include "Debug.h"

Scene3::Scene3() {
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}


Scene3::~Scene3() {

}

bool Scene3::OnCreate() {
	return true;
}

void Scene3::OnDestroy() {}

void Scene3::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene3::Update(const float deltaTime) {}

void Scene3::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
