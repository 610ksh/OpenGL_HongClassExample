#pragma once

#include "Game2D.h"
#include "SoundEngine_Singleton.h"
#include "SoundEngine.h"

namespace jm
{
	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);

		/*
			사운드와 같은 모듈은 한번만 초기화되고, 그것을 공유하는 형태로 사용해야함.
			만약 여러개를 선언해서 사용하면, 예측불가능한 결과를 볼수도 있음.
		*/
		//SoundEngine* sound_engine; // 이런식으로 코딩하면 안됨.

		MyBullet()
		{
			SoundEngine_Singleton::getInstance()->playSound("missile");
		}

		~MyBullet()
		{
			SoundEngine_Singleton::getInstance()->stopSound("missile");
		}

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center += velocity * dt;
		}
	};

}
