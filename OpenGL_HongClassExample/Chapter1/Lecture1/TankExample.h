#pragma once

#include "Game2D.h"

// �Ѿ� ������
#define BULLET_SIZE 50

namespace jm
{
	///////////////////////////////////////////////////////////////////////
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f); // ���� ��ġ
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f); //���� �����Ϸ���

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	///////////////////////////////////////////////////////////////////////

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f); // �Ѿ���ġ
		vec2 velocity = vec2(0.0f, 0.0f); // �ӵ�
		bool isActive = false;

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8); //�Ѿ� ��ü
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8); //�Ѿ� �׵θ�
			endTransformation();
		}

		// �Ѿ��� ��ġ�� �ٲ��ִ� �Լ�
		void update(const float& dt)
		{
			center += velocity * dt;
		}
	};

	///////////////////////////////////////////////////////////////////////

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		MyBullet* bullet = nullptr; // �߻簡 �Ǿ������� ������
		//TODO: allow multiple bullets
		MyBullet bullet2[BULLET_SIZE];
		int bulletNum = 0;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		// �Ҹ���
		~TankExample()
		{
			if (bullet != nullptr) delete bullet;
		}

		void update() override
		{
			/// Ű �Է� ���� �ڵ�� ������ �ݹ��Լ��� �� ���� ���ȴ�.
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE)) // �����ٰ� ������
			{
				/*if (bullet == nullptr)
				{
					bullet = new MyBullet;
					bullet->velocity = vec2(2.0f, 0.0f);
				}
				bullet->center = tank.center;
				bullet->center.x += 0.2f;
				bullet->center.y += 0.1f;*/
				if (bulletNum == BULLET_SIZE)
				{
					bulletNum = 0;
				}
				bullet2[bulletNum].center = tank.center;
				bullet2[bulletNum].center.x += 0.2f;
				bullet2[bulletNum].center.y += 0.1f;
				bullet2[bulletNum].velocity = vec2(2.0f, 0.0f);
				bullet2[bulletNum].isActive = true;
				bulletNum++;
			}

			// ��� �Ѿ� ����
			for (int i = 0; i < BULLET_SIZE; ++i)
			{
				// �̹� �����ϴ� �Ѿ��� �ִٸ�
				if (bullet2[i].isActive)
				{
					if (bullet2[i].center.x<1.5 && bullet2[i].center.x>-1.5f
						&& bullet2[i].center.y<1.5f && bullet2[i].center.y>-1.5f)
					{
						bullet2[i].update(getTimeStep());
						bullet2[i].draw();
					}
					else
					{
						bullet2[i].isActive = false;
					}
				}
			}
			
			// �Ѿ� ��ġ ������Ʈ
			//if (bullet != nullptr) bullet->update(getTimeStep());
			
			// �Ѿ� ���� ���� ����
			//if (bullet != nullptr)
			//{
			//	if (bullet->center.x > 1.0f || bullet->center.x < -1.0f
			//		|| bullet->center.y > 1.0f || bullet->center.y < -1.0f)
			//	{
			//		std::cout << "������" << std::endl;
			//		delete bullet;
			//		bullet = nullptr; // �̰� �ݵ�� �������. delete���� �� �߿���
			//		std::cout << "���ſϷ�" << std::endl;
			//	}
			//	else
			//	{
			//		std::cout << "���ư��� ��" << std::endl;
			//	}
			//}

			// �Ѿ� �׸���
			//if (bullet != nullptr) bullet->draw();
			
			// rendering
			tank.draw();

		}
	};
}