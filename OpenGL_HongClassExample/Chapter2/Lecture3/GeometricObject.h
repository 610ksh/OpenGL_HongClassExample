#pragma once
#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		vec2 pos;
		RGB  color;

		// unique_ptr에서는 가상소멸자를 사용하는게 안전
		virtual ~GeometricObject()
		{

		}

		void init(const RGB & _color, const vec2 & _pos)
		{
			color = _color;
			pos = _pos;
		}

		virtual void drawGeometry() const = 0;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawGeometry();
			}
			endTransformation();
		}
	};
}