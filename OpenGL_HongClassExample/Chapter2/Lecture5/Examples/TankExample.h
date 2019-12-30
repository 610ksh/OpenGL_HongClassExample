#pragma once

#include "Game2D.h"
#include <map>

namespace jm
{
	// 모든 물체들
	class Actor
	{
	public:
		// 순수가상함수
		virtual void moveUp(float dt) = 0;
		virtual void moveDown(float dt) = 0;
		virtual void moveRight(float dt) = 0;
		virtual void moveLeft(float dt) = 0;
	};

	class Command
	{
	public:
		virtual ~Command() {}
		// 어떠한 형태의 Actor가 들어오던지 상관없이 함수를 이 수행하겠다는 의미.
		// 결론 : 탱크가 아닌 다른것도 들어갈수 있음.
		virtual void execute(Actor& actor, float dt, int key) = 0;
	};

	// 행위 자체를 객체로 만듦
	class KeyCommand : public Command
	{
	public:
		virtual void execute(Actor& actor, float dt, int key) override
		{
			// 들어오는 액터의 함수를 실행함
			if (key == GLFW_KEY_UP)
				actor.moveUp(dt);
			else if (key == GLFW_KEY_DOWN)
				actor.moveDown(dt);
			else if (key == GLFW_KEY_RIGHT)
				actor.moveRight(dt);
			else if (key == GLFW_KEY_LEFT)
				actor.moveLeft(dt);
		}
	};

	//////////////////////////////////////////////////////////

	class MyTank : public Actor
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);

		// 구체적으로 수행함.
		void moveUp(float dt) override
		{
			center.y += 0.5f * dt;
		}
		void moveDown(float dt) override
		{
			center.y -= 0.5f * dt;
		}
		void moveRight(float dt) override
		{
			center.x += 0.5f * dt;
		}
		void moveLeft(float dt) override
		{
			center.x -= 0.5f * dt;
		}

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	//////////////////////////////////////////////////////////

	class InputHandler
	{
	public:
		// Command 클래스 변수라는것이 중요!
		Command * button_up = nullptr;

		// <키보드 번호, 커맨드자체> 이렇게 두개를 맵핑시킴.
		/// 키 세팅을 위한 코드
		std::map<int, Command *> key_command_map;

		InputHandler()
		{
			button_up = new KeyCommand;
		}

		// 눌렸을때 어떤 행동을 할지 결정하는 함수 (button_up 변수가 중요)
		void handleInput(Game2D & game, Actor & actor, float dt)
		{
			/*if (game.isKeyPressed(GLFW_KEY_UP))  button_up->execute(actor, dt, GLFW_KEY_UP);
			if (game.isKeyPressed(GLFW_KEY_DOWN))  button_up->execute(actor, dt, GLFW_KEY_DOWN);
			if (game.isKeyPressed(GLFW_KEY_RIGHT))  button_up->execute(actor, dt, GLFW_KEY_RIGHT);
			if (game.isKeyPressed(GLFW_KEY_LEFT))  button_up->execute(actor, dt, GLFW_KEY_LEFT);*/

			// 정해진키가 아니라, 유저가 원하는 키로 같은 기능을 하도록 만들수도 있음
			for (auto & m : key_command_map)
			{
				if (game.isKeyPressed(m.first)) m.second->execute(actor, dt, m.first);
			}
		}
	};

	//////////////////////////////////////////////////////////

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		InputHandler input_handler;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			//key mapping
			input_handler.key_command_map[GLFW_KEY_UP] = new KeyCommand;
			input_handler.key_command_map[GLFW_KEY_DOWN] = new KeyCommand;
			input_handler.key_command_map[GLFW_KEY_RIGHT] = new KeyCommand;
			input_handler.key_command_map[GLFW_KEY_LEFT] = new KeyCommand;
		}

		~TankExample()
		{
			for (auto & m : input_handler.key_command_map)
			{
				delete m.second;
				std::cout << "해제 성공" << std::endl;
			}
		}

		void update() override
		{
			/// 확장성에 대한 고민
			// 아래같은 경우에서 만약 tank가 아니라 다른걸로 바뀌었을때, 매번 바꿔줘야 하는 단점이 있다.
			// 중요한 기능을 하는 update 함수는 웬만하면 수정되지 않는 쪽으로 코딩하는것이 매우 안전하다.
			// 그래서 물체가 바뀌었을때, tank와 관련된 부분을 수정해야 하는 위험성이 생긴다.
			// 탱크일때, 비행기일때 등등 조작법이 달라질수도 있음

			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			input_handler.handleInput(*this, tank, getTimeStep());

			// rendering
			tank.draw();
		}
	};
}