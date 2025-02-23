#include <iostream>
#include <glew.h>
#include "Scene6.h"
#include "Debug.h"

Scene6::Scene6() {
	Debug::Info("Created Scene6: ", __FILE__, __LINE__);
}


Scene6::~Scene6() {
	
}

bool Scene6::OnCreate() {
	return true;
}

void Scene6::OnDestroy() {}

void Scene6::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene6::Update(const float deltaTime) {}

void Scene6::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




}
