#define _CRT_SECURE_NO_WARNINGS
#include "SnakeGame.h"


void SnakeGame::UpdateScoreTexture()
{
    if (snake_length != 0)
    {
        SDL_DestroyTexture(snake_length);		// !!!�߿�!!!  �̹� �����Ǿ��ִ� texture �� ������ �ݵ�� �޸𸮿��� �������Ѵ�. !!!
        snake_length = 0;
    }

    sprintf(text, u8"%03d", snake->getSnakeLength()); // ���ڿ� ������ ����Ͽ� text�� ���ڿ��� �����մϴ�.

    SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(fontK, text, { 255,255,255 });

    snake_length_rect.x = screenWidth-GRID*3;
    snake_length_rect.y = GRID*4;
    snake_length_rect.w = GRID*2;
    snake_length_rect.h = GRID;

    snake_length = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

}

void SnakeGame::UpdateTimeTexture(int ms)
{
    if (text_time != 0)
    {
        SDL_DestroyTexture(text_time);		// !!!�߿�!!!  �̹� �����Ǿ��ִ� texture �� ������ �ݵ�� �޸𸮿��� �������Ѵ�. !!!
        text_time = 0;
    }

    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    char timeStr[6];
    sprintf(timeStr, "%02d:%02d", minutes, seconds);

    SDL_Surface* tmp_surface = TTF_RenderText_Blended(fontK, timeStr, { 255,255,255 });
    text_time_rect.x = screenWidth - GRID * 3 - GRID / 2;
    text_time_rect.y = screenHeight - GRID * 3;
    text_time_rect.w = GRID * 3;
    text_time_rect.h = GRID * 2;

    text_time = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

    SDL_FreeSurface(tmp_surface);
}


SnakeGame::SnakeGame() {
    std::cout << "���� ����" << std::endl;
    g_flag_running = true;
    //2. �ؽ��� �ҷ�����
    //2.1 Snake �ؽ��� �ҷ�����
    snake = new Snake();

    SDL_Surface* snakeHead_sheet_surface = IMG_Load("../../Resources/head.png");
    std::cout << "snake ��� �̹��� �ε�" << std::endl;
    snakeHead_texture = SDL_CreateTextureFromSurface(g_renderer, snakeHead_sheet_surface);
    SDL_FreeSurface(snakeHead_sheet_surface);//���� �ʼ�
    snakeHead_source_rect.x = 0;
    snakeHead_source_rect.y = 0;
    snakeHead_source_rect.w = 512;
    snakeHead_source_rect.h = 512;


    snake_destination_rect.w = GRID; //ũ�� 10*10
    snake_destination_rect.h = GRID;

    snake_destination_rect.x = snake->getSnakeHead()->x; //ȭ�� �߾ӿ� �׷��� ��
    snake_destination_rect.y = snake->getSnakeHead()->y;


    SDL_Surface* snake_sheet_surface = IMG_Load("../../Resources/snake.png");
    std::cout << "snake �̹��� �ε�" << std::endl;
    snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_sheet_surface);
    SDL_FreeSurface(snake_sheet_surface);//���� �ʼ�

    snake_source_rect.x = 0;
    snake_source_rect.y = 0;
    snake_source_rect.w = 512;
    snake_source_rect.h = 512;

 
    
    //2.2 ������ �ؽ��� �ҷ�����
    item = new Item(snake->getSnakeList());

    SDL_Surface* item_sheet_surface = IMG_Load("../../Resources/item.png");
    std::cout << "������ �̹��� �ε�" << std::endl;

    item_texture = SDL_CreateTextureFromSurface(g_renderer, item_sheet_surface);
    SDL_FreeSurface(item_sheet_surface);//���� �ʼ�

    item_source_rect.x = 0;
    item_source_rect.y = 0;
    item_source_rect.w = 512;
    item_source_rect.h = 512;

    item_destination_rect.w = GRID; //ũ�� 10*10
    item_destination_rect.h = GRID;
    item_destination_rect.x = item->getX(); //�׷��� ��ǥ ����
    item_destination_rect.y = item->getY();

    

    //2.3 background �ؽ��� �ҷ�����
    //��� �̹��� ����
    SDL_Surface* bg_sheet_surface = IMG_Load("../../Resources/background.png");
    std::cout << "��� �̹��� �ε�" << std::endl;
    bg_texture= SDL_CreateTextureFromSurface(g_renderer, bg_sheet_surface);
    SDL_FreeSurface(bg_sheet_surface);//���� �ʼ�
    bg_destination_rect.x = GRID;
    bg_destination_rect.y = GRID;
    bg_destination_rect.w = screenWidth-GRID*5;
    bg_destination_rect.h = screenHeight-GRID*2;
    
    //3. ��Ʈ ��������
    //��Ʈ �ҽ� ȣ��
    fontK=TTF_OpenFont("../../Resources/establish Retrosans.ttf", 100);
    //3.1 ready �ؽ��� �����
    SDL_Surface * tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Ready", {0,0,0});
    read_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2;
    read_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    read_rect.w = tmp_surface->w;
    read_rect.h = tmp_surface->h;
    ready = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.2 game over �ؽ��� �����
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Game Over", { 0,0,0 });
    over_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2+bg_destination_rect.x;
    over_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    over_rect.w = tmp_surface->w;
    over_rect.h = tmp_surface->h;
    over = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.3 score �ؽ���
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"SCORE", { 255,255,255 });
    snake_score_rect.x = screenWidth - GRID * 3 - GRID / 2;
    snake_score_rect.y = GRID;
    snake_score_rect.w = GRID*3;
    snake_score_rect.h = GRID*2;
    snake_score = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.4 �� ���� ���� ��� �ؽ���
    UpdateScoreTexture();
    

    //3. ����Ű �ʱ�ȭ
    snakeGame_running = 0;
    stop = true;
    s_state = -1;//����Ű �� ����
    //4. �ð� �ʱ�ȭ
    time_ms_ = 0;
    UpdateTimeTexture(time_ms_);
    
}

