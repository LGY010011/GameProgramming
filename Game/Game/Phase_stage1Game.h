#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iomanip>
#include <sstream>
//#include <memory>
#include "Creature_stage1.h"
#include <vector>
#include <ctime>  // time 함수를 사용하기 위해 필요합니다.
#include <cstdlib>  // srand 함수를 사용하기 위해 필요합니다.
#include "STAGE.h"

extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
class Stage1 : public PhaseInterface
{
public:
    Stage1();
    ~Stage1();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();


private:
    Uint32 lastFireTime = 0;  // 마지막으로 투사체를 발사한 시간
    Uint32 invincibleStartTime = 0;
    Uint32 invincibleTime = 0;
    Uint32 dandelionInvincibleStartTime = 0;
    Uint32 monsterDamage = 0;
    Uint32 dogPoopInvincibleStartTime = 0;
    Uint32 gameStartTime = 0;
    Uint32 now = 0;


    DogPoop* dogPoop;
    Dandelion* dandelion;
    Chick* chick;
    Sparrow* sparrow;
    Item* items;
    SDL_Window* window;
    SDL_Renderer* renderer;

    //강아지똥 이미지 변수
    SDL_Rect dp_source_rect;
    SDL_Rect dp_dest_rect;
    SDL_Surface* dp_ani_surface;
    SDL_Texture* dogPoopTexture;  // 강아지 똥의 이미지 시트
    std::vector<SDL_Rect> dogPoopClips;  // 강아지 똥의 애니메이션 프레임
    SDL_Surface* dp_hit_surface;
    SDL_Texture* dogPoopHitTexture;  // 강아지 똥이 맞았을 때의 이미지


    //민들레 이미지 변수
    SDL_Surface* d_surface;
    SDL_Texture* d_texture;
    SDL_Rect d_source_rect;
    SDL_Rect d_dest_rect;

    SDL_Surface* d_hit_surface;
    SDL_Texture* d_hit_texture;  // 민들레 HP가 80 이하일 때의 이미지

    SDL_Surface* d_hit_surface2;
    SDL_Texture* d_hit_texture2;  // 민들레 HP가 40 이하일 때의 이미지

    SDL_Surface* d_hit_surface3;
    SDL_Texture* d_hit_texture3;  // 민들레 HP가 20 이하일 때의 이미지

    //병아리 이미지 변수
    SDL_Surface* c_surface;
    SDL_Texture* c_texture;
    SDL_Rect c_source_rect;
    SDL_Rect c_dest_rect;

    //참새 이미지 변수
    SDL_Surface* s_surface;
    SDL_Texture* s_texture;
    SDL_Rect s_source_rect;
    SDL_Rect s_dest_rect;

    //배경 이미지 변수
    SDL_Surface* bg_surface;
    SDL_Texture* bg_texture;
    SDL_Rect bg_source_rect;
    SDL_Rect bg_dest_rect;

    //배경 액자 이미지 변수
    SDL_Surface* bgframe_surface;
    SDL_Texture* bgframe_texture;
    SDL_Rect bgframe_source_rect;
    SDL_Rect bgframe_dest_rect;

    //투사체 이미지 변수
    SDL_Surface* p_surface;
    SDL_Texture* p_texture;
    SDL_Surface* p_rock_surface;
    SDL_Texture* p_rock_texture;
    SDL_Rect p_source_rect;
    SDL_Rect p_dest_rect;

    //아이템 이미지 변수
    SDL_Surface* i_surface;
    SDL_Texture* i_texture;
    SDL_Rect i_source_rect;
    SDL_Rect i_dest_rect;
    std::vector<std::vector<SDL_Rect>> itemClips;  // 아이템의 애니메이션 프레임

    //하트 이미지 변수
    SDL_Surface* h0_surface;
    SDL_Texture* h0_texture;
    SDL_Surface* h1_surface;
    SDL_Texture* h1_texture;
    SDL_Surface* h2_surface;
    SDL_Texture* h2_texture;
    SDL_Rect dp_heart_dest_rect;
    //SDL_Rect h_source_rect;
    //SDL_Rect h_dest_rect;

    //버튼 이미지 변수
    SDL_Texture* _stg1_continue_button_texture;
    SDL_Texture* _stg1_home_button_texture;
    SDL_Rect _stg1_continue_button_destination;
    SDL_Rect _stg1_home_button_destination;

    //검은 반투명 배경
    SDL_Texture* _stg1_pause_bg_texture;
    SDL_Rect _stg1_pause_bg_destination;
    std::vector<Monster*> monsters;

    //스테이지1 음악 변수
    Mix_Music* stg1_music;
    Mix_Chunk* stg1_eat_sound;
    Mix_Chunk* stg1_shoot_sound;
    Mix_Chunk* stg1_pause_sound;

    //스테이지1 효과음 부울 변수 (1번만 나게 하기 위해서)
    bool g_pause_sound_played = false;
    int g_is_paused = false;

    //스테이지1 일시정지 버튼 관련 변수 
    // 1이면 continue 버튼
    // 2이면 main 버튼
    int stg1_pause_btn_pushed;

};


extern bool g_flag_running;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int COLLISION_DISTANCE = 20;
extern bool is_intro_initialized;

extern bool g_key_left;
extern bool g_key_right;
extern bool g_key_up;
extern bool g_key_down;
extern bool g_key_space;
extern Uint32 FIRE_COOLDOWN;  // 투사체 발사 쿨타임
extern bool is_rock;

enum Direction {
    UP_,
    DOWN_,
    LEFT_,
    RIGHT_,
    LEFT_UP,
    RIGHT_UP,
    LEFT_DOWN,
    RIGHT_DOWN
};

extern Direction g_direction;
