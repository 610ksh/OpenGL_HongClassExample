#pragma once
// 부모 클래스 헤더 추가
#include "GeometricObject.h"

namespace jm
{
	class Circle : public GeometricObject
	{
	public:
		//vec2 pos = vec2{ 0.0f, 0.0f };
		//RGB color = Colors::red;
		//float size = 0.15f;

		/*void Draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawGeometry();
			}
			endTransformation();
		}*/

		float size;

		void init(const RGB& _color, const vec2& _pos, const float& _size)
		{
			/*color = _color;
			pos = _pos;*/
			// 위와같이 직접하지 않고, 부모 생성자를 호출하는 방식으로 해결
			GeometricObject::init(_color, _pos);

			size = _size;
		}


		void drawGeometry(const float& time) override // by 방어적 프로그래밍
		{
			rotate(time*90.0f);
			drawFilledCircle(color, size);
		}
	};
}