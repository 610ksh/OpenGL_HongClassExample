#pragma once
// 부모 클래스 헤더 추가
#include "GeometricObject.h"

namespace jm
{
	class Triangle : public GeometricObject
	{
	public:
		//vec2 pos = vec2{ -0.5f, -0.05f };
		//RGB color = Colors::yellow;
		//float size = 0.3f;

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
		float angle;

		void init(const RGB& _color, const vec2& _pos, const float& _size, const float& _angle)
		{
			/*color = _color;
			pos = _pos;*/
			// 위와같이 직접하지 않고, 부모 생성자를 호출하는 방식으로 해결
			GeometricObject::init(_color, _pos);

			angle = _angle;
			size = _size;
		}

		void drawGeometry(const float& time) override // by 방어적 프로그래밍
		{
			rotate(time*90.0f);
			beginTransformation();
			{
				rotate(angle);
				drawFilledTriangle(color, size);
			}
			endTransformation();
		}
	};
}
