#pragma once
// �θ� Ŭ���� ��� �߰�
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
			// ���Ͱ��� �������� �ʰ�, �θ� �����ڸ� ȣ���ϴ� ������� �ذ�
			GeometricObject::init(_color, _pos);

			angle = _angle;

			width = _width;
			height = _height;
		}

		// �׷��� �̰� �����ϰ� �ȸ���� �����ص� ������ �ȶ�.
		// �����߰� �Ϸ���, �����Լ��� ���������Լ��� ������༭ ������ �������ؾ���.
		// virtual void drawGeometry() = 0; // �ٵ� ����.
		void drawGeometry(const float& time) override // by ����� ���α׷���
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
