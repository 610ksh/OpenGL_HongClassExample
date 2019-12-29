#pragma once

#include "Game2D.h"

// 총알 사이즈
#define BULLET_SIZE 50

namespace jm
{
	///////////////////////////////////////////////////////////////////////
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f); // 현재 위치
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f); //방향 조절하려면

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
		vec2 center = vec2(0.0f, 0.0f); // 총알위치
		vec2 velocity = vec2(0.0f, 0.0f); // 속도
		bool isActive = false;

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8); //총알 본체
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8); //총알 테두리
			endTransformation();
		}

		// 총알의 위치를 바꿔주는 함수
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

		MyBullet* bullet = nullptr; // 발사가 되었을때만 존재함
		//TODO: allow multiple bullets
		MyBullet bullet2[BULLET_SIZE];
		int bulletNum = 0;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		// 소멸자
		~TankExample()
		{
			if (bullet != nullptr) delete bullet;
		}

		void update() override
		{
			/// 키 입력 여부 코드는 실제로 콜백함수가 더 많이 사용된다.
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE)) // 눌렀다가 뗐을때
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

			// 모든 총알 조사
			for (int i = 0; i < BULLET_SIZE; ++i)
			{
				// 이미 존재하는 총알이 있다면
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
			
			// 총알 위치 업데이트
			//if (bullet != nullptr) bullet->update(getTimeStep());
			
			// 총알 생존 범위 조사
			//if (bullet != nullptr)
			//{
			//	if (bullet->center.x > 1.0f || bullet->center.x < -1.0f
			//		|| bullet->center.y > 1.0f || bullet->center.y < -1.0f)
			//	{
			//		std::cout << "제거중" << std::endl;
			//		delete bullet;
			//		bullet = nullptr; // 이거 반드시 해줘야함. delete보다 더 중요함
			//		std::cout << "제거완료" << std::endl;
			//	}
			//	else
			//	{
			//		std::cout << "날아가는 중" << std::endl;
			//	}
			//}

			// 총알 그리기
			//if (bullet != nullptr) bullet->draw();
			
			// rendering
			tank.draw();

		}
	};
}