#include <iostream>
#include <glew.h>
#include "Scene1.h"
#include "Debug.h"

Scene1::Scene1() {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}


Scene1::~Scene1() {
	
}

bool Scene1::OnCreate() {
	return true;
}

void Scene1::OnDestroy() {}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene1::Update(const float deltaTime) {}

void Scene1::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




}
