#pragma once

#ifndef _SOUND_H_
#define _SOUND_H_
#include <Windows.h>
#include "./FMode/fmod.h"

#pragma comment (lib, "./lib/fmodex_vc.lib")

enum SOUNDKIND
{
	BGM = 0,
	SD_END
};

enum EFFSOUNDKIND
{
	SHOOT = 0,
	JUMP,
	ITEM_DROP,
	BULLET_DROP,
	SOUND_FROZEN,
	DEATH,
	EFFSD_END
};

class CSoundManager
{

public:
	void Init();
	void Release();

public:
	FMOD_SYSTEM* GetBgmSystem() { return g_psystem; }
	FMOD_SOUND** GetBgmSound() { return g_psound; }
	FMOD_CHANNEL** GetBgmChannel() { return g_pchannel; }

	FMOD_SYSTEM* GetEftSystem() { return effg_psystem; }
	FMOD_SOUND** GetEftSound() { return effg_psound; }
	FMOD_CHANNEL** GetEftChannel() { return effg_pchannel; }
public:
	void soundsetup();
	void effsoundsetup();
	void playsound(SOUNDKIND esound);
	void effsoundoff();
	void BGsoundoff();
	void effplaysound(EFFSOUNDKIND esound);

public:
	static CSoundManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CSoundManager;

		return m_instance;
	}

private:
	CSoundManager() {};
	~CSoundManager();

	CSoundManager(const CSoundManager&) = delete;
	void operator=(const CSoundManager&) = delete;
	static CSoundManager* m_instance;

private:
	FMOD_SYSTEM* g_psystem;
	FMOD_SOUND* g_psound[SD_END];
	FMOD_CHANNEL* g_pchannel[SD_END];

	FMOD_SYSTEM* effg_psystem;
	FMOD_SOUND* effg_psound[EFFSD_END];
	FMOD_CHANNEL* effg_pchannel[EFFSD_END];
};
#endif