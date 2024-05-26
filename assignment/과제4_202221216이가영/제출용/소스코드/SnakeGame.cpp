#define _CRT_SECURE_NO_WARNINGS
#include "SnakeGame.h"


extern int DASH_SPEED; // �뽬 �ӵ�
extern int NORMAL_SPEED; // �Ϲ� �ӵ�
extern Uint32 move_interval; // ���� �����̴� ����


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
    g_flag_running = true;
    
    //2. �ؽ��� �ҷ�����
    //2.1 Snake �ؽ��� �ҷ�����
    snake = new Snake();

    SDL_Surface* snakeHead_sheet_surface = IMG_Load("../../Resources/head.png");
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
    snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_sheet_surface);
    SDL_FreeSurface(snake_sheet_surface);//���� �ʼ�

    snake_source_rect.x = 0;
    snake_source_rect.y = 0;
    snake_source_rect.w = 512;
    snake_source_rect.h = 512;

    //2.2 ������ �ؽ��� �ҷ�����
    item = new Item(snake->getSnakeList());

    SDL_Surface* item_sheet_surface = IMG_Load("../../Resources/item.png");

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

    //2.3 monster �ؽ��� �ҷ�����
    // ���� ��ü ����
    for(int i = 0; i < 2; i++)
        monsterList.push_back(new Monster(snake->getSnakeList()));
    
    
    SDL_Surface* monster_sheet_surface = IMG_Load("../../Resources/monster.png");
    monster_texture = SDL_CreateTextureFromSurface(g_renderer, monster_sheet_surface);
    SDL_FreeSurface(monster_sheet_surface);//���� �ʼ�

    monster_destination_rect.w = GRID; //ũ�� 10*10
    monster_destination_rect.h = GRID;
    

    //2.3 background �ؽ��� �ҷ�����
    //��� �̹��� ����
    SDL_Surface* bg_sheet_surface = IMG_Load("../../Resources/background.png");
    bg_texture= SDL_CreateTextureFromSurface(g_renderer, bg_sheet_surface);
    SDL_FreeSurface(bg_sheet_surface);//���� �ʼ�
    bg_destination_rect.x = GRID;
    bg_destination_rect.y = GRID;
    bg_destination_rect.w = screenWidth-GRID*5;
    bg_destination_rect.h = screenHeight-GRID*2;
    
    //2.4 �Ͻ����� �ؽ��� ��������
    SDL_Surface* stop_sheet_surface = IMG_Load("../../Resources/stop.png");
    stop_texture = SDL_CreateTextureFromSurface(g_renderer, stop_sheet_surface);
    SDL_FreeSurface(stop_sheet_surface);//���� �ʼ�

    stop_destination_rect.w = GRID * 10; //ũ�� 10*10
    stop_destination_rect.h = GRID * 10;
    stop_destination_rect.x = (GRID + bg_destination_rect.w - stop_destination_rect.w) / 2;
    stop_destination_rect.y = (GRID + bg_destination_rect.h - stop_destination_rect.h) / 2;
    
    
    //3. ��Ʈ ��������
    //��Ʈ �ҽ� ȣ��
    fontK=TTF_OpenFont("../../Resources/establish Retrosans.ttf", 100);
    //3.1 ready �ؽ��� �����
    SDL_Surface * tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Ready", {255, 255, 255});
    read_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2;
    read_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    read_rect.w = tmp_surface->w;
    read_rect.h = tmp_surface->h;
    ready = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    
    //3.2 readme �ؽ���
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8">> �����Ϸ��� ����Ű�� ��������", { 80, 80,80 });
    readme_rect.x = read_rect.x+GRID;
    readme_rect.y = read_rect.y + GRID*7;
    readme_rect.w = tmp_surface->w /5;
    readme_rect.h = tmp_surface->h/5+2;
    readme = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.3 game over �ؽ��� �����
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"Game Over", { 0,0,0 });
    over_rect.x = (GRID+bg_destination_rect.w - tmp_surface->w) / 2+bg_destination_rect.x;
    over_rect.y = (GRID+bg_destination_rect.h - tmp_surface->h) / 2;
    over_rect.w = tmp_surface->w;
    over_rect.h = tmp_surface->h;
    over = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.4 score �ؽ���
    tmp_surface = TTF_RenderUTF8_Blended(fontK, u8"SCORE", { 255,255,255 });
    snake_score_rect.x = screenWidth - GRID * 3 - GRID / 2;
    snake_score_rect.y = GRID;
    snake_score_rect.w = GRID*3;
    snake_score_rect.h = GRID*2;
    snake_score = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);

    //3.5 �� ���� ���� ��� �ؽ���
    UpdateScoreTexture();
    

    //3. ����Ű �ʱ�ȭ
    snakeGame_running = 0;
    stop = true;
    s_state = -1;//����Ű �� ����
    //4. �ð� �ʱ�ȭ
    time_ms_ = 0;
    //UpdateTimeTexture(time_ms_);
    SDL_SetTextureBlendMode(bg_texture, SDL_BLENDMODE_BLEND);
    monsterCollisionTime = 0;
    //lastMonsterAddedTime = SDL_GetTicks(); // ���� ����
    
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
    
    //// ���� �׸���
    for(auto& monster : monsterList){
		monster_destination_rect.x = monster->getX(); // �׷��� ��ǥ ����
		monster_destination_rect.y = monster->getY();
		SDL_RenderCopy(g_renderer, monster_texture, NULL, &monster_destination_rect);
	}
    

    //// 3. �� �׸���
    //�浹 ���η� ���� ����
    // ���� ���Ϳ� �浹���� ��� ���� ������� �׸��ϴ�.

    auto snakeList = snake->getSnakeList();
    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->x; // �׷��� ��ǥ ����
        snake_destination_rect.y = (*it)->y;

        // ���� ��� ����� ��쿡�� ��� �̹����� ����ϰ�, �׷��� ���� ��쿡�� ������ �� �̹����� ����մϴ�.
        if (it == snakeList.begin()) {
            int angle = 0;
            switch (s_state) {
            case 0://��
                angle = -90;
                break;
            case 1://��
                angle = 90;
                break;
            case -1:
            case 2://��
                angle = 0;
                break;
            case 3://�Ʒ�
                angle = 180;
                break;
            default:
                break;
            }

            SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }
        else {
            
            SDL_RenderCopy(g_renderer, snake_texture, NULL, &snake_destination_rect);
        }
    }
    //���� ����
    SDL_SetTextureColorMod(snakeHead_texture, 255, 255, 255);
    SDL_SetTextureColorMod(snake_texture, 255, 255, 255);

    if (snakeGame_running != 1) {
        SDL_SetTextureAlphaMod(bg_texture, 127); // 50% ������
        SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);
        SDL_SetTextureAlphaMod(bg_texture, 255);
    }
    
    //���� �ؽ���
    UpdateScoreTexture();
    SDL_RenderCopy(g_renderer, snake_score, NULL, &snake_score_rect);
    SDL_RenderCopy(g_renderer, snake_length, NULL, &snake_length_rect);

    if (snakeGame_running == 0) {
        SDL_RenderCopy(g_renderer, ready, NULL, &read_rect);
        SDL_RenderCopy(g_renderer, readme, NULL, &readme_rect);
    }else if(snakeGame_running == 2) {
        SDL_RenderCopy(g_renderer, over, NULL, &over_rect);
    }
    else if (snakeGame_running==3) {
        SDL_RenderCopy(g_renderer, stop_texture, NULL, &stop_destination_rect);
    }
    
    
    UpdateTimeTexture(time_ms_);
    SDL_RenderCopy(g_renderer, text_time, NULL, &text_time_rect);
    

    SDL_RenderPresent(g_renderer);
}

