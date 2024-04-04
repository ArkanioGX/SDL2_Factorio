#include "Window.h"
#include "Log.h"
Window::Window() : RenderWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGHT)
{
}

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}
	RenderWindow = SDL_CreateWindow("Basic Factory Game", 100, 100, width, height, 0); //0 is flag we will use later
	if (!RenderWindow)
	{
	Log::error(LogCategory::System, "Failed to create window");
		return false;
	}
	return true;
}

void Window::close() {
	SDL_DestroyWindow(RenderWindow);
}
