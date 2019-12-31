#pragma once

#include "fmod.hpp"
#include <iostream>
#include <map>
#include <string>

/* 
	실무에서 사용하기에는 무리가 있는 코드다.
	예제를 위해 공부하는거라서 효율적인 코드는 아니다.
*/

namespace jm
{
	//Note: This example implementation of sound engine is inefficient.
	class SoundEngine
	{
	private:
		FMOD::System  *system = nullptr;
		//FMOD::Channel *channel = nullptr;
		std::map<std::string, FMOD::Sound*> sound_map; // 이름을 입력해서 사운드 포인터를 얻어옴
		std::map<FMOD::Sound*, FMOD::Channel*> channel_map;// not efficient // 사운드 포인터를 입력하면 해당 채널 포인터를 받아옴
		// 전체조건, 한 채널에 한 사운드만 재생되는 로직이라 비효율적이다.
		
		FMOD_RESULT   result;
		unsigned int  version;
		void          *extradriverdata = nullptr;

	public:
		SoundEngine()
		{
			using namespace std;

			result = FMOD::System_Create(&system);
			if (result != FMOD_OK) {
				cout << "FMOD::System_Create() fail" << endl;
				exit(-1);
			}

			result = system->getVersion(&version);
			if (result != FMOD_OK) {
				cout << "getVersion() fail" << endl;
				exit(-1);
			}
			else printf("FMOD version %08x\n", version);

			result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
			if (result != FMOD_OK) {
				cout << "system->init() fail" << endl;
				exit(-1);
			}
		}

	public:
		~SoundEngine()
		{
			system->release();
		}

		void createSound(const std::string & filename, const std::string & sound_name, const bool & use_loop)
		{
			sound_map[sound_name] = nullptr;

			auto & sound_ptr = sound_map[sound_name];

			const int loop_flag = use_loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

			result = system->createSound(filename.c_str(), loop_flag, 0, &sound_ptr);
			
			if (result != FMOD_OK) {
				std::cout << "system->createSound() fail" << std::endl;
				exit(-1);
			}
		}

		void playSound(const std::string & sound_name)
		{
			// 존재여부를 해당하는 key값에 해당하는 value를 이용해서 처리함
			if (sound_map.count(sound_name) <= 0) {
				std::cout << sound_name << " isn't initialized." << std::endl;
				exit(-1);
			}

			const auto & sound_ptr = sound_map[sound_name];
			auto & channel_ptr = channel_map[sound_ptr];

			bool is_playing = false;
			result = channel_ptr->isPlaying(&is_playing);

			if (is_playing) return; // don't play if this is already playing

			result = system->playSound(sound_ptr, 0, false, &channel_ptr);

			if (result != FMOD_OK) {
				std::cout << "system->playSound() fail" << std::endl;
				exit(-1);
			}
		}

		void stopSound(const std::string & sound_name)
		{
			if (sound_map.count(sound_name) <= 0) {
				std::cout << sound_name << " isn't initialized." << std::endl;
				exit(-1);
			}

			const auto & sound_ptr = sound_map[sound_name];
			auto & channel_ptr = channel_map[sound_ptr];

			bool is_playing = false;
			result = channel_ptr->isPlaying(&is_playing);

			if (is_playing == false) return; // don't stop playing if this is not playing

			result = channel_ptr->stop();

			if (result != FMOD_OK) {
				std::cout << "system->playSound() fail" << std::endl;
				exit(-1);
			}
		}
	};
}
