#pragma once
#include "STAGE.h"
#include <string>
#define GRID 40



class Phase_stage3Ending : public PhaseInterface {
private:
    //엔딩 텍스쳐
    SDL_Texture* winEnding_texture;
    SDL_Texture* loseEnding_texture1;
    SDL_Texture* loseEnding_texture2;
    SDL_Texture* loseEnding_texture3;
    SDL_Texture* loseEnding_texture_gameover;
    SDL_Rect ending_destination;
    //버튼 텍스트 텍스쳐
    SDL_Texture* retry_button_texture;
    SDL_Texture* main_button_texture;
    SDL_Rect retry_button_destination;
    SDL_Rect main_button_destination;

    // 엔딩 페이즈로 넘어온 시간을 저장하는 변수
    int endingPhaseStartTime;
    int buttonToTime;//버튼을 위한 변수로 pageCheck가 4가 되면 그 시간 저장
    bool button; //버튼 생성 여부

    int flag = false;

    int buttonPushed;//1이면 retry버튼 =>intro로 이동 , 2면 home 버튼 main으로 이동


    int pageCheck;

    Mix_Music* win_music;
    Mix_Music* lose_music;
    Mix_Chunk* button_sound;

public:
    Phase_stage3Ending();
    ~Phase_stage3Ending();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();
};