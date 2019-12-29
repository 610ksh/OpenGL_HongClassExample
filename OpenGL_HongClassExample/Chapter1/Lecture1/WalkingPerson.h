#pragma once

#include "Game2D.h"

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/
	class Person
	{
	public:
		vec2 center; // 현재 위치

		void draw(const float& time)
		{
			beginTransformation();
			translate(center);
			{
				// gold face
				beginTransformation();
				translate(0.0f, 0.12f);
				drawFilledCircle(Colors::gold, 0.08f);
				translate(0.05f, 0.03f);
				drawFilledCircle(Colors::white, 0.01f); // while eye

				endTransformation();

				// yellow arm1
				beginTransformation();
				rotate(sin(time*5.0f) * -30.0f);					// animation!
				scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledBox(Colors::yellow, 0.05f, 0.18f);
				endTransformation();

				// red body
				beginTransformation();
				scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledBox(Colors::red, 0.13f, 0.2f);
				endTransformation();

				// yellow arm2
				beginTransformation();
				rotate(sin(time*5.0f) * 30.0f);					// animation!
				scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledBox(Colors::yellow, 0.05f, 0.18f);
				endTransformation();

				// green leg
				beginTransformation();
				translate(0.0f, -0.6f);
				translate(0.0f, 0.2f);
				rotate(sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
				translate(0.0f, -0.2f);
				drawFilledBox(Colors::green, 0.1f, 0.4f);
				endTransformation();


				beginTransformation();
				translate(0.0f, -0.6f);
				translate(0.0f, 0.2f);
				rotate(sinf(time*5.0f + 3.141592f) * -30.0f);	// animation!
				translate(0.0f, -0.2f);
				drawFilledBox(Colors::silver, 0.1f, 0.4f);
				endTransformation();
			}
			endTransformation();
		}
	};

	class WalkingPerson : public Game2D
	{
		Person person[3];

		float time = 0.0f;

	public:
		WalkingPerson()
		{
			person[0].center = vec2(0.0f, -0.2f);
			person[1].center = vec2(1.0f, 0.5f);
			person[2].center = vec2(-0.5f, 0.1f);
		}
		void update() override
		{
			if (isKeyPressed(GLFW_KEY_LEFT))	person[0].center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	person[0].center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		person[0].center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	person[0].center.y -= 0.5f * getTimeStep();

			for (int i = 0; i < 3; ++i)
			{
				// draw
				person[i].draw(time);
			}
			time += this->getTimeStep();
		}

		/*
		void update() override
		{
			// gold face
			beginTransformation();
			translate(0.0f, 0.12f);
			drawFilledCircle(Colors::gold, 0.08f);
			translate(0.05f, 0.03f);
			drawFilledCircle(Colors::white, 0.01f); // while eye

			endTransformation();

			// yellow arm1
			beginTransformation();
			rotate(sin(time*5.0f) * -30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// red body
			beginTransformation();
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::red, 0.13f, 0.2f);
			endTransformation();

			// yellow arm2
			beginTransformation();
			rotate(sin(time*5.0f) * 30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();


			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time*5.0f + 3.141592f) * -30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::silver, 0.1f, 0.4f);
			endTransformation();

			time += this->getTimeStep();
		}
		*/
	};
}