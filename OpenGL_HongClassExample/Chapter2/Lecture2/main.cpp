#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"

#include "Triangle.h"
#include "Circle.h"
#include "Box.h"

#include <Windows.h>
#define ARRAY_COUNT 5

namespace jm
{
	class Example : public Game2D
	{
		Triangle my_tri, rnd_tri[ARRAY_COUNT];
		Circle my_cir, rnd_cir[ARRAY_COUNT];
		Box my_box, rnd_box[ARRAY_COUNT];

		float time = 0.0f;
		RandomNumberGenerator rnd;

	public:
		Example()
			: Game2D()
		{
			/*
				원래 init은 부모 클래스에서 공통적으로 호출했는데,
				하나의 자식 클래스에서 독특한 멤버변수가 생겼을때 문제가됨.
				그래서 그냥 모든 초기화는 각각의 자식 클래스에서 하게되는데,
				공통되는 부분은 부모 클래스를 호출함.
			*/
			my_tri.init(Colors::gold, vec2(-0.5f, 0.2f), 0.25f, 60.0f);
			/*my_tri.color = Colors::gold;
			my_tri.pos = vec2(-0.5f, 0.2f);
			my_tri.size = 0.25f;*/

			my_cir.init(Colors::olive, vec2(0.1f, 0.1f), 0.2f);
			/*my_cir.color = Colors::olive;
			my_cir.pos = vec2(0.1f, 0.1f);
			my_cir.size = 0.2f;*/

			my_box.init(Colors::black, { 0.0f,0.5f }, 0.2f, 0.2f, 45.0f);
			
		}

		void update() override
		{
			Sleep(100);
			my_tri.Draw(time); // yellow triangle
			my_cir.Draw(); // red circle
			my_box.Draw(time); // black box

			for (int i = 0; i < ARRAY_COUNT; ++i)
			{
				rnd_tri[i].init(
					Colors::colorArray[rnd.getInt(0, Colors::colorSize)],
					rnd.getFloatVector(-1.5, 1.5), // pos
					rnd.getFloat(0.1f, 0.5f), // size
					rnd.getFloat(-60.0f, 60.0f) // angle
				);

				rnd_cir[i].init(
					Colors::colorArray[rnd.getInt(0, Colors::colorSize)],
					rnd.getFloatVector(-1.5, 1.5), // pos
					rnd.getFloat(0.1f, 0.5f) // size
				);

				rnd_box[i].init(
					Colors::colorArray[rnd.getInt(0, Colors::colorSize)],
					rnd.getFloatVector(-1.5, 1.5), // pos
					rnd.getFloat(0.1f, 0.5f), // width
					rnd.getFloat(0.1f, 0.5f), // height
					rnd.getFloat(-60.0f, 60.0f) // angle
				);
			}

			for (int i = 0; i < ARRAY_COUNT; ++i)
			{
				rnd_tri[i].Draw();
				rnd_cir[i].Draw();
				rnd_box[i].Draw();
			}

			time += getTimeStep();
		}
	};
}

int main(void)
{
	jm::Example().run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}
