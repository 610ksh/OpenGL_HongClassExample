#pragma once
// �θ� Ŭ���� ��� �߰�
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
			// ���Ͱ��� �������� �ʰ�, �θ� �����ڸ� ȣ���ϴ� ������� �ذ�
			GeometricObject::init(_color, _pos);

			size = _size;
		}


		void drawGeometry(const float& time) override // by ����� ���α׷���
		{
			rotate(time*90.0f);
			drawFilledCircle(color, size);
		}
	};
}