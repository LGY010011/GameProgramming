#pragma once
#include "Game.h"

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	Mix_Music* background_music;

	TTF_Font* fontK;
	SDL_Texture* g_start;
	SDL_Rect g_start_rect;

	bool text_push;
};