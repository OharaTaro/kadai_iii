#pragma once

// �T�E���h�֘A����
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		SoundId_BgmMain,	// �擪��ʂ�BGM

		// ���ʉ�
		SoundId_PlayerExplosion,	// �v���C���[������
		SoundId_EnemyAppear,	// �G�̓o�ꉹ

		SoundId_Num
	}SoundId;

	// ���[�h�A�A�����[�h
	void load();
	void unload();

	// BGM�̍Đ�
	void startBgm(SoundId id, int volume = 255);
	void stopBgm(SoundId id);

	// ���ʉ��̍Đ�
	void play(SoundId id);

	// ���ʐݒ�	0~255
	void setVolume(SoundId id, int volume);
}
