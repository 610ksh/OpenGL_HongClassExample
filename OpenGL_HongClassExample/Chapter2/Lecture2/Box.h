#pragma once
// 부모 클래스 헤더 추가
#include "GeometricObject.h"

namespace jm
{
	class Box : public GeometricObject
	{
	public:
		float width, height;
		float angle;

		void init(const RGB& _color, const vec2& _pos, const float& _width, const float& _height, const float& _angle)
		{
			/*color = _color;
			pos = _pos;*/
			// 위와같이 직접하지 않고, 부모 생성자를 호출하는 방식으로 해결
			GeometricObject::init(_color, _pos);

			angle = _angle;

			width = _width;
			height = _height;
		}

		// 그런데 이거 깜빡하고 안만들고 실행해도 에러가 안뜸.
		// 에러뜨게 하려면, 가상함수를 순수가상함수로 만들어줘서 에러가 나오게해야함.
		// virtual void drawGeometry() = 0; // 바디가 없음.
		void drawGeometry(const float& time) override // by 방어적 프로그래밍
		{
			rotate(time*90.0f);
			beginTransformation();
			{
				rotate(angle);
				drawFilledBox(Colors::blue, width, height);
			}
			endTransformation();
		}

	};
}
