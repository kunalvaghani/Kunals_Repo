#include <iostream>
#include <glew.h>
#include "Scene2.h"
#include "Debug.h"

Scene2::Scene2() {
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
}


Scene2::~Scene2() {
	
}

bool Scene2::OnCreate() {
	return true;
}

void Scene2::OnDestroy() {}

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene2::Update(const float deltaTime) {}

void Scene2::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




}
