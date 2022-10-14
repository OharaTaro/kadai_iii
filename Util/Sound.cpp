#include "Sound.h"
#include "DxLib.h"
#include <vector>

namespace
{
	// �T�E���h�n���h��
	std::vector<int>	m_soundHandle;

	// �T�E���h�t�@�C����
	const char* const kFileName[Sound::SoundId_Num] =
	{
		"Sound/appear.mp3",
	};
}

namespace Sound
{
	void load()
	{
		// �T�E���h�f�[�^�̓ǂݍ���
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}
	}
	void unload()
	{
		// �T�E���h�f�[�^�̉��
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
			handle = -1;
		}
	}

	// ���ʉ��̍Đ�
	void play(int soundId)
	{
		PlaySoundMem(m_soundHandle[soundId], DX_PLAYTYPE_BACK, true);
	}
}