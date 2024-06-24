#include <iostream>

#include "ProjectileGame.h" 
#include "SDL_image.h"
#include "G2W.h"
#include "math.h"


extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern double g_timestep_s;

double ball_size = 0.11f;

ProjectileGame::ProjectileGame()
{
	g_flag_running = true;

	// Texture
	{
		SDL_Surface* ball_surface = IMG_Load("../../Resources/ball.png");
		ball_src_rectangle_.x = 0;
		ball_src_rectangle_.y = 0;
		ball_src_rectangle_.w = ball_surface->w;
		ball_src_rectangle_.h = ball_surface->h;

		ball_texture_ = SDL_CreateTextureFromSurface(g_renderer, ball_surface);
		SDL_FreeSurface(ball_surface);
	}

	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

	type = 1; //1�̸� ���� ũ�� 2�� ���� ����
	AddNewBall();
	
}



ProjectileGame::~ProjectileGame()
{
	SDL_DestroyTexture(ball_texture_);
}


void
ProjectileGame::AddNewBall() //�� �߰� �Լ� -> ����Ʈ �� �ο� �߰�
{
	
	balls_.push_back(Ball(ball_size/type, &room_));
	//1�̸� �״�� 2�� ��������
}


void
ProjectileGame::Update()
{

	// Update balls
	for (Ball& b : balls_)
	{
		b.Update(g_timestep_s);
	}
}

void 
ProjectileGame::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,255,255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	
	
	// Draw room_
	{
		SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);

		// Left Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
										G2W_Y(0), 
										G2W_X(room_.left_wall_x()),
										G2W_Y(room_.height()) );

		
		// Right Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.right_wall_x()),
										G2W_Y(0), 
										G2W_X(room_.right_wall_x()),
										G2W_Y(room_.height()) );

		// Top Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
										G2W_Y(room_.height()), 
										G2W_X(room_.right_wall_x()),
										G2W_Y(room_.height()) );

		// Bottom Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
										G2W_Y(0), 
										G2W_X(room_.right_wall_x()),
										G2W_Y(0) );

		// Fence
		SDL_RenderDrawLine(g_renderer, G2W_X( room_.vertical_fence_pos_x() ), 
										G2W_Y(0), 
										G2W_X( room_.vertical_fence_pos_x()  ),
										G2W_Y( room_.ground_height()+room_.vertical_fence_height() ) );
	}


	// Draw Balls
	for ( Ball &b : balls_ )
	{

		int ball_win_x = G2W_X(b.pos_x());
		int ball_win_y = G2W_Y(b.pos_y());

		double win_radius = G2W_Scale * b.radius();

		SDL_Rect dest_rect;
		dest_rect.w = (int)(2*win_radius);
		dest_rect.h = (int)(2*win_radius);
		dest_rect.x = (int)(ball_win_x - win_radius);
		dest_rect.y = (int)(ball_win_y - win_radius);

		SDL_RenderCopy(g_renderer, ball_texture_, &ball_src_rectangle_, &dest_rect);
		

	}

	// Draw prediction path
	DrawPredictionPath(balls_.back(), W2G_X(mouse_win_x_), W2G_Y(mouse_win_y_));

	// Draw the Guide Line 
	if (balls_.size() > 0)
	{
		SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 100);
		SDL_RenderDrawLine(g_renderer, G2W_X(balls_.back().pos_x()), 
										G2W_Y(balls_.back().pos_y()),
										mouse_win_x_, 
										mouse_win_y_ );
	}


	SDL_RenderPresent(g_renderer); // draw to the screen
}



void 
ProjectileGame::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;
		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_1) {
				type = 1;
			}
			if (event.key.keysym.sym == SDLK_2) {
				type = 2;
			}
			balls_.back().setRadius(ball_size/type); //������ �缳��
			balls_.back().Reset();//����� ����� �°� ��ġ ������

			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT )
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;

				
				double mouse_game_x = W2G_X(mouse_win_x_);
				double mouse_game_y = W2G_Y(mouse_win_y_);
				

				
				// Luanch
				if ( balls_.size() > 0)
				{
					// Guide Line Vector
					double guide_line_x = mouse_game_x - balls_.back().pos_x();
					double guide_line_y = mouse_game_y - balls_.back().pos_y();

					// Lauching Force
					double launcing_force_x = 8.0 * guide_line_x;
					double launcing_force_y = 8.0 * guide_line_y;

					// Launch
					balls_.back().Launch(launcing_force_x, launcing_force_y);


					// Add a new ball for the next
					AddNewBall();
				}
			}

		

		case SDL_MOUSEMOTION:
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;
				
			}
			break;

		default:
			break;
		}
	}
}

