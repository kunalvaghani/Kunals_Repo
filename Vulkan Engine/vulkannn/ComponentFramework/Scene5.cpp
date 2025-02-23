#include <iostream>
#include <glew.h>
#include "Scene5.h"
#include "Debug.h"

Scene5::Scene5() {
	Debug::Info("Created Scene5: ", __FILE__, __LINE__);
}


Scene5::~Scene5() {
	
}

bool Scene5::OnCreate() {
	return true;
}

void Scene5::OnDestroy() {}

void Scene5::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene5::Update(const float deltaTime) {}

void Scene5::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




}
