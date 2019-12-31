#pragma once

#include "Game2D.h"
#include "MyBullet.h"
#include "MyTank.h"
//#include "SoundEngine.h"
#include "SoundEngine_Singleton.h"

namespace jm
{
	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		MyBullet *bullet = nullptr;
		//TODO: allow multiple bullets
		//TODO: delete bullets when they go out of the screen

		//SoundEngine sound_engine; // 생성자가 private이면 컴파일 에러

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			// singleton을 사용해야하는 곳에서 getInstance()를 통해 받아옴
			auto & sound_engine = *SoundEngine_Singleton::getInstance();

			sound_engine.createSound("drumloop.wav", "background_music", true);
			sound_engine.createSound("truck_idle_off_02.wav", "tank_move", true);
			sound_engine.createSound("cannon1.wav", "cannon", false);
			sound_engine.createSound("missile.mp3", "missile", false);

			sound_engine.playSound("background_music");
		}

		~TankExample()
		{
			if(bullet != nullptr) delete bullet;
		}

		void update() override
		{
			// singleton을 사용해야하는 곳에서 getInstance()를 통해 받아옴
			auto & sound_engine = *SoundEngine_Singleton::getInstance(); // 레퍼런스로 받을때는 포인터로 받아야한다 (*)

			// move tank
			bool is_moving = false;

			if (isKeyPressed(GLFW_KEY_LEFT)) {
				tank.moveLeft(getTimeStep());
				is_moving = true;
			}

			if (isKeyPressed(GLFW_KEY_RIGHT)) {
				tank.moveRight(getTimeStep());
				is_moving = true;
			}

			if (isKeyPressed(GLFW_KEY_UP)) {
				tank.moveUp(getTimeStep());
				is_moving = true;
			}

			if (isKeyPressed(GLFW_KEY_DOWN)) {
				tank.moveDown(getTimeStep());
				is_moving = true;
			}

			if(is_moving)
				sound_engine.playSound("tank_move");
			else
				sound_engine.stopSound("tank_move");

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				if (bullet != nullptr) delete bullet;

				bullet = new MyBullet;
				bullet->center = tank.center;
				bullet->center.x += 0.2f;
				bullet->center.y += 0.1f;
				bullet->velocity = vec2(2.0f, 0.0f);

				sound_engine.stopSound("cannon");
				sound_engine.playSound("cannon");				
			}

			if (bullet != nullptr) bullet->update(getTimeStep());

			// rendering
			tank.draw();
			if (bullet != nullptr) bullet->draw();
		}
	};
}