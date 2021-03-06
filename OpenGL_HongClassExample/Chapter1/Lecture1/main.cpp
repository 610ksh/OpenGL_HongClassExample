#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "TankExample.h"
#include "FaceExample.h"
#include "WalkingPerson.h"
#include "SolarSystem.h"

// 1-1강 맛보기 시작
namespace jm
{
	class RotatingStarExample :public Game2D
	{
		float time = 0.0f;

	public:
		void update() override // override 적어주는게 좋다. 프로그래머를 위해
		{
			rotate(time*180.0f); // 1초에 반바퀴를 돈다.

			drawFilledStar(Colors::gold, 0.4f, 0.25f); // 바깥쪽, 안쪽 길이

			time += this->getTimeStep(); // 각 프레임별 구간 길이만큼 시간이 더해진다.
		}
	};
}

// 1-2강 이동,회전,스케일링,애니메이션
namespace jm
{
	class TransformationExample : public Game2D
	{
	public:
		float time = 0;

		void update() override
		{
			setLineWidth(3.0f); // 선의 굵기 조절
			// 1.점 그리기
			/*const vec2 point(0.0f, 0.0f);
			drawPoint(Colors::black, point, 10.0f);*/

			// 2.선 그리기
			/*const vec2 p0(0.0f, 0.0f);
			const vec2 p1(0.5f, 0.5f);
			drawLine(Colors::red, p0, Colors::blue, p1);*/

			// 3.삼각형 그리기
			/*const vec2 p0(0.0f, 0.0f);
			const vec2 p1(0.5f, 0.5f);
			const vec2 p2(0.5f, 0.0f);
			drawLine(Colors::red, p0, Colors::blue, p1);
			drawLine(Colors::red, p0, Colors::blue, p2);
			drawLine(Colors::red, p1, Colors::blue, p2);*/

			// 4-1.움직이기 (translation / 누적)
			//const vec2 p0(0.0f, 0.0f);
			//const vec2 p1(0.5f, 0.5f);
			//const vec2 p2(0.5f, 0.0f);

			//translate(0.1f, 0.0f);  // 좌표계 자체를 이동시킴. 기준을 변경시킴. 누적가능.

			//drawLine(Colors::red, p0, Colors::blue, p1);
			//drawLine(Colors::red, p0, Colors::blue, p2);
			//drawLine(Colors::red, p1, Colors::blue, p2);

			//// 좌표계 원점으로 다시 맞춰주기
			//translate(-0.1f, 0.0f); 

			// 4-2.움직이기 (변환이 누적x)
			//beginTransformation(); // glPushMatrix() 사용

			//translate(-0.1f, 0.0f);

			//drawLine(Colors::red, p0, Colors::blue, p1);
			//drawLine(Colors::red, p0, Colors::blue, p2);
			//drawLine(Colors::red, p1, Colors::blue, p2);

			//endTransformation(); // glPopMatrix() 사용


			setLineWidth(5.0f); // glLineWidth() 사용

			// 5.박스 그리기 gold(원점 기준)
			//drawWiredBox(Colors::gold, 0.5f, 0.25f);

			// 6.박스 회전 skyblue(원점 기준)
			/*beginTransformation();
			rotate(30.0f);
			drawWiredBox(Colors::skyblue, 0.5f, 0.25f);
			endTransformation();*/

			// 7-1.박스 이동&회전 red(원점 기준)
			/*
				원하는 형태 : 회전시킨 모습을 오른쪽으로 이동시킴.
				=> 논리에 의하면 회전시키고 이동시켜야하는데 아래 코드는 마치,
				이동 -> 회전 순서인것처럼 보이지만, 실제로는 그렇지 않다
				컴퓨터 그래픽스에서 사용되는 API는 내부적으로 역순으로 적용되기 때문.
				여기서는 그리기(draw) -> 회전(rotate) -> 이동(translate)순서로 적용된거다.
				결과적으로 아래처럼 코딩하는게 정상적이고 반대로하면 원하지 않는 모양이 나옴.
			*/
			/*beginTransformation();
			translate(0.5f, 0.0f);
			rotate(30.0f);
			drawWiredBox(Colors::red, 0.5f, 0.25f);
			endTransformation();*/

			// 7-2.박스 이동&회전 olive(변환 순서를 잘못 적용했을때)
			/*beginTransformation();
			rotate(30.0f);
			translate(0.5f, 0.0f);
			drawWiredBox(Colors::olive, 0.5f, 0.25f);
			endTransformation();*/

			/*
				만약 원점이 아닌 점에서 회전을 시키고 싶을때는,
				1. 현재 물체를 원점으로 가져온뒤
				2. 물체를 회전시키고
				3. 다시 원래 위치로 이동시킨다.
				이런식의 과정이 숨어있는것
			*/

			// 8.원점이 아닌 점을 기준으로 회전하고 싶을때
			//const vec2 center_of_rot(-0.4f, 0.0f); // 회전하고 싶은 기준점
			//beginTransformation();
			//
			//// 회전 이전의 원본상태
			//drawWiredBox(Colors::gold, 0.5f, 0.25f);

			//translate(center_of_rot); // 다시 원래 위치로 복구 // 3rd
			//rotate(45.0f); // 회전시키고 // 2nd
			//// 기준점을 원점처럼 인식하려면, 전체 좌표계를 반대 방향으로 이동시켜야함 (-)
			//translate(-center_of_rot); // 회전 중심을 원점으로 가져오고 // 1st

			//drawWiredBox(Colors::gold, 0.5f, 0.25f);
			//drawPoint(Colors::black, center_of_rot, 5.0f);
			//endTransformation();

			// 9.크기 조절 (scaling)
			//beginTransformation();
			//drawWiredBox(Colors::gold, 1.0f, 1.0f); // 원본

			//scale(2.0f, 0.5f); // 스케일
			//drawWiredBox(Colors::green, 1.0f, 1.0f);
			//endTransformation();

			// 10.회전 애니메이션
			//beginTransformation();

			//rotate(time * 90.0f); // 60fps 기준, 1초에 90도 회전
			//scale(2.0f, 0.25f); // 스케일
			//drawWiredBox(Colors::red, 0.5f, 0.5f);
			//time += this->getTimeStep();
			//endTransformation();
		}
	};
}

