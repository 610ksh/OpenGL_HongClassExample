#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Circle.h"
#include "Box.h"

#include <vector>
#include <memory>

namespace jm
{
	class Example : public Game2D
	{
	public:
		std::vector<std::unique_ptr<GeometricObject>> my_objs;

		Example()
			: Game2D()
		{
			my_objs.push_back(std::make_unique<Triangle>(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f));
			my_objs.push_back(std::make_unique<Circle>(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f));
			my_objs.push_back(std::make_unique<Box>(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f));
		}

		~Example()
		{
			// 이때 obj는 부모클래스였기 때문에 소멸자가 부모클래스로 호출됨.
			// 자식 클래스의 소멸자를 부르려면, 소멸자를 가상함수로 만들어야함!
			/*for (const auto& obj : my_objs)
				delete obj;*/
		}

		void update() override
		{
			for (const auto& obj : my_objs)
				obj->draw();
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
