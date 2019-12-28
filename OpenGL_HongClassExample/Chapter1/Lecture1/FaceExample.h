#pragma once

#include "Game2D.h"

namespace jm
{
	class FaceExample : public Game2D
	{
		float time = 0.0f;
	public:
		void update() override
		{
			//rotate(time*90.0f);
			//translate(0.5f, 0.0f);

			// Big yellow face
			drawFilledCircle(Colors::skyblue, 0.8f); // draw background object first
			{
				setLineWidth(5.0f);
				drawWiredCircle(Colors::black, 0.8f);
			}

			// 坷弗率 内关
			beginTransformation();
			{
				setLineWidth(2.0f);

				translate(0.125f, -0.225f);
				rotate(-45.0f);
				scale(1.6f, 1.3f);
				drawFilledCircle(Colors::white, 0.1f);
				drawWiredCircle(Colors::black, 0.1f);
			}
			endTransformation();
			
			// 哭率 内关
			beginTransformation();
			{
				setLineWidth(2.0f);

				translate(-0.125f, -0.225f);
				rotate(45.0f);
				scale(1.6f, 1.3f);
				drawFilledCircle(Colors::white, 0.1f);
				drawWiredCircle(Colors::black, 0.1f);
			}
			endTransformation();

			// 泥荐堪
			beginTransformation();
			{
				drawLine(Colors::black, vec2(-0.175f, -0.15f), Colors::black, vec2(-0.4f, -0.10f));
				drawLine(Colors::black, vec2(-0.175f, -0.2f), Colors::black, vec2(-0.4f, -0.2f));
				drawLine(Colors::black, vec2(-0.175f, -0.25f), Colors::black, vec2(-0.4f, -0.35f));

				drawLine(Colors::black, vec2(0.175f, -0.15f), Colors::black, vec2(0.4f, -0.10f));
				drawLine(Colors::black, vec2(0.175f, -0.2f), Colors::black, vec2(0.4f, -0.2f));
				drawLine(Colors::black, vec2(0.175f, -0.25f), Colors::black, vec2(0.4f, -0.35f));
			}
			endTransformation();


			// Blue nose
			beginTransformation();
			{
				//rotate(-10.0f);		// 10 degrees rotated 
				//scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledCircle(Colors::black, 0.08f);
			}
			endTransformation();

			// left eye
			beginTransformation();
			{
				translate(-0.6f, 0.18f);
				drawFilledCircle(Colors::black, 0.035f);
			}
			endTransformation();

			// right eye
			beginTransformation();
			{
				translate(0.6f, 0.18f);
				drawFilledCircle(Colors::black, 0.035f);
			}
			endTransformation();

			/*for (float x = -0.5f; x < 0.4f; x += 0.05f)
			{
				drawLine(Colors::black, vec2(x, 0.6f), Colors::gray, vec2(x + 0.05f, 0.85f));
			}*/

			time += this->getTimeStep();
		}
	};
}