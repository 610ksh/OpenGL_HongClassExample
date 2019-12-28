#pragma once

#include "Game2D.h"
/* 
	�� �¾� : �� / ���� : �Ķ� �� / �� : ���� ��

	1. ������ �¾� ������ �����ϰ�
	2. ���� ���� ������ �����ϰ�
	3. �¾��� �����ϵ��� �����
*/

namespace jm
{
	class SolarSystem : public Game2D
	{
		float time = 0.0f;
		/*vec2 a(0.0f, 0.0f);
		vec2 b = Vector2<float>(0.5f, 0);
		vec2 c = Vector2<float>(0.7f, 0);*/
	public:
		void update() override
		{
			beginTransformation();
			{
				beginTransformation();
				rotate(time*45.0f);
				drawFilledStar(Colors::gold, 0.2f, 0.13f);	// Sun
				endTransformation();
				
				//beginTransformation();
				rotate(time*45.0f);
				translate(0.5f, 0.0f);
				drawFilledStar(Colors::blue, 0.2f, 0.13f);
				//drawFilledCircle(Colors::blue, 0.1f);		// Earth
				//endTransformation();

				// �Ʒ��� translate�� �Ǳ� ���� ���� �������̵�. ���� (0.5f, 0.0f)

				rotate(time*180.0f);
				translate(0.2f, 0.0f);
				drawFilledStar(Colors::green, 0.2f, 0.13f);
				//drawFilledCircle(Colors::green, 0.05f);	// Moon
			}
			endTransformation();

			time += this->getTimeStep();

		}
	};
}