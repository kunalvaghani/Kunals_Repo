#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "VulkanRenderer.h"
#include "OpenGLRenderer.h"
#include "Camera.h"

Scene0::Scene0(Renderer *renderer_): 
	Scene(nullptr),renderer(renderer_), camera(nullptr) {
	camera = new Camera();

	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	if(camera) delete camera;
}

bool Scene0::OnCreate() {
	int width = 0, height = 0;
	float aspectRatio;
	switch (renderer->getRendererType()){
	case RendererType::VULKAN:
		
		SDL_GetWindowSize(dynamic_cast<VulkanRenderer*>(renderer)->GetWindow(), &width, &height);
		aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		camera->Perspective(45.0f, aspectRatio, 0.5f, 20.0f);
		camera->LookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
		lightpos[0]= Vec3(0.0f, 0.0f, 3.0f);
		lightdiffuse[0] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
		lightpos[1] = Vec3(0.0f, 0.0f, 6.0f);
		lightdiffuse[1] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);


		break;
		
	case RendererType::OPENGL:
		break;
	}

	pushConst = new ModelMatrixPushConst;
	pushConst1 = new ModelMatrixPushConst;
	return true;
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_WINDOWEVENT) {
		switch (sdlEvent.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			printf("size changed %d %d\n", sdlEvent.window.data1, sdlEvent.window.data2);
			float aspectRatio = static_cast<float>(sdlEvent.window.data1) / static_cast<float>(sdlEvent.window.data2);
			camera->Perspective(45.0f, aspectRatio, 0.5f, 20.0f);
			if (renderer->getRendererType() == RendererType::VULKAN) {
				dynamic_cast<VulkanRenderer*>(renderer)->RecreateSwapChain();
			}
			break;
		}
	
	
	}
}
void Scene0::Update(const float deltaTime) {
	static float elapsedTime = 0.0f;
	elapsedTime += deltaTime;

	pushConst->modelMatrix= MMath::translate(1.5f, 0, 0)* MMath::rotate(elapsedTime * 90.0f, Vec3(0.0f, 1.0f, 0.0f))* MMath::scale(1,1,1);
	pushConst1->modelMatrix = MMath::translate(-1.5f, 0, 0)*MMath::rotate(elapsedTime * 180.0f, Vec3(1.0f, 0.0f, 1.0f)) * MMath::scale(1, 1, 1);

}

void Scene0::Render() const {
	switch (renderer->getRendererType()) {

	case RendererType::VULKAN:
		VulkanRenderer* vRenderer;
		vRenderer = dynamic_cast<VulkanRenderer*>(renderer);
		vRenderer->SetCameraUBO(camera->GetProjectionMatrix(), camera->GetViewMatrix(), pushConst->modelMatrix);
		
		vRenderer->SetLightUBO(lightpos, lightdiffuse, numberoflights);
		
		vRenderer->SetModelMatrix(pushConst->modelMatrix, pushConst1->modelMatrix);
		vRenderer->Render();
		break;

	case RendererType::OPENGL:
		OpenGLRenderer* glRenderer;
		glRenderer = dynamic_cast<OpenGLRenderer*>(renderer);
		/// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		/// Draw your scene here
		
		
		glUseProgram(0);
		
		break;
	}
}


void Scene0::OnDestroy() {
	
}
