#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"

namespace jm
{
	class House
	{
		// getter, setter를 만들어서 객체지향설계를 해주는게 원칙
	private:
		RGB roof_color;
		RGB wall_color;
		RGB window_color;

		vec2 pos;
		float angle = 0.0f; // 아래 생성자와 동일하게 작동됨(신기능)

	public:
		House()
			:roof_color(Colors::red), pos(0.0f, 0.0f), angle(0.0f),
			window_color(Colors::skyblue), wall_color(Colors::yellow)
		{}

		void SetColor(const RGB& _roof_color, const RGB& _wall_color = Colors::yellow,
			const RGB& _window_color = Colors::skyblue)
		{
			roof_color = _roof_color;
			wall_color = _wall_color;
			window_color = _window_color;
		}

		void SetPos(const vec2& _pos)
		{
			pos = _pos;
		}

		void SetAngle(const float& _angle)
		{
			angle = _angle;
		}

		// draw a house
		void Draw(float const& time = 0.0f)
		{
			beginTransformation(); // push
			{
				// 전체 회전
				rotate(time*90.0f);

				beginTransformation(); // push
				{
					// 각각의 집의 평행이동과 회전
					translate(pos);
					rotate(angle);

					// wall
					drawFilledBox(wall_color, 0.2f, 0.2f);

					// roof
					drawFilledTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
					drawWiredTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

					// window
					drawFilledBox(window_color, 0.1f, 0.1f);
					drawWiredBox(Colors::gray, 0.1f, 0.1f);
					drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
					drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });
				}
				endTransformation(); // pop
			}
			endTransformation(); // pop
		}
	};

	class Example : public Game2D
	{
		House* house[3];
		float time = 0.0f;
	public:
		Example()
		{
			for (int i = 0; i < 3; ++i)
				house[i] = new House;
			house[1]->SetPos({ -0.5f, -0.5f });
			house[2]->SetPos({  0.5f,  0.5f });
		}

		void update() override
		{
			RandomNumberGenerator rnd;

			House houses[10];

			for (int i = 0; i < 10; ++i)
			{
				houses[i].SetPos({ -1.3f + 0.3f*float(i), rnd.getFloat(-1.0f,1.0f) });
				houses[i].SetAngle(rnd.getFloat(-60.0f, 60.0f));
				houses[i].SetColor(ColorArray::colors[rnd.getInt(0,ColorArray::color_length)],
					ColorArray::colors[rnd.getInt(0, ColorArray::color_length)],
					ColorArray::colors[rnd.getInt(0, ColorArray::color_length)]);
			}

			for (int i = 0; i < 10; ++i)
			{
				houses[i].Draw(time);
			}
			
			for (int i = 0; i < 3;++i)
			{
				house[i]->Draw();
			}
			
			time += getTimeStep();
			/*draw(Colors::red, { -0.5f, 0.0f });
			draw(Colors::blue, {  0.0f, 0.0f }, 10.0f);
			draw(Colors::skyblue, {  0.5f, 0.0f });*/
		}
	};
}

int main(void)
{
	/// 참고용
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();
	
	/// 2-1. 클래스 이해하기
	jm::Example().run();
	
	return 0;
}
