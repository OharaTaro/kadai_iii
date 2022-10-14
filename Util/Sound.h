#pragma once

// サウンド関連処理
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		SoundId_BgmMain,	// 先頭画面のBGM

		// 効果音
		SoundId_PlayerExplosion,	// プレイヤー爆発音
		SoundId_EnemyAppear,	// 敵の登場音

		SoundId_Num
	}SoundId;

	// ロード、アンロード
	void load();
	void unload();

	// BGMの再生
	void startBgm(SoundId id, int volume = 255);
	void stopBgm(SoundId id);

	// 効果音の再生
	void play(SoundId id);

	// 音量設定	0~255
	void setVolume(SoundId id, int volume);
}
