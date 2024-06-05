#pragma once

#include "SDL.h"

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
	SDL_Texture* stagePoop_texture_; // the SDL_Texture
	SDL_Texture* stageSnake_texture_; // the SDL_Texture
	SDL_Texture* stageRabbit_texture_; // the SDL_Texture
	SDL_Texture* start_button_texture_; // the SDL_Texture
	SDL_Texture* gallery_button_texture_; // the SDL_Texture
	SDL_Texture* option_button_texture_; // the SDL_Texture
	SDL_Texture* exit_button_texture_; // the SDL_Texture
	SDL_Texture* frame_texture_;

	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect stagePoop_source_rectangle_; // the rectangle for source image
	SDL_Rect stagePoop_destination_rectangle_; // for destination

	SDL_Rect stageSnake_source_rectangle_; // the rectangle for source image
	SDL_Rect stageSnake_destination_rectangle_;// for destination

	SDL_Rect stageRabbit_source_rectangle_; // the rectangle for source image
	SDL_Rect stageRabbit_destination_rectangle_; // for destination

	SDL_Rect start_button_source_rectangle_; // the rectangle for source image
	SDL_Rect start_button_destination_rectangle_; // for destination

	SDL_Rect gallery_button_source_rectangle_; // the rectangle for source image
	SDL_Rect gallery_button_destination_rectangle_; // for destination

	SDL_Rect option_button_source_rectangle_; // the rectangle for source image
	SDL_Rect option_button_destination_rectangle_; // for destination

	SDL_Rect exit_button_source_rectangle_; // the rectangle for source image
	SDL_Rect exit_button_destination_rectangle_; // for destination

	SDL_Rect frame_source_rectangle_;
	SDL_Rect frame_destination_rectangle_;
	SDL_Rect frame_destination_rectangle2_;
	SDL_Rect frame_destination_rectangle3_;

	Mix_Music* click_start;
	Mix_Music* click_gallery;
	Mix_Chunk* pause_Sound;

	bool selected_stage[3];
	// 0: poop, 1: snake, 2: rabbit
};

