#include <SDL.h>
#include "SceneManager.h"
#include "VulkanRenderer.h"
#include "OpenGLRenderer.h"
#include "Timer.h"
#include "Scene0.h"
#include "Debug.h"


SceneManager::SceneManager(): 
	currentScene(nullptr), timer(nullptr),
	fps(60), isRunning(false), rendererType(RendererType::VULKAN),
	renderer(nullptr) {}

SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}
	renderer->OnDestroy();
	delete renderer;
	Debug::Info("Deleting the GameSceneManager", __FILE__, __LINE__);

}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	switch(rendererType){
	case RendererType::OPENGL:
		renderer = new OpenGLRenderer();
		renderer->setRendererType(RendererType::OPENGL);
		renderer->CreateWindow(name_, width_, height_);
		renderer->OnCreate();
			
		
		break;

	case RendererType::VULKAN:
		renderer = new VulkanRenderer();
		renderer->setRendererType(RendererType::VULKAN);
		renderer->CreateWindow(name_, width_, height_);
		renderer->OnCreate();
		break;

	case RendererType::DIRECTX11:
	case RendererType::DIRECTX12:
		Debug::FatalError("Renderer not supported", __FILE__, __LINE__);
		return false;
		break;
	}

	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}
	
	BuildScene(SCENE0);
	
	return true;
}


void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	while (isRunning) {
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		GetEvents();
		SDL_Delay(timer->GetSleepTime(fps));	
	}
}

void SceneManager::GetEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
			case SDL_SCANCODE_Q:
				isRunning = false;
				return;

			case SDL_SCANCODE_F1:
				///BuildScene(SCENE1);
				break;

			case SDL_SCANCODE_F2:
				///BuildScene(SCENE2);
				break;

			case SDL_SCANCODE_F3:
				///BuildScene(SCENE3);
				break;

			case SDL_SCANCODE_F4:
				///BuildScene(SCENE4);
				break;

			case SDL_SCANCODE_F5:
				///BuildScene(SCENE5);
				break;

			case SDL_SCANCODE_F6:
				///BuildScene(SCENE6);
				break;

			default:
				BuildScene(SCENE0);
				break;
			}
		}
		if (currentScene == nullptr) {
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		
		currentScene->HandleEvents(sdlEvent);
	}
}

void SceneManager::BuildScene(SCENE_NUMBER scene) {
	bool status; 

	if (currentScene != nullptr) {
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE0:  
		currentScene = new Scene0(renderer);
		status = currentScene->OnCreate();
		break;

	case SCENE1:
		///currentScene = new Scene1();
		status = currentScene->OnCreate();
		break;

	case SCENE2:
		///currentScene = new Scene2();
		status = currentScene->OnCreate();
		break;

	case SCENE3:
		///currentScene = new Scene3();
		status = currentScene->OnCreate();
		break;

	case SCENE4:
		///currentScene = new Scene4();
		//status = currentScene->OnCreate();
		break;

	case SCENE5:
		///currentScene = new Scene5();
		status = currentScene->OnCreate();
		break;

	case SCENE6:
		///currentScene = new Scene6();
		status = currentScene->OnCreate();
		break;

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		break;
	}	
}


