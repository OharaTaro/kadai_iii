#pragma once

// �T�E���h�֘A����
namespace Sound
{
	typedef enum SoundId
	{
		SoundId_PlayerExplosion,	// �v���C���[������
		SoundId_EnemyAppear,	// �G�̓o�ꉹ

		SoundId_Num
	}SoundId;

	// ���[�h�A�A�����[�h
	void load();
	void unload();

	// ���ʉ��̍Đ�
	void play(int soundId);
}
