#pragma once

// サウンド関連処理
namespace Sound
{
	typedef enum SoundId
	{
		SoundId_EnemyAppear,	// 敵の登場音

		SoundId_Num
	}SoundId;

	// ロード、アンロード
	void load();
	void unload();

	// 効果音の再生
	void play(int soundId);
}
