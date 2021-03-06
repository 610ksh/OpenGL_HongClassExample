#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <vector>
#include <memory>

namespace jm
{
	class Example : public Game2D
	{
	public:
		RigidCircle rb0, rb1;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			// Initial position and velocity
			rb0.pos = vec2(-0.8f, 0.3f);
			rb0.vel = vec2(5.0f, 0.0f);
			rb0.color = Colors::hotpink;
			rb0.radius = 0.1f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.8f, 0.3f);
			rb1.vel = vec2(-5.0f, 0.0f);
			rb1.color = Colors::yellow;
			rb1.radius = 0.1f;
			// 밀도가 같다고 가정해서, 넓이에 따라서 rb1의 질량을 계산하도록 함. (2차원이라 제곱에 비례하도록 함)
			rb1.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);
		}

		void drawWall()
		{
			setLineWidth(5.0f);
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			drawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		void update() override
		{
			const float dt = getTimeStep() * 0.4f;
			const float epsilon = 0.5f; // 반발계수, 0이면 달라붙고 1이면 에너지 소실없이 튕김

			// physics update
			rb0.update(dt);
			rb1.update(dt);

			// check collision between two rigid bodies
			const float distance = (rb0.pos - rb1.pos).getMagnitude();

			// 반지름의 합보다 작으면 부딪힘
			if (distance <= rb0.radius + rb1.radius)
			{
				// compute impulse
				// 상대속도 : rb1이 바라본 rb0 속도
				const auto vel_rel = rb0.vel - rb1.vel;
				// 노멀벡터, 크기가 1이 되어야 함. n1 노멀벡터는 앞에 -를 붙여야함. (슬라이드는 rb1기준)
				const auto normal = -(rb1.pos - rb0.pos) / (rb1.pos - rb0.pos).getMagnitude();

				// 두 물체가 다가오고 있는지 검사
				if (vel_rel.getDotProduct(normal) < 0.0f)
				{
					const auto impuse = normal * -(1.0f + epsilon) * vel_rel.getDotProduct(normal) /
						((1.0f / rb0.mass) + (1.0f / rb1.mass));

					// update velocities of two bodies
					rb0.vel += impuse / rb0.mass;
					rb1.vel -= impuse / rb1.mass;
				}
			}

			// draw
			drawWall();
			rb0.draw();
			rb1.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
		}

	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}
