#pragma once
// �θ� Ŭ���� ��� �߰�
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
			// ���Ͱ��� �������� �ʰ�, �θ� �����ڸ� ȣ���ϴ� ������� �ذ�
			GeometricObject::init(_color, _pos);

			angle = _angle;
			size = _size;
		}

		void drawGeometry(const float& time) override // by ����� ���α׷���
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
