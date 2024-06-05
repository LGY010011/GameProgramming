#pragma once
#include "STAGE.h"
#include <string>



class Phase_stage1Ending : public PhaseInterface {
private:
    //엔딩 텍스쳐
    SDL_Texture* stg1_dandelion_ending_texture1;
    SDL_Texture* stg1_dandelion_ending_texture2;
    SDL_Texture* stg1_dogPoop_ending_texture1;
    SDL_Texture* stg1_dogPoop_ending_texture2;
    SDL_Texture* stg1_happy_ending_texture1;
    SDL_Rect stg1_ending_destination;
    //버튼 텍스트 텍스쳐
    SDL_Texture* stg1_retry_button_texture;
    SDL_Texture* stg1_home_button_texture;
    SDL_Rect stg1_retry_button_destination;
    SDL_Rect stg1_home_button_destination;

    //엔딩 사운드
    Mix_Chunk* stg1_gosad_sound;
    Mix_Chunk* stg1_gohappy_sound;
    // 엔딩 페이즈로 넘어온 시간을 저장하는 변수
    int stg1_endingPhaseStartTime;
    bool  stg1_button; //버튼 생성 여부

    int stg1_buttonPushed;//1이면 retry버튼 =>intro로 이동 , 2면 home 버튼 main으로 이동

    //TTF_Font* font = TTF_OpenFont("../../Resource/establish Retrosans.ttf", 100);

    int stg1_pageCheck;
public:
    Phase_stage1Ending();
    ~Phase_stage1Ending();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();
};