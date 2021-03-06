#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include <vector>
#include <memory>

namespace jm
{
	class RigidCircle
	{
	public:
		vec2 pos; // 원의 중심 위치
		vec2 vel;
		float radius = 0.1f;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(Colors::hotpink, radius - 1e-3f);
				setLineWidth(2.0f);
				drawWiredCircle(Colors::black, radius);
			}
			endTransformation();
		}

		void update(const float & dt)
		{
			// Note.실제 물리엔진에서는 별도의 헤더에 상수로 모아둔다.
			static const vec2 gravity = vec2(0.0f, -9.8f); // y축으로

			//// 완전탄성충돌 (속도를 완전히 되돌려줌)
			static const float coef_res = 0.8f; // Coefficient of restitution : 반발 계수
			///// 1보다 크면 더 세게 튕겨 나옴. 1보다 작으면 속력값을 잃고 약해지는거임.

			static const float coef_friction = 0.98f; // friction (정확한 물리는 아님)

			//// 중력 적용
			// 속도의 변화량은 위치의 변화량 * 단위시간
			vel = vel + gravity * dt; //

			//// 위치 변화
			// numerical integration (수치 적분)
			// 공이 날아갈때, 시간과 속력이 필요함.
			pos = pos + vel * dt; // 거리 = 시간 * 속력 (물리)



			// wall collision, friction // 튕기는 부분, 마찰

			////////////// wall collision
			
			// 오른쪽 벽은 (1,0)에 있음
			if (1.0f - pos.x <= radius)
			{
				// 벽에 달라붙음 (순간 뚫고 지나가는걸 막는 용도)
				pos.x = 1.0f - radius;

				// 오른쪽 방향은 양수 방향임
				if (vel.x >= 0.0f)
					// 공의 방향을 바꿈
					vel.x *= -1.0f * coef_res; // -1.0f은 방향을 바꾸는 용도임
			}

			// 왼쪽 벽 (-1,0)
			if (pos.x <= -1.0f + radius)
			{
				// 벽에 달라붙음 (순간 뚫고 지나가는걸 막는 용도)
				pos.x = -1.0f + radius;

				// 왼쪽 방향은 음수 방향임
				if (vel.x <= 0.0f)
					// 공의 방향을 바꿈
					vel.x *= -1.0f * coef_res; // -1.0f은 방향을 바꾸는 용도임
			}

			// 바닥 (0,-1)
			if (pos.y <= -1.0f + radius)
			{
				// 벽에 달라붙음 (순간 뚫고 지나가는걸 막는 용도)
				pos.y = -1.0f + radius;

				// 아래 방향은 음수 방향임
				if (vel.y <= 0.0f)
					// 공의 방향을 바꿈
					vel.y *= -1.0f * coef_res; // -1.0f은 방향을 바꾸는 용도임

				/* 
					바닥에 닿았다면 속도가 점점 줄어듦 (1보다 작은값)
					Note. 마찰에 영향을 받는 속도는 수직속도가 아니라 평행속도(좌우)이다.
					그래서 속도의 x값을 바꿔줘야한다. 주의하기!
				*/
				vel.x *= coef_friction;
			}
		}
	};

	class Example : public Game2D
	{
	public:
		RigidCircle rigid_body;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			// Initial position and velocity
			rigid_body.pos = vec2(-0.8f, 0.3f); // 격자가 m단위임
			rigid_body.vel = vec2(10.0f, 0.0f); // 10m/s
		}

		void drawWall()
		{
			setLineWidth(5.0f);
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			drawLine(Colors::blue, { 1.0f,  -1.0f }, Colors::blue, { 1.0f, 1.0f });
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		void update() override
		{
			// physics update // 업데이트 패턴이라고 부르기도 함
			rigid_body.update(getTimeStep() * 0.4f); // 0.1을 곱한 이유는 너무 빨라서임.

			// draw
			drawWall();
			rigid_body.draw(); // 실제로 그리는건 따로 분리됨

			// reset button (추가 기능 R)
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
		}
	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}