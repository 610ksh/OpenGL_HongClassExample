#pragma once

#include "RGB.h"
#include "Vector2.h"
#include "Vector3.h"
#include <GL/glew.h>

namespace jm
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	float getRadian(const float& degree); // 대부분의 그래픽스 라이브러리는 라디안을 사용함.

	// Various primitives
	void drawPoint(const RGB& color, const vec2& position, const float & size); // use drawFilledCircle instead // 점
	void drawLine(const RGB& color0, const vec2& position0, const vec3& color1, const vec2& position1); // 라인

	void drawWiredBox(const RGB& color, const float& width, const float& height); // ?
	void drawWiredTriangle(const RGB& color, const float& edge_length); // 삼각형
	void drawWiredTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2);
	void drawWiredSquare(const RGB& color, const float& edge_length); // 사각형
	void drawWiredRegularConvexPolygon(const RGB& color, const float& radius, const float & start_theta = 0.0f, const int& num_segments = 100); //다각형
	void drawWiredCircle(const RGB& color, const float& radius); // 원
	void drawWiredPentagon(const RGB& color, const float& radius); // 오각형

	void drawFilledBox(const RGB& color, const float& width, const float& height);
	void drawFilledRegularConvexPolygon(const RGB& color, const float& radius, const float & start_theta = 0.0f, const int& num_segments = 100);
	void drawFilledCircle(const RGB& color, const float& radius);
	void drawFilledTriangle(const RGB& color, const float& edge_length);
	void drawFilledTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2);
	void drawFilledSquare(const RGB& color, const float& edge_length);
	void drawFilledPentagon(const RGB& color, const float& radius);
	void drawFilledStar(const RGB& color, const float& outer_radius, const float& inner_radius);
	
	void drawGrid(const RGB& color, const float& dx);

	// Affine transformations
	void beginTransformation();
	void endTransformation();
	void translate(const vec2& dx);
	void translate(const float& pos_x, const float& pos_y);
	void rotate(const float& degree);
	void scale(const float& scale_x, const float& scale_y);

	// Other options
	void setLineWidth(const int & width);
}