void ProjectileGame::DrawPredictionPath(Ball& ball, double target_x, double target_y) {

	// ���� ��� �׸���
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 100); // ���� ��� ���� ����
	
	//Launch
	//(���콺��ġ-�� ��ġ)=>�Ÿ�
	//8��� ���ؼ� ���� ����
	double initial_force_x = 8.0 * (target_x - ball.pos_x());
	double initial_force_y = 8.0 * (target_y - ball.pos_y());

	double dt = g_timestep_s;
	double prediction_time = 1.0; // ���� ��θ� �׸� �� �ð� (1�ʷ� ����)
	int num_steps = prediction_time / dt; // ���� ��θ� �׸� �� �ܰ� ��

	double coeff_of_friction = 0.25; // ���� ��� ���� (������ ������ ����)
	double coeff_of_restitution=ball.coeff_of_restitution(); // �ݹ߷� ��� ����

	// ���ӵ�
	double a[2];
	a[0] = 0;
	a[1] = room_.gravitational_acc_y();// Gravity

	// Move
	double p[2];
	p[0] = ball.pos_x();
	p[1] = ball.pos_y();

	// �ӵ�
	double v[2];
	v[0] = ball.vx()+ (initial_force_x / ball.mass());
	v[1] = ball.vy()+ (initial_force_y / ball.mass());

	double previous_p[2];
	previous_p[0] = p[0];
	previous_p[1] = p[1];

	// ���� ��� �׸���
	for (int i = 1; i <= num_steps; i++) {
		previous_p[0] = p[0];
		previous_p[1] = p[1];
		// Move
		p[0] += (dt) * v[0];
		p[1] += (dt) * v[1];

		// Collision with Ground �ٴ��̶� �浹
		if (p[1] - ball.radius() < room_.ground_height() && v[1] < 0)
		{
			p[1] = ball.radius() + room_.ground_height();

			v[1] = -1 * v[1];

			// Coefficient of restitution
			v[1] = coeff_of_restitution * v[1];
		}

		// Collision with Ceilling õ���̶� �浹
		else if (p[1] + ball.radius() > room_.height() && v[1] > 0)
		{
			p[1] = room_.height() - ball.radius();

			v[1] = -1 * v[1];

			// Coefficient of restitution
			v[1] = coeff_of_restitution * v[1];
		}

		// Collision with Left Wall ���� ���̶� �浹
		if (p[0] - ball.radius() < room_.left_wall_x() && v[0] < 0)
		{
			p[0] = room_.left_wall_x() + ball.radius();

			v[0] = -1 * v[0];

			// Coefficient of restitution
			v[0] = coeff_of_restitution * v[0];

		}
		// Collision with Right Wall ������ ���̶� �浹
		else if (p[0] + ball.radius() > room_.right_wall_x() && v[0] > 0)
		{
			p[0] = room_.right_wall_x() - ball.radius();

			v[0] = -1 * v[0];
			// Coefficient of restitution
			v[0] = coeff_of_restitution * v[0];
		}

		// �ٴڿ� ���� �� ������ ����
		if (p[1] - ball.radius() <= room_.ground_height())
		{
			// ������ ���
			double friction_force = coeff_of_friction * (ball.mass() * room_.gravitational_acc_y()); //������=�������x�Ʒ��� ���ϴ� ��=�������x����x�߷°��ӵ�
			double friction_acc = friction_force / ball.mass(); //��꿡 ������ ���ӵ� ���


			// �ӵ��� ������ ����
			if (v[0] > 0) //������ �̵� ��
			{
				v[0] = std::max(0.0, v[0] + friction_acc * dt); // �ӵ��� ����� �� ����
			}
			else if (v[0] < 0) //���� �̵� ��
			{
				v[0] = std::min(0.0, v[0] - friction_acc * dt); // �ӵ��� ������ �� ���� (���밪 ����)
			}

		}

		// �潺�� �浹 ó��
		
		bool hit_fence_x = false;
		bool hit_fence_y = false;

		// ���� �߽��� �潺 ���̺��� ���� ��
		if (p[1] - ball.radius() < room_.vertical_fence_height())
		{
			// ���� ���� ��ġ���� ���� ��ġ�� �̵��ϸ鼭 �潺�� ����ߴ��� Ȯ��
			bool passed_fence_x = (previous_p[0] - ball.radius() <= room_.vertical_fence_pos_x() && p[0] + ball.radius() >= room_.vertical_fence_pos_x()) ||
				(previous_p[0] + ball.radius() >= room_.vertical_fence_pos_x() && p[0] - ball.radius() <= room_.vertical_fence_pos_x());

			if (passed_fence_x)
			{
				if (previous_p[0] + ball.radius() <= room_.vertical_fence_pos_x() && p[0] + ball.radius() > room_.vertical_fence_pos_x() && v[0] > 0)
				{
					// ���� ���������� �̵��ϸ鼭 �潺�� ������� ��
					p[0] = room_.vertical_fence_pos_x() - ball.radius();
					v[0] = -v[0] * ball.coeff_of_restitution();
					hit_fence_x = true;
				}
				else if (previous_p[0] - ball.radius() >= room_.vertical_fence_pos_x() && p[0] - ball.radius() < room_.vertical_fence_pos_x() && v[0] < 0)
				{
					// ���� �������� �̵��ϸ鼭 �潺�� ������� ��
					p[0] = room_.vertical_fence_pos_x() + ball.radius();
					v[0] = -v[0] * ball.coeff_of_restitution();
					hit_fence_x = true;
				}
			}
		}

		// ���� �潺�� ���̿��� �浹�� ��
		if (p[1] - ball.radius() < room_.vertical_fence_height() && p[1] + ball.radius() > room_.vertical_fence_height())
		{
			if (hit_fence_x || (p[0] - ball.radius() < room_.vertical_fence_pos_x() && p[0] + ball.radius() > room_.vertical_fence_pos_x()))
			{
				if (previous_p[1] - ball.radius() >= room_.vertical_fence_height() && p[1] - ball.radius() < room_.vertical_fence_height() && v[1] < 0)
				{
					// ���� ������ �Ʒ��� �̵��ϸ鼭 �潺�� ������� ��
					p[1] = room_.vertical_fence_height() + ball.radius();
					v[1] = -v[1] * ball.coeff_of_restitution();
					hit_fence_y = true;
				}
			}
		}

		// �ӵ�
		v[0] += dt * a[0];
		v[1] += dt * a[1];

		

		// Draw
		int x1 = G2W_X(p[0]);
		int y1 = G2W_Y(p[1]);

		SDL_Rect rect;
		int rect_size = 6;
		rect.w = rect_size;
		rect.h = rect_size;
		rect.x = x1 - rect_size/2;
		rect.y = y1 - rect_size/2;

		SDL_RenderFillRect(g_renderer, &rect);
	}


}
