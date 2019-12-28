#pragma once

#include "Game2D.h"
/* 
	※ 태양 : 별 / 지구 : 파란 원 / 달 : 작은 원

	1. 지구가 태양 주위를 공전하고
	2. 달이 지구 주위를 공전하고
	3. 태양이 자전하도록 만들기
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

				// 아래의 translate가 되기 전의 점이 기준점이됨. 위의 (0.5f, 0.0f)

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