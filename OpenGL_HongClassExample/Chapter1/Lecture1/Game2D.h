#pragma once

#include "RGB.h"
#include "Vector2.h" // 2차원
#include "Vector3.h" // 3차원
#include "Colors.h"
#include "Timer.h"
#include "DrawFunctions.h"

// 그래픽스 라이브러리
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <thread>         // std::this_thread::sleep_for
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace jm
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Game2D
	{
	private:
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr;

		Timer timer;

		// spf는 fps의 역수
		float spf = 1.0f / 60.0f;		 // second(s) per frame

		// control options
		std::map<int, bool> key_status;  // key_id, is_pressed
		std::map<int, bool> mbtn_status; // mouse_button_id, is_pressed
		bool draw_grid = false;

	public:
		Game2D()
		{}

		Game2D(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		~Game2D();

		Game2D & init(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		void reportErrorAndExit(const std::string& function_name, const std::string& message);

		bool isKeyPressed(const int& key);
		bool isKeyReleased(const int & key);
		bool isKeyPressedAndReleased(const int& key); //눌렀다가 땠을때

		bool isMouseButtonPressed(const int& mbtn);
		bool isMouseButtonReleased(const int& mbtn);
		bool isMouseButtonPressedAndReleased(const int& mbtn);

		vec2 getCursorPos(const bool& screen_coordinates = true);

		float getTimeStep(); // 한 프레임당 시간을 측정

		void drawGrid();

		void run();

		// 오버라이딩해서 사용하기 위해 virutal로 선언함. 우리만의 update를 만들기 위해
		virtual void update() 
		{
			// draw : 그리거나
			// play sould : 사운드
			// physics update : 물리처리
			// etc. : 기타등등
		}
	};
}