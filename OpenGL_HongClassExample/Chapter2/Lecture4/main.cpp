#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"

#include <vector> // 벡터
#include <memory> // 스마트 포인터


// 새로운 도형들이 추가될때마다 여기에 헤더가 추가될 것이다.
//#include "Triangle.h"
//#include "Circle.h"
//#include "Box.h"

// 새로운 도형이 추가되어도 헤더를 여기에 추가하지 않고, 하나의 헤더로 해결가능
#include "GeometricObject.h"


namespace jm
{
	class Example : public Game2D
	{
	public:
		std::vector<GeometricObject*> my_objs;

		Example()
			: Game2D()
		{
			// 새로운 도형이 추가되어도 헤더를 여기에 추가하지 않고, 하나의 헤더로 해결가능
			my_objs.push_back(GeometricObject::makeTriangle(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f));
			my_objs.push_back(GeometricObject::makeCircle(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f));
			my_objs.push_back(GeometricObject::makeBox(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f));
			my_objs.push_back(GeometricObject::makeStar(Colors::red, vec2{ 0.0f, -0.5f }, 0.25f, 0.15f));

			/*my_objs.push_back(std::make_unique<Triangle>(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f));
			my_objs.push_back(std::make_unique<Circle>(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f));
			my_objs.push_back(std::make_unique<Box>(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f));*/
		}

		~Example()
		{
			// delete is unnecessary with shared_ptr
			for (const auto & obj : my_objs)
				delete obj;
		}

		void update() override
		{
			for (const auto & obj : my_objs)
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
