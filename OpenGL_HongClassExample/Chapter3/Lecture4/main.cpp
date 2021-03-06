#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <vector>
#include <memory>

namespace jm
{
	using namespace std;

	static const auto gravity = vec2(0.0f, -9.8f);

	class Particle
	{
	public:
		vec2 pos;
		vec2 vel;
		RGB  color;

		// 단위는 시간이다
		float age; // 나이
		float life; // 수명

		// 별의 회전(2차원만 고려)
		float rot;
		float angular_velocity; // 회전속도

		void update(const float & dt)
		{
			const auto acc = gravity; //assumes GA only.

			vel += acc * dt;
			pos += vel * dt;

			rot += angular_velocity * dt;

			// update age.
			age += dt; // 시간간격만큼 나이를 먹어감
		}
	};

	class ParticleSystem
	{
	public:
		// Note.파티클의 포인터를 넣는 경우도 있다
		vector<Particle> particles;
		// Note. 랜덤 기능 사용
		RandomNumberGenerator rn;

		ParticleSystem()
		{
			reset();
		}
		// 임의의 방향의 랜덤 벡터를 만듦.
		auto getRandomUnitVector()
		{
			const float theta = rn.getFloat(0.0f, 3.141592f * 2.0f); // 0.0 ~ 2pi (360도)

			return vec2{cos(theta), -sin(theta)};
		}

		auto getRandomColor()
		{
			return RGB{ rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f) };
		}

		void reset()
		{
			particles.clear();
			// reserve를 사용하면 좀더 빠르긴하다.
			// initialize particles (1000개 사용)
			for (int i = 0; i < 1000; ++i)
			{
				Particle new_particle;
				new_particle.pos = vec2(0.0f, 0.5f) + getRandomUnitVector() * rn.getFloat(0.001f, 0.03f); //랜덤
				new_particle.vel = getRandomUnitVector() * rn.getFloat(0.01f, 2.0f); //랜덤
				new_particle.color = getRandomColor(); //랜덤

				new_particle.age = 0.0f; // 처음 나이는 0살
				new_particle.life = rn.getFloat(0.1f, 0.5f); // 전체 수명을 랜덤하게 잡음

				// 별의 회전
				new_particle.rot = rn.getFloat(0.0f, 360.0f);
				new_particle.angular_velocity = rn.getFloat(-1.0f, 1.0f)*360.0f * 4.0f;

				particles.push_back(new_particle);
			}
		}

		void update(const float & dt)
		{
			for (auto & pt : particles)
			{
				// 파티클 시스템에서 생성한 모든 하나하나의 파티클들 상태 update 
				pt.update(dt);

				// remove particles when they are 1. too old, 2. out of screen.
			}
		}

		void draw()
		{
			beginTransformation();
			for (const auto & pt : particles)
			{
				// 만약 나이가 전체 수명을 넘어서면 그리지 않는다.(점점 사라짐)
				if (pt.age > pt.life) continue;

				// 배경색으로 블랜딩효과 넣기
				const float alpha = 1.0f - pt.age / pt.life; //(1~0, %, 점점 흐려짐)

				// 배경색이 흰색이라서 가운데가 (1,1,1)이 된거임. 아래 코드는 매우 빈번한 코드임. 꼭 알아두자
				// update color (blend with background color)
				const RGB blended_color = {
					pt.color.r * alpha + 1.0f * (1.0f - alpha),
					pt.color.g * alpha + 1.0f * (1.0f - alpha),
					pt.color.b * alpha + 1.0f * (1.0f - alpha)
				};

				// 파티클 안에 넣을수도 있지만, 여기서는 파티클 시스템에 만듦.
				// gpu 가속을 위해, 하나하나 파티클을 보내기보다, 여러개의 파티클을 한번에 보내는게 좋기때문
				// 하나하나 보내서 호출하는 방식은 느림 (본 예제는 차이가 없을것임)
				// drawPoint(blended_color, pt.pos, 3.0f);

				// 별
				beginTransformation();
				translate(pt.pos);

				rotate(pt.rot);

				drawFilledStar(blended_color, 0.03f, 0.01f);
				endTransformation();

			}
			endTransformation();
		}
	};

	class Example : public Game2D
	{
	public:
		ParticleSystem ps;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			ps.reset();
		}

		void update() override
		{
			const float dt = getTimeStep() * 0.4f;

			ps.update(dt);

			ps.draw();

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
