#include "Sound.h"
#include "DxLib.h"
#include <vector>

namespace
{
	// サウンドハンドル
	std::vector<int>	m_soundHandle;

	// サウンドファイル名
	const char* const kFileName[Sound::SoundId_Num] =
	{
		"Sound/appear.mp3",
	};
}

namespace Sound
{
	void load()
	{
		// サウンドデータの読み込み
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}
	}
	void unload()
	{
		// サウンドデータの解放
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
			handle = -1;
		}
	}

	// 効果音の再生
	void play(int soundId)
	{
		PlaySoundMem(m_soundHandle[soundId], DX_PLAYTYPE_BACK, true);
	}
}