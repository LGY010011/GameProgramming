#pragma once
#include <SDL.h>
#include "Creature_stage2.h"
#include "STAGE.h"


class Stage2 : public PhaseInterface {
public:
    Stage2();
    ~Stage2();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();




private:
    Turtle* turtle;
    Rabbit* rabbit;
    Coral* coral;
    Coral2* coral2;
    Conch* conch1;
    Conch* conch2;
    Conch* conch3;
    Conch* conch4;


    // 방향키 조작 변수들
    bool f_list[4];
    int f_state; // 현재 눌린 키 정보
    bool stop; // 정지 정보
    //방향키 조작 변수들
    //승패 확인 변수
    SDL_RendererFlip flip;

    //미로

    int rabbitSpawnTimer;
    int coral2_spawn_timer; // coral2의 나타나고 사라지는 시간을 제어하는 타이머
    int coral3_spawn_timer; // coral의 나타나고 사라지는 시간을 제어하는 타이머=>추가
    bool coral2_visible;
    bool coral3_visible;//=>추가

    Uint32 pauseStartTime;
    Uint32 totalPauseTime;
    Uint32 totalPauseTime_2;

    //아무키나 누르면 시작
    int stage2_startTime;
    int stage2_status; //0이면 키 대기 상태, 1이면 게임 중, 2면 게임 일시정지
    int alpha;

    //텍스쳐
    SDL_Texture* stage2_bg_texture;
    SDL_Texture* turtle_texture;
    SDL_Texture* rabbit_texture;
    SDL_Texture* coral_texture;
    SDL_Texture* coral2_texture;
    SDL_Texture* gan_texture;
    SDL_Texture* heart0_texture;
    SDL_Texture* heart2_texture;
    SDL_Texture* stage2_bgbgbg_texture;
    SDL_Texture* conch_texture;

    SDL_Texture* turtle2_texture;


    //텍스쳐 사각형
    SDL_Rect turtle_destination_rect;
    SDL_Rect rabbit_destination_rect;
    SDL_Rect coral_destination_rect;
    SDL_Rect coral2_destination_rect;
    SDL_Rect stage2_bg_destination_rect;
    SDL_Rect gan_destination_rect;
    SDL_Rect heart0_destination_rect;
    SDL_Rect heart2_destination_rect;
    SDL_Rect stage2_bgbgbg_destination_rect;
    SDL_Rect conch_destination_rect;
    SDL_Rect wait_destination_rect;

    SDL_Texture* wait_texture; // the SDL_Texture
    SDL_Texture* bg_texture; // the SDL_Texture 
    SDL_Rect bg_destination_rect; // for destination
    //버튼 텍스쳐
    SDL_Texture* button_main; // the SDL_Texture 
    SDL_Texture* button_continue; // the SDL_Texture 
    SDL_Rect continue_destination_rect; // for destination
    SDL_Rect main_destination_rect; // for destination

    //음향 
    Mix_Music* background_music;
    Mix_Chunk* conch_sound;
    Mix_Chunk* rabbit_sound;
    Mix_Chunk* coral_sound;
    Mix_Chunk* button_sound;
    //글씨 텍스쳐
    SDL_Texture* ready_texture;
    SDL_Rect readyCount_destination;

};
