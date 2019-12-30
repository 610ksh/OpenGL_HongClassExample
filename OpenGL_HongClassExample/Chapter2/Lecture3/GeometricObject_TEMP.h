#pragma once

#include "Game2D.h"

namespace jm
{
	// this class shows what happens if you do not use OOP properly
	class GeometricObject_TEMP
	{
	public:
		enum TYPE
		{
			TRIANGLE, CIRCLE, BOX, // add more types
		} type;

		// common properties
		vec2 pos;
		RGB  color;

		// for triangle and circle
		float size;

		// for box
		float width;
		float height;

		//////////////// init 내용이 전부 달라질수 있어서 각각 따로 설계

		void initTriangle(const RGB & _color, const vec2 & _pos,
						  const float & _size)
		{
			color = _color;
			pos = _pos;
			size = _size;
		}

		void initCircle(const RGB & _color, const vec2 & _pos,
						const float & _size)
		{
			color = _color;
			pos = _pos;
			size = _size;
		}

		void initBox(const RGB & _color, const vec2 & _pos, 
					 const float & _width, const float & _height)
		{
			color = _color;
			pos = _pos;
			//size = _size; //Warning: do not use for Boxes
			width = _width;
			height = _height;
		}

		////////////////////// 그리는 방식도 다르게

		void draw()
		{
			if (type == TRIANGLE) {
				beginTransformation();
				{
					translate(pos);
					drawFilledTriangle(color, size);
				}
				endTransformation();
			}
			else if (type == CIRCLE)
			{
				beginTransformation();
				{
					translate(pos);
					drawFilledCircle(color, size);
				}
				endTransformation();
			}
			else if (type == BOX)
			{
				beginTransformation();
				{
					translate(pos);
					drawFilledBox(Colors::blue, this->width, this->height);
				}
				endTransformation();
			}
		}

		/*
		void drawGeometry()
		{
			if (type == TRIANGLE)
				drawFilledTriangle(color, size);
			else if (type == CIRCLE)
				drawFilledCircle(color, size);
			else if (type == BOX)
				drawFilledBox(Colors::blue, this->width, this->height);
			else
				exit(-1);
		}

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawGeometry();
			}
			endTransformation();
		}
		*/
	};
}