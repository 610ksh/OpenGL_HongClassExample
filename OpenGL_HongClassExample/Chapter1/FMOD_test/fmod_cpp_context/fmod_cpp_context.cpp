//#include "fmod.h"  // c-context (C문법)
#include "fmod.hpp" // cpp 전용
#include <iostream>
#include <conio.h> // getch()를 위해 필요

/*
	fmod api documentation
	https://www.fmod.com/resources/documentation-api
*/

using namespace std;

int main()
{
	cout << "FMOD cpp conext example" << endl;

	FMOD::System     *system(nullptr); // 채널은 하나를 선언하는게 일반적
	FMOD::Sound      *sound(nullptr); // 여러개의 사운드를 사용할거면 여러개 선언해야함(배열)
	FMOD::Channel    *channel(nullptr); // 한 시스템에서 여러가지 채널을 받을 수 있음.
	FMOD_RESULT       result;
	unsigned int      version; // 버전받을 변수 선언해줌
	void             *extradriverdata(nullptr); // 본 예제에서 사용하지x
	
	result = FMOD::System_Create(&system); // 시스템 생성
	if (result != FMOD_OK) return -1; // 위에서 실행한 함수가 제대로 실행됐는지 확인하는 함수
	
	result = system->getVersion(&version); // 버전 받아오기
	if (result != FMOD_OK) return -1;
	else printf("FMOD version %08x\n", version);
	
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); // 시스템 초기화 (32개까지 채널을 사용)
	if (result != FMOD_OK) return -1;
	// FMOD_LOOP_BIDI : 한방향 갔다가 거꾸로 재생해서 원상복귀
	result = system->createSound("singing.wav", FMOD_LOOP_NORMAL, 0, &sound); // LOOP_NORMAL : 반복
	//result = system->createSound("singing.wav", FMOD_LOOP_OFF, 0, &sound); // .mp3 files work!
	if (result != FMOD_OK) return -1;

	// 한 채널에 여러개 사운드를 재생 가능
	result = system->playSound(sound, 0, false, &channel); // 위에서 받은 sound를 플레이함. 어떤 채널을 통해 재생되는지 받아옴
	if (result != FMOD_OK) return -1;

	/*
		여기까지 진행하고 실행하면 소리가 나지 않음.
		playsound()를 실행하고 바로 내려와서 프로그램이 종료되기 때문.
		그래서 소리가 실행될때까지 최소한 시스템이 살아있게(임시 무한루프)를 돌게 해줘야함.
		근데 끝나고나서 자동 종료되도록 하려면, 조건을 걸어줘야함.
	*/
	while (true)
	{
		// 시스템 문제 있는지 체크
		result = system->update();
		if (result != FMOD_OK) return -1;

		//if (channel)
		//{
		//	bool playing = false;
		//	// channel->isPlaying(변수) : 변수에 해당 채널에서 소리가 현재 재생중인지 아닌지 bool 반환
		//	result = channel->isPlaying(&playing);
		//	if (!playing) break; // 소리가 나오고 있으면 true로 break 없이 빠져나옴
		//}


		/* 소리 반복 재생될때 사용하는 로직 */
		cout << "Press 0 to pause, 1 to resume, and x to exit" << endl;
		
		// 키보드 입력 하나를 받아들임
		int i = getch(); // i is ASCII code

		if (i == '0')
			channel->setPaused(true);
		else if (i == '1')
			channel->setPaused(false);
		else if (i == 'x')
			break;
	}

	// 시스템 해제
	system->release();	
}
