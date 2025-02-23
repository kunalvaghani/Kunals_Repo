#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Debug.h"

class Window {
public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int getHeight();
	int getWidth();
	SDL_Window* getWindow() const;
	
private:
	
	int width, height;
	SDL_Window* window;
	SDL_GLContext context;
	void setAttributes(int major_, int minor_);
	void getInstalledOpenGLInfo(int *major, int *minor);
};
#endif // !WINDOW_H