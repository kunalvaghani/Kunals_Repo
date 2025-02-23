#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "PlayerBody.h"
#include <random> 
#include <cstdlib> 
#include <thread>
#include <mutex>
#include <condition_variable>


class GameManager {
private:
	/// These are called "forward declarations" The idea is that a pointer is 
	/// really just an unsigned int, so to create a pointer to it you really only
	/// need to tell the compiler that there is a class called Window and I need
	/// a pointer to it, thus the "class Window*" means trust me, there is a class 
	/// called Window, I just need a pointer to it.

	/// If that was too much for your brain, just #include "Window.h" and declare
	/// Window *ptr and don't use the word "class"  This is a second semester C++
	/// topic anyway
	class Window *windowPtr;
	class Timer *timer;
	bool isRunning;
	class Scene *currentScene;
    class PlayerBody *player;
    Uint32 changeSceneEventType; // event type number for user defined events
    bool launched = true;
	Vec3 MouseClick;
	std::thread preloadThread;
	std::mutex preloadMutex;
	std::condition_variable preloadCondVar;
	bool preloadRequired = false;
	int preloadSceneIndex = 0;
	

public:
	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();
	float getSceneHeight();
	float getSceneWidth();
	Vec3 getrandompoint();
	Vec3 getMouseClick() { return MouseClick; }
	Matrix4 getProjectionMatrix();
    PlayerBody* getPlayer(){ return player; }
	Uint32 getChangeScene() { return changeSceneEventType; }

	SDL_Renderer* getRenderer();
	void RenderPlayer(float scale = 1.0f);
	void Run();
	void PreloadNextScene();
    void LoadScene( int i );
    void handleEvents();
    bool ValidateCurrentScene();
    
};
#endif