// 1-4가 마우스
namespace jm
{
	class MouseExample :public Game2D
	{
	public:
		void update() override
		{
			// 윈도우 좌표계(false) vs 스크린 좌표계(true)
			const vec2 mouse_pos = getCursorPos(false);

			std::cout << mouse_pos << std::endl;

			//if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_1) == true)
			//{
			//	translate(mouse_pos);
			//	drawFilledCircle(Colors::gold, 0.1f);
			//}

			//if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_2) == true)
			//{
			//	translate(mouse_pos);
			//	drawFilledCircle(Colors::red, 0.1f);
			//}

			//if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_3) == true)
			//{
			//	translate(mouse_pos);
			//	drawFilledCircle(Colors::skyblue, 0.1f);
			//}
		}
	};
}

int main(void)
{

	/// 1-1강 맛보기 시작
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::RotatingStarExample().run();
	//jm::RotatingStarExample().init("This is my digital canvas!", 1280, 960, false).run();

	/// 1-2강 이동,회전,스케일링,애니메이션
	//jm::TransformationExample().run();
	////1-2강에서 다루지 않은 예시들
	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();

	/// 1-2강 과제
	//jm::SolarSystem().run();
	//jm::FaceExample().run();

	/// 1-3강 ﻿키보드입력과 반응
	//jm::TankExample().run();
	
	/// 1-3강 과제
	//jm::WalkingPerson().run();

	/// 1-4가 마우스
	//jm::MouseExample().init("This is my digital canvas!", 1500, 1000, false).run();

	return 0;
}
