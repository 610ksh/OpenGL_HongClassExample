#pragma once
#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		RGB color;
		vec2 pos;

		void init(const RGB& _color, const vec2& _pos)
		{
			color = _color;
			pos = _pos;
		}

		// 자식들에서 구현(순수 가상 함수 사용)
		virtual void drawGeometry(const float& time) = 0;

		void Draw(const float& time = 0.0f)
		{
			beginTransformation();
			{
				translate(pos);

				// 현재 클래스에서 있는것처럼 보이게함. 실제로는 자식클래스 사용.
				drawGeometry(time);
			}
			endTransformation();
		}
	};
}