void SnakeGame::Update() {
    //std::cout << "update" << std::endl;
    if (snakeGame_running == 0 || snakeGame_running==2 || snakeGame_running == 3) // ���� ����Ű�� �� ���� ��Ȳ�̶�� ������Ʈ �� ��
        return;
    //1. snake & item ������Ʈ
    snake->setDirection(s_state); 

    //���� �߰�����
    Uint32 currentTime = SDL_GetTicks(); // ���� �ð��� �����ɴϴ�.
    // 30��(30000�и���)�� �������� Ȯ���մϴ�.
    if (currentTime - lastMonsterAddedTime >= 30000 && monsterList.size()<20) {
        // 30�ʰ� �����ٰ� 20���� �ȵȴٸ� ���ο� ���͸� �߰��մϴ�.
        Monster* newMonster = new Monster(snake->getSnakeList());
        monsterList.push_back(newMonster);
        lastMonsterAddedTime = currentTime; // ���͸� �߰��� �ð��� ������Ʈ�մϴ�.
    }
    
    //1.1 snake�� item�� �浹�ߴٸ�
    if (snake->isCollidingItem(item,s_state)) {
        snake->eatItem(item->getItemPower());//���� ����
        item->spawn(snake->getSnakeList()); //item ��ġ ������
    }
    //1.2 snake�� �ڽ��� ���� �浹�ߴٸ�
    if (snake->isCollidingSelf(s_state))
        snakeGame_running = 2;
    //1.3 snake�� ���� �浹�ߴٸ�
    if (snake->isCollidingWall(s_state))
        snakeGame_running = 2;


    for (const auto& monster : monsterList)
        monster->move();
    
    // ���� ������ ������Ʈ �Ŀ� �浹�� Ȯ���մϴ�.
    int flag = false; //�ߺ� �浹�Ǵ� ����
    for (const auto& monster : monsterList) {
        if (snake->isCollidingMonster(monster, s_state)) {
            snakeGame_running = 2;
            flag = true;
            break;
        }
    }

    if (snakeGame_running == 1) {
        snake->move();

        //�ð� ������Ʈ
        
        Uint32 current_ticks = SDL_GetTicks();
        time_ms_ += current_ticks - last_ticks_;
        UpdateTimeTexture(time_ms_);	// ������Ʈ �� �ð�(time_ms_)�� ���ڷ� ��ȯ�� �� texture�� �����.

        last_ticks_ = current_ticks;
    }

    //���� �浹 üũ
    if (!flag) {
        for (const auto& monster : monsterList) {
            if (snake->isCollidingMonster(monster, s_state)) {
                snakeGame_running = 2;
                break;
            }
        }
    }
    
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
            if (snakeGame_running == 2) //�׾����� Ű �̺�Ʈ �� ����
                break;

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (snakeGame_running == 1) {//���� ���� ���̾����� �Ͻ�������
                    snakeGame_running = 3;
                    // �Ͻ������� ������ �� �ð��� ������Ʈ�մϴ�.
                    Uint32 current_ticks = SDL_GetTicks();
                    time_ms_ += current_ticks - last_ticks_;
                    pauseStartTime = SDL_GetTicks();
                }
                else if (snakeGame_running == 3) {//�Ͻ����������� ���� ������
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks(); 
                    lastMonsterAddedTime += SDL_GetTicks() - pauseStartTime; // �Ͻ����� �ð���ŭ �����ݴϴ�.
                }
            }
            if (snakeGame_running == 3) //�Ͻ����� ���̸� Ű �̺�Ʈ �� ����
                break;

            /////����Ű �ٿ�
            //����Ű ������ ���� ������ Ǯ���� ��� �̵�
            if (event.key.keysym.sym == SDLK_LEFT) {
                s_state = 0; //���� ���� ���� LEFT
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // ���� ����
                }
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                s_state = 1;
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // ���� ����
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                s_state = 2;
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // ���� ����
                }
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                s_state = 3;
                stop = false;
                if (snakeGame_running == 0) {
                    snakeGame_running = 1;
                    last_ticks_ = SDL_GetTicks();
                    lastMonsterAddedTime = SDL_GetTicks(); // ���� ����
                }
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
    //���� ��ü ���� �ߴٰ� �����
    for (const auto& mon : monsterList) {
        delete mon;
    }
    monsterList.clear(); // ���� ����Ʈ�� ���ϴ�.

    

    for (int i = 0;i < 2;i++) {
        monsterList.push_back(new Monster(snake->getSnakeList()));
    }
    

    //item ���ġ
    item->spawn(snake->getSnakeList());
    UpdateScoreTexture();

    //time �ʱ�ȭ
    time_ms_ = 0;
    
    UpdateTimeTexture(time_ms_);
    //lastMonsterAddedTime = SDL_GetTicks(); // ���� ����
}


SnakeGame::~SnakeGame() {
    //�̹��� �ؽ��� ����
    SDL_DestroyTexture(item_texture);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(monster_texture);
    SDL_DestroyTexture(stop_texture);

    //��Ʈ �ؽ��� ����
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(readme);
    SDL_DestroyTexture(snake_length);
    SDL_DestroyTexture(snake_score);
    SDL_DestroyTexture(text_time);
    

    // ���� ��ü ����
    for (const auto& monster : monsterList) {
        delete monster;
    }
    monsterList.clear(); // ���� ����Ʈ�� ���ϴ�.


    delete item;
    delete snake;
}
