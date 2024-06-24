
#include "Ball.h"
#include "SDL_image.h"
#include <iostream>




Ball::Ball(double radius, Room *room) //radius 넘겨받기
{
	room_ = room;
	radius_ = radius; //radius

	
	v_[0] = 0;
	v_[1] = 0;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	Reset();
}

void
Ball::Reset() //공 위치랑 속도 초기화
{
	p_[0] = radius_ + room_->left_wall_x();
	p_[1] = radius_;

	v_[0] = 0; //x축 속도
	v_[1] = 0; //y축 속도
}

void
Ball::Launch(double initial_force_x, double initial_force_y) //초기 힘으로 공 발사
{
	v_[0] = v_[0] + (initial_force_x/mass_);
	v_[1] = v_[1] + (initial_force_y/mass_);
}

void 
Ball::Update(double timestep_s)
{
	double dt = timestep_s;	// seconds

	double coeff_of_friction = 0.25; // 마찰 계수 설정 (적절한 값으로 설정)

	// 가속도
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	double previous_p[2];
	previous_p[0] = p_[0];
	previous_p[1] = p_[1];

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];


	// Collision with Ground 바닥이랑 충돌
	if ( p_[1]-radius_ < room_->ground_height() && v_[1] < 0 ) 
	{
		p_[1] = radius_ + room_->ground_height();

		v_[1] = -1*v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Ceilling 천장이랑 충돌
	else if ( p_[1]+radius_ > room_->height() && v_[1] > 0 ) 
	{
		p_[1] = room_->height() - radius_;

		v_[1] = -1*v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Left Wall 왼쪽 벽 충돌
	if ( p_[0] - radius_ < room_->left_wall_x() && v_[0] < 0 )
	{
		p_[0] = room_->left_wall_x() + radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	// Collision with Right Wall 오른쪽 벽 충돌
	else if (p_[0] + radius_ > room_->right_wall_x() && v_[0] > 0)
	{
		p_[0] = room_->right_wall_x() - radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	
	// 바닥에 있을 때 마찰력 적용
	if (p_[1] - radius_ <= room_->ground_height())
	{
		// 마찰력 계산
		double friction_force = coeff_of_friction * (mass_ * room_->gravitational_acc_y()); //마찰력=마찰계수x아래로 향하는 힘=마찰계수x질량x중력가속도
		double friction_acc = friction_force / mass_; //계산에 적용할 가속도 계산
		

		// 속도에 마찰력 적용
		if (v_[0]>  0) //오른쪽 이동 중
		{
			v_[0] = std::max(0.0, v_[0] + friction_acc * dt); // 속도가 양수일 때 감소
		}
		else if (v_[0] < 0) //왼쪽 이동 중
		{
			v_[0] = std::min(0.0, v_[0] - friction_acc * dt); // 속도가 음수일 때 증가 (절대값 감소)
		}
		
	}

	// 펜스와 충돌 처리
	bool hit_fence_x = false;
	bool hit_fence_y = false;

	// 공의 중심이 펜스 높이보다 낮을 때
	if (p_[1] - radius_ < room_->vertical_fence_height())
	{
		// 공이 이전 위치에서 현재 위치로 이동하면서 펜스를 통과했는지 확인
		bool passed_fence_x = (previous_p[0] - radius_ <= room_->vertical_fence_pos_x() && p_[0] + radius_ >= room_->vertical_fence_pos_x()) ||
			(previous_p[0] + radius_ >= room_->vertical_fence_pos_x() && p_[0] - radius_ <= room_->vertical_fence_pos_x());

		if (passed_fence_x)
		{
			if (previous_p[0] + radius_ <= room_->vertical_fence_pos_x() && p_[0] + radius_ > room_->vertical_fence_pos_x() && v_[0] > 0)
			{
				// 공이 오른쪽으로 이동하면서 펜스를 통과했을 때
				p_[0] = room_->vertical_fence_pos_x() - radius_;
				v_[0] = -v_[0] * coeff_of_restitution_;
				hit_fence_x = true;
			}
			else if (previous_p[0] - radius_ >= room_->vertical_fence_pos_x() && p_[0] - radius_ < room_->vertical_fence_pos_x() && v_[0] < 0)
			{
				// 공이 왼쪽으로 이동하면서 펜스를 통과했을 때
				p_[0] = room_->vertical_fence_pos_x() + radius_;
				v_[0] = -v_[0] * coeff_of_restitution_;
				hit_fence_x = true;
			}
		}
	}

	// 공이 펜스의 높이에서 충돌할 때
	if (p_[1] - radius_ < room_->vertical_fence_height() && p_[1] + radius_ > room_->vertical_fence_height())
	{
		if (hit_fence_x || (p_[0] - radius_ < room_->vertical_fence_pos_x() && p_[0] + radius_ > room_->vertical_fence_pos_x()))//
		{
			//if (previous_p[1] + radius_ <= room_->vertical_fence_height() && p_[1] + radius_ > room_->vertical_fence_height() && v_[1] > 0)
			//{
			//	// 공이 아래에서 위로 이동하면서 펜스를 통과했을 때
			//	p_[1] = room_->vertical_fence_height() - radius_;
			//	v_[1] = -v_[1] * coeff_of_restitution_;
			//	hit_fence_y = true;
			//}
			if (previous_p[1] - radius_ >= room_->vertical_fence_height() && p_[1] - radius_ < room_->vertical_fence_height() && v_[1] < 0)
			{
				// 공이 위에서 아래로 이동하면서 펜스를 통과했을 때
				p_[1] = room_->vertical_fence_height() + radius_;
				v_[1] = -v_[1] * coeff_of_restitution_;
				hit_fence_y = true;
			}
		}
	}
	// 공이 펜스의 높이보다 높을 때
	// -> 아무것도 안함

	
	


	//속도 = 이전속도 + 시간(dt) * 가속도;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
}


//radius setter
void Ball::setRadius(double radius) {
	radius_ = radius;
}

//mass setter
void Ball::setMass(double mass) { //크기 절반 줄어들 때 질량도 바뀌어야 하나?
	mass_ = mass;
}