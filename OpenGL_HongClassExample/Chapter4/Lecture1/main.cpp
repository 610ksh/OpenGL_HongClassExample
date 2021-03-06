#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
// 이미지.h
#include "ImageObject.h"

#include <vector>
#include <memory>

/*
	<참고>
	이 예제는 고전적인 OpenGL을 사용했다.
	그 이유는 초보자 입장에서 이해하는데 더 쉽고 직관적이기 때문.
	현대 OpenGL은 코딩할때 좀더 간결하고 쉽게 할 수 있지만,
	초보가 바로 이해하기엔 난해할 수 있는 코드가 있는편이다.
*/

namespace jm
{
	using namespace std;

	class Example : public Game2D
	{
	public:
		// 이미지 파일들을 오브젝트로 관리하기 위한 변수들
		ImageObject house;
		ImageObject background;
		ImageObject sentence;

		Example()
			: Game2D("This is my digital canvas!", 1280, 960, false) // MUST initialize Game2D
		{
			// 포토샵을 이용하지 못하는경우, 배경을 투명하게 하지 못할수도 있다. 그럴때 이용하는 코드
			house.init("car.png", 255, 255, 255); // white to transparent (검은색은 (0,0,0)해야함)
			background.init("Background_image.bmp");
			sentence.init("sentence.png");
		}

		void update() override
		{
			beginTransformation();
			scale(1.5f, 1.5f);
			background.draw();
			endTransformation();
			
			beginTransformation();
			translate(-0.5f, 0.0f);
			drawFilledStar(Colors::gold, 0.2f, 0.1f);
			endTransformation();

			beginTransformation();
			translate(0.0f, 0.5f);
			scale(0.5f, 0.5f);
			sentence.draw();
			endTransformation();

			// moving car
			{
				static float x = -1.0f;

				beginTransformation();
				translate(x, 0.0f);
				scale(0.5f, 0.5f);
				house.draw();
				endTransformation();

				x += 0.01f;

				if (x > 1.0f) x = -1.0f;
			}

			beginTransformation();
			translate(0.5f, 0.0f);
			drawFilledStar(Colors::red, 0.2f, 0.1f);
			endTransformation();

			// 그리는 순서 주의하자.
			//background.draw(); //this hides everything
		}
	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}
