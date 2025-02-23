#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include "Renderer.h"
class SceneManager  {
public:
	
	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void GetEvents();
	
	
private:
	
	enum SCENE_NUMBER {
		SCENE0 = 0,
		SCENE1,
		SCENE2,
		SCENE3,
		SCENE4,
		SCENE5,
		SCENE6
	};

	enum class RendererType rendererType;
	class Scene* currentScene;
	class Timer* timer;

	Renderer* renderer;
	unsigned int fps;
	bool isRunning;
	void BuildScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H