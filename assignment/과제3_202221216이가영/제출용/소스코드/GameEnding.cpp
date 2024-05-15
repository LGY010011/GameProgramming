//이미지 출처
//<a href="https://kr.freepik.com/free-vector/watercolor-purple-striped-background_30576599.htm">출처 freepik</a>

//✔ Music provided by 셀바이뮤직
//🎵 Title : 니아 by SellBuyMusic
//https ://sellbuymusic.com/md/myvtckh-icbhnwh


#include "Game.h"
#include "GameEnding.h"

Ending::Ending()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../../Resources/EndingImage.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w;
	destination_rectangle_.h = source_rectangle_.h;

	background_music = Mix_LoadMUS("../../Resources/EndingMusic.mp3");
	if (!background_music)
	{
		printf(" %s\n", Mix_GetError());
		// this might be a critical error...
	}
	Mix_VolumeMusic(128);

	//폰트 열기
	fontK = TTF_OpenFont("../../Resources/Pretendard-Bold.ttf", 100);
	//"END" 설정
	SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"END", { 0,0,0 });

	g_end_rect.x = screenWidth / 2 - 125;
	g_end_rect.y = screenHeight / 2 - 50;
	g_end_rect.w = 250;
	g_end_rect.h = 100;
	g_end = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

}

void Ending::Reset() {
	
	Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작

}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
	if (background_music) Mix_FreeMusic(background_music);
	TTF_CloseFont(fontK);
}

void Ending::Update()
{
}


void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderCopy(g_renderer, g_end, NULL, &g_end_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Ending::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				Mix_FadeOutMusic(1);
				g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}
}