void SnakeGame::Render() {
    //std::cout << "render" << std::endl;
    //// 1. ��� �׸���.
    SDL_RenderClear(g_renderer); //�������� �ʱ�ȭ
    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);

    //// 2. ������ �׸���
    item_destination_rect.x = item->getX(); //�׷��� ��ǥ ����
    item_destination_rect.y = item->getY();
    SDL_RenderCopy(g_renderer, item_texture, NULL, &item_destination_rect);
    
    //// 3. �� �׸���
    auto snakeList = snake->getSnakeList();
    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->x; // �׷��� ��ǥ ����
        snake_destination_rect.y = (*it)->y;

        // ���� ��� ����� ��쿡�� ��� �̹����� ����ϰ�, �׷��� ���� ��쿡�� ������ �� �̹����� ����մϴ�.
        if (it == snakeList.begin()) {

            switch (s_state) {
            case 0://��
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, -90, NULL, SDL_FLIP_NONE);
                break;
            case 1://��
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, 90, NULL, SDL_FLIP_NONE);
                break;
            case -1:
            case 2://��
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, 0, NULL, SDL_FLIP_NONE);
                break;
            case 3://�Ʒ�
                SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, 180, NULL, SDL_FLIP_NONE);
                break;
            default:
                break;
            }
            //SDL_RenderCopy(g_renderer, snakeHead_texture, NULL, &snake_destination_rect);
        }
        else {
            SDL_RenderCopy(g_renderer, snake_texture, NULL, &snake_destination_rect);
        }
    }

    
    //���� �ؽ���
    UpdateScoreTexture();
    SDL_RenderCopy(g_renderer, snake_score, NULL, &snake_score_rect);
    SDL_RenderCopy(g_renderer, snake_length, NULL, &snake_length_rect);

    if (snakeGame_running == 0) {
        SDL_RenderCopy(g_renderer, ready, NULL, &read_rect);
    }else if(snakeGame_running == 2) {
        SDL_RenderCopy(g_renderer, over, NULL, &over_rect);
    }
    
    UpdateTimeTexture(time_ms_);
    SDL_RenderCopy(g_renderer, text_time, NULL, &text_time_rect);

    SDL_RenderPresent(g_renderer);
}

void SnakeGame::Update() {
    //std::cout << "update" << std::endl;
    if (snakeGame_running == 0 || snakeGame_running==2) // ���� ����Ű�� �� ���� ��Ȳ�̶�� ������Ʈ �� ��
        return;
    //1. snake & item ������Ʈ
    snake->setDirection(s_state); 
    
    
    //1.1 snake�� item�� �浹�ߴٸ�
    if (snake->isCollidingItem(item,s_state)) {
        snake->eatItem(item->getItemPower());//���� ����
        item->spawn(snake->getSnakeList()); //item ��ġ ������
    }
    //1.2 snake�� �ڽ��� ���� �浹�ߴٸ�
    if (snake->isCollidingSelf(s_state))
        snakeGame_running = 2;
    //1.3 snake�� ���� �浹�ߴٸ�
    if (snake->isColldingWall(s_state))
        snakeGame_running = 2;

    if (snakeGame_running != 2)
        snake->move();
    //�ð� ������Ʈ
    static Uint32 last_ticks = SDL_GetTicks(); // !�߿�! static ���� ������ ���� Ȯ�� �� ��.
    Uint32 current_ticks = SDL_GetTicks();

    time_ms_ += current_ticks - last_ticks;
    UpdateTimeTexture(time_ms_);	// ������Ʈ �� �ð�(time_ms_)�� ���ڷ� ��ȯ�� �� texture�� �����.
    

    last_ticks = current_ticks;
}

void SnakeGame::HandleEvents() {
    //std::cout << "handleEvents" << std::endl;
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (snakeGame_running == 2)
                break;
            //����Ű ������ ���� ������ Ǯ���� ��� �̵�
            if (event.key.keysym.sym == SDLK_LEFT) {
                s_state = 0; //���� ���� ���� LEFT
                stop = false;
                if(snakeGame_running==0)
                    snakeGame_running = 1;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                s_state = 1;
                stop = false;
                if (snakeGame_running == 0)
                    snakeGame_running = 1;
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                s_state = 2;
                stop = false;
                if (snakeGame_running == 0)
                    snakeGame_running = 1;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                s_state = 3;
                stop = false;
                if (snakeGame_running == 0)
                    snakeGame_running = 1;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (snakeGame_running == 2) {
                    Reset();
                }
                break;
            }
        }
    }
}

void SnakeGame::Reset() {
    //����Ű �ʱ�ȭ
    snakeGame_running = 0;
    stop = true;
    s_state = -1;//����Ű �� ����

    //�� ��ü ���� �ߴٰ� �����
    delete snake;
    snake = new Snake();
    //item ���ġ
    item->spawn(snake->getSnakeList());
    UpdateScoreTexture();

    //time �ʱ�ȭ
    time_ms_ = 0;
    UpdateTimeTexture(time_ms_);
}


SnakeGame::~SnakeGame() {
    //�̹��� �ؽ��� ����
    SDL_DestroyTexture(item_texture);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(bg_texture);
    //��Ʈ �ؽ��� ����
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(snake_length);
    SDL_DestroyTexture(snake_score);
    SDL_DestroyTexture(text_time);

}
