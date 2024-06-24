
#include "Ball.h"
#include "SDL_image.h"
#include <iostream>




Ball::Ball(double radius, Room *room) //radius �Ѱܹޱ�
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
Ball::Reset() //�� ��ġ�� �ӵ� �ʱ�ȭ
{
	p_[0] = radius_ + room_->left_wall_x();
	p_[1] = radius_;

	v_[0] = 0; //x�� �ӵ�
	v_[1] = 0; //y�� �ӵ�
}

void
Ball::Launch(double initial_force_x, double initial_force_y) //�ʱ� ������ �� �߻�
{
	v_[0] = v_[0] + (initial_force_x/mass_);
	v_[1] = v_[1] + (initial_force_y/mass_);
}

void 
Ball::Update(double timestep_s)
{
	double dt = timestep_s;	// seconds

	double coeff_of_friction = 0.25; // ���� ��� ���� (������ ������ ����)

	// ���ӵ�
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	double previous_p[2];
	previous_p[0] = p_[0];
	previous_p[1] = p_[1];

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];


	// Collision with Ground �ٴ��̶� �浹
	if ( p_[1]-radius_ < room_->ground_height() && v_[1] < 0 ) 
	{
		p_[1] = radius_ + room_->ground_height();

		v_[1] = -1*v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Ceilling õ���̶� �浹
	else if ( p_[1]+radius_ > room_->height() && v_[1] > 0 ) 
	{
		p_[1] = room_->height() - radius_;

		v_[1] = -1*v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Left Wall ���� �� �浹
	if ( p_[0] - radius_ < room_->left_wall_x() && v_[0] < 0 )
	{
		p_[0] = room_->left_wall_x() + radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	// Collision with Right Wall ������ �� �浹
	else if (p_[0] + radius_ > room_->right_wall_x() && v_[0] > 0)
	{
		p_[0] = room_->right_wall_x() - radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	
	// �ٴڿ� ���� �� ������ ����
	if (p_[1] - radius_ <= room_->ground_height())
	{
		// ������ ���
		double friction_force = coeff_of_friction * (mass_ * room_->gravitational_acc_y()); //������=�������x�Ʒ��� ���ϴ� ��=�������x����x�߷°��ӵ�
		double friction_acc = friction_force / mass_; //��꿡 ������ ���ӵ� ���
		

		// �ӵ��� ������ ����
		if (v_[0]>  0) //������ �̵� ��
		{
			v_[0] = std::max(0.0, v_[0] + friction_acc * dt); // �ӵ��� ����� �� ����
		}
		else if (v_[0] < 0) //���� �̵� ��
		{
			v_[0] = std::min(0.0, v_[0] - friction_acc * dt); // �ӵ��� ������ �� ���� (���밪 ����)
		}
		
	}

	// �潺�� �浹 ó��
	bool hit_fence_x = false;
	bool hit_fence_y = false;

	// ���� �߽��� �潺 ���̺��� ���� ��
	if (p_[1] - radius_ < room_->vertical_fence_height())
	{
		// ���� ���� ��ġ���� ���� ��ġ�� �̵��ϸ鼭 �潺�� ����ߴ��� Ȯ��
		bool passed_fence_x = (previous_p[0] - radius_ <= room_->vertical_fence_pos_x() && p_[0] + radius_ >= room_->vertical_fence_pos_x()) ||
			(previous_p[0] + radius_ >= room_->vertical_fence_pos_x() && p_[0] - radius_ <= room_->vertical_fence_pos_x());

		if (passed_fence_x)
		{
			if (previous_p[0] + radius_ <= room_->vertical_fence_pos_x() && p_[0] + radius_ > room_->vertical_fence_pos_x() && v_[0] > 0)
			{
				// ���� ���������� �̵��ϸ鼭 �潺�� ������� ��
				p_[0] = room_->vertical_fence_pos_x() - radius_;
				v_[0] = -v_[0] * coeff_of_restitution_;
				hit_fence_x = true;
			}
			else if (previous_p[0] - radius_ >= room_->vertical_fence_pos_x() && p_[0] - radius_ < room_->vertical_fence_pos_x() && v_[0] < 0)
			{
				// ���� �������� �̵��ϸ鼭 �潺�� ������� ��
				p_[0] = room_->vertical_fence_pos_x() + radius_;
				v_[0] = -v_[0] * coeff_of_restitution_;
				hit_fence_x = true;
			}
		}
	}

	// ���� �潺�� ���̿��� �浹�� ��
	if (p_[1] - radius_ < room_->vertical_fence_height() && p_[1] + radius_ > room_->vertical_fence_height())
	{
		if (hit_fence_x || (p_[0] - radius_ < room_->vertical_fence_pos_x() && p_[0] + radius_ > room_->vertical_fence_pos_x()))//
		{
			//if (previous_p[1] + radius_ <= room_->vertical_fence_height() && p_[1] + radius_ > room_->vertical_fence_height() && v_[1] > 0)
			//{
			//	// ���� �Ʒ����� ���� �̵��ϸ鼭 �潺�� ������� ��
			//	p_[1] = room_->vertical_fence_height() - radius_;
			//	v_[1] = -v_[1] * coeff_of_restitution_;
			//	hit_fence_y = true;
			//}
			if (previous_p[1] - radius_ >= room_->vertical_fence_height() && p_[1] - radius_ < room_->vertical_fence_height() && v_[1] < 0)
			{
				// ���� ������ �Ʒ��� �̵��ϸ鼭 �潺�� ������� ��
				p_[1] = room_->vertical_fence_height() + radius_;
				v_[1] = -v_[1] * coeff_of_restitution_;
				hit_fence_y = true;
			}
		}
	}
	// ���� �潺�� ���̺��� ���� ��
	// -> �ƹ��͵� ����

	
	


	//�ӵ� = �����ӵ� + �ð�(dt) * ���ӵ�;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
}


//radius setter
void Ball::setRadius(double radius) {
	radius_ = radius;
}

//mass setter
void Ball::setMass(double mass) { //ũ�� ���� �پ�� �� ������ �ٲ��� �ϳ�?
	mass_ = mass;
}