#include "SoundEngine_Singleton.h"

namespace jm
{
	SoundEngine_Singleton * SoundEngine_Singleton::instance = nullptr;

	// ��𼱰� getInstance()�� ȣ���ϸ�
	SoundEngine_Singleton * SoundEngine_Singleton::getInstance()
	{
		// �ν��Ͻ��� nullptr�̶�� ���Ӱ� �ʱ�ȭ.
		if (instance == nullptr)
		{
			instance = new SoundEngine_Singleton();
		}

		// �̹� �����ϰ� �ִٸ�, �� �����ϴ� ����� �Ѱ���
		return instance;
	}
}
