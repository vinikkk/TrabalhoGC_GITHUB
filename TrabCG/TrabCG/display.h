#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

	virtual ~Display();
	SDL_Surface* loadSurface(std::string path);
	bool loadMedia();

protected:
private:
	void operator=(const Display& display) {};
	Display(const Display& display) {};

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	SDL_Surface* m_screenSurface;
	SDL_Surface* gPNGSurface = NULL;
};

#endif // DISPLAY_H