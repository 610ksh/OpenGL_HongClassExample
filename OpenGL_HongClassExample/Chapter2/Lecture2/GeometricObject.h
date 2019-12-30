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

		// �ڽĵ鿡�� ����(���� ���� �Լ� ���)
		virtual void drawGeometry(const float& time) = 0;

		void Draw(const float& time = 0.0f)
		{
			beginTransformation();
			{
				translate(pos);

				// ���� Ŭ�������� �ִ°�ó�� ���̰���. �����δ� �ڽ�Ŭ���� ���.
				drawGeometry(time);
			}
			endTransformation();
		}
	};
}