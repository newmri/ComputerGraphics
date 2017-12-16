#include "Define.h"

CSoundManager* CSoundManager::m_instance = nullptr;


void CSoundManager::Init()
{
	this->soundsetup();
	this->effsoundsetup();
}

void CSoundManager::Release()
{
	this->BGsoundoff();
	this->effsoundoff();
	for (int i = 0; i < SD_END; i++)
		FMOD_Sound_Release(this->g_psound[i]);
	for (int i = 0; i < EFFSD_END; i++)
		FMOD_Sound_Release(this->effg_psound[i]);
	FMOD_System_Close(this->g_psystem);
	FMOD_System_Release(this->g_psystem);
}
void CSoundManager::soundsetup()
{
	//���� �ý��� ����
	FMOD_System_Create(&this->g_psystem);
	//ä�� �� , ���, 0
	FMOD_System_Init(this->g_psystem, SD_END, FMOD_INIT_NORMAL, NULL);


	FMOD_System_CreateStream(this->g_psystem, "Resources\\Sound\\BGM\\Menu.mp3", FMOD_LOOP_NORMAL, 0, &this->g_psound[BGM]);


}

/*
���� 1 - ���θ޴�
���� 2 - ������
*/

void CSoundManager::playsound(SOUNDKIND esound)
{

	this->BGsoundoff();
	FMOD_System_PlaySound(this->g_psystem, FMOD_CHANNEL_FREE, this->g_psound[esound], 0, &this->g_pchannel[esound]);

}

void CSoundManager::effsoundsetup()
{
	char str[128];

	//���� �ý��� ����
	FMOD_System_Create(&this->effg_psystem);

	//ä�� �� , ���, 0
	FMOD_System_Init(this->effg_psystem, EFFSD_END, FMOD_INIT_NORMAL, NULL);

	//���� ���
	for (int i = 0; i<EFFSD_END; i++) {
		sprintf_s(str, "Sound\\effsound%d.wav", i + 1);
		FMOD_System_CreateSound(this->effg_psystem, (const char*)str, FMOD_DEFAULT, 0, &this->effg_psound[i]);
	}
	FMOD_System_CreateSound(this->effg_psystem, "Resources\\Sound\\Effects\\Attack\\Shoot.mp3", FMOD_DEFAULT, 0, &this->effg_psound[EFFSOUNDKIND::SHOOT]);
	FMOD_System_CreateSound(this->effg_psystem, "Resources\\Sound\\Effects\\Jump\\PlayerJump.wav", FMOD_DEFAULT, 0, &this->effg_psound[EFFSOUNDKIND::JUMP]);
	FMOD_System_CreateSound(this->effg_psystem, "Resources\\Sound\\Effects\\ItemDrop\\ItemDrop.wav", FMOD_DEFAULT, 0, &this->effg_psound[EFFSOUNDKIND::ITEM_DROP]);
	FMOD_System_CreateSound(this->effg_psystem, "Resources\\Sound\\Effects\\ItemDrop\\BulletDrop.mp3", FMOD_DEFAULT, 0, &this->effg_psound[EFFSOUNDKIND::BULLET_DROP]);
	FMOD_System_CreateSound(this->effg_psystem, "Resources\\Sound\\Effects\\Attack\\Blizzard.wav", FMOD_DEFAULT, 0, &this->effg_psound[EFFSOUNDKIND::SOUND_FROZEN]);
	FMOD_System_CreateSound(this->effg_psystem, "Resources\\Sound\\Effects\\Death\\Death.wav", FMOD_DEFAULT, 0, &this->effg_psound[EFFSOUNDKIND::DEATH]);
}

void CSoundManager::BGsoundoff()
{
	for (int i = 0; i < SD_END; i++)
		FMOD_Channel_Stop(this->g_pchannel[i]);
}

void CSoundManager::effsoundoff()
{
	for (int i = 0; i < EFFSD_END; i++)
		FMOD_Channel_Stop(this->effg_pchannel[i]);
}
void CSoundManager::effplaysound(EFFSOUNDKIND esound)
{

	FMOD_System_PlaySound(this->effg_psystem, FMOD_CHANNEL_FREE, this->effg_psound[esound], 0, &this->effg_pchannel[esound]);

}


CSoundManager::~CSoundManager() { this->Release(); }