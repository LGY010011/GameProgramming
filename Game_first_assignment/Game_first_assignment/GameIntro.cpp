//이미지 출처
//<a href="https://kr.freepik.com/free-vector/pixel-art-mystical-background_29019077.htm#query=pixel%20art%20space&position=4&from_view=keyword&track=ais&uuid=9bec65e7-17ec-42f8-94b3-937e680f0801">작가 pikisuperstar</a> 출처 Freepik

//✔ Music provided by 셀바이뮤직
//🎵 Title : 어둡고 묵직한 bgm by SellBuyMusic
//https ://sellbuymusic.com/md/muatcnf-ycbhnwh


#include "GameIntro.h"

Intro::Intro()
{
	// For Texture
	SDL_Surface* temp_surface = IMG_Load("../../Resources/IntroImage.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	
	destination_rectangle_.x = 0;
	destination_rectangle_.y = 0;
	destination_rectangle_.w = screenWidth;
	destination_rectangle_.h = screenHeight;

	text_push = false;

	background_music = Mix_LoadMUS("../../Resources/IntroMusic.mp3");
	if (!background_music)
	{
		printf(" %s\n", Mix_GetError());
		// this might be a critical error...
	}

	//폰트 열기
	fontK = TTF_OpenFont("../../Resources/Pretendard-Bold.ttf", 100);
	//"재장착" 설정
	SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Game Start!!", { 0,0,0 });

	g_start_rect.x = screenWidth / 2 - 200;
	g_start_rect.y = screenHeight / 2 - 50;
	g_start_rect.w = 400;
	g_start_rect.h = 100;
	g_start = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	Mix_VolumeMusic(128);
	Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작

}



Intro::~Intro()//인트로 페이즈 사라질 때 텍스쳐 해제
{
	SDL_DestroyTexture(texture_);
	if (background_music) Mix_FreeMusic(background_music);
	TTF_CloseFont(fontK);
}

void Intro::Update()//업데이트 할 거 없음
{
	if (text_push) {
		g_start_rect.x = screenWidth / 2 - 150;
		g_start_rect.y = screenHeight / 2 - 37;
		g_start_rect.w = 300;
		g_start_rect.h = 75;
	}
	else {
		
		g_start_rect.x = screenWidth / 2 - 200;
		g_start_rect.y = screenHeight / 2 - 50;
		g_start_rect.w = 400;
		g_start_rect.h = 100;
	}
}

void Intro::Reset() {
	Mix_VolumeMusic(128);
	Mix_FadeInMusic(background_music, -1, 2000);//노래 페이드인으로 바로 시작

}

void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderCopy(g_renderer, g_start, NULL, &g_start_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
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

			// 마우스 우클릭의 경우 다음 페이즈로 넘어감
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				Mix_FadeOutMusic(1);
				g_current_game_phase = PHASE_STAGE;
			}
			else if (event.button.button == SDL_BUTTON_LEFT)//좌클릭인데 텍스트 쪽이라면
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x >= g_start_rect.x && mouse_x <= g_start_rect.x + g_start_rect.w &&
					mouse_y >= g_start_rect.y && mouse_y <= g_start_rect.y + g_start_rect.h
					)
				{
					text_push=true;
				}
				
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (text_push) {
				text_push = false;
				Mix_FadeOutMusic(1);
				g_current_game_phase = PHASE_STAGE;
			}
			break;

		default:
			break;
		}
	}
}