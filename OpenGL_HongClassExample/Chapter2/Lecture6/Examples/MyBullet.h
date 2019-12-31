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
			����� ���� ����� �ѹ��� �ʱ�ȭ�ǰ�, �װ��� �����ϴ� ���·� ����ؾ���.
			���� �������� �����ؼ� ����ϸ�, �����Ұ����� ����� ������ ����.
		*/
		//SoundEngine* sound_engine; // �̷������� �ڵ��ϸ� �ȵ�.

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
