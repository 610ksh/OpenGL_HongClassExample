#include "SoundEngine_Singleton.h"

namespace jm
{
	SoundEngine_Singleton * SoundEngine_Singleton::instance = nullptr;

	// 어디선가 getInstance()를 호출하면
	SoundEngine_Singleton * SoundEngine_Singleton::getInstance()
	{
		// 인스턴스가 nullptr이라면 새롭게 초기화.
		if (instance == nullptr)
		{
			instance = new SoundEngine_Singleton();
		}

		// 이미 존재하고 있다면, 그 존재하는 대상을 넘겨줌
		return instance;
	}
}
