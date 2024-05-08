#pragma once

class Ending : public PhaseInterface
{
public:
	Ending();
	~Ending();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	Mix_Music* background_music;

	//폰트용 변수
	TTF_Font* fontK;
	SDL_Texture* g_end;
	SDL_Rect g_end_rect;
};