/* ========================================
	DX22/Dropin
	------------------------------------
	音声管理用ヘッダ
	------------------------------------
	説明:Sound.hを使用して音声を再生する処理をまとめる
	　　 音声データの読み込み、再生、停止を行う
	------------------------------------
	SoundManager.h
========================================== */
#pragma once


// =============== インクルード ===================
#include "Sound.h"
#include <unordered_map>
#include <memory>


// =============== 定数定義 =======================
#define SOUND_MNG_INST SoundManager::GetInstance()	// インスタンス取得

#define BGM_KEY			SoundManager::E_BGM_KEY		// キー省略
#define SE_KEY			SoundManager::E_SE_KEY		// キー省略
#define PLAY_SE(x)		SOUND_MNG_INST.PlaySE(x)	// 効果音再生
#define PLAY_BGM(x)		SOUND_MNG_INST.PlayBGM(x)	// BGM再生
#define STOP_BGM()		SOUND_MNG_INST.StopBGM()	// BGM停止
#define STOP_SE()		SOUND_MNG_INST.StopSE()		// SE停止
#define RESTART_BGM()	SOUND_MNG_INST.ReStartBGM()	// BGM再開
#define RESTART_SE()	SOUND_MNG_INST.ReStartSE()	// SE再開


// =============== クラス定義 =====================
class SoundManager
{
public:

	// BGMキー
	enum E_BGM_KEY
	{
		BGM_TITLE,
		BGM_SELECT,
		BGM_GAME_1,

		BGM_MAX,
	};

	// SEキー
	enum E_SE_KEY
	{
		SE_MENU_CURSOR,		// メニューカーソル
		SE_MENU_DECIDE,		// メニュー決定
		SE_PLAYER_JUMP,		// プレイヤーのジャンプ
		SE_PLAYER_SHOT,		// プレイヤーのショット
		SE_PLAYER_DAMAGE,	// プレイヤーのダメージ
		SE_COIN_GET,		// コイン取得
		SE_BLOCK_BREAK,		// ブロック破壊
		SE_GAME_CLEAR,		// ゲームクリア
		SE_GAME_OVER,		// ゲームオーバー

		SE_MAX,
	};

public:
	static SoundManager& GetInstance();
	void Init();
	void Uninit();

	void PlaySE(E_SE_KEY e_GetKey, float vol = 1.0f, bool loopFlg = false);
	void PlayBGM(E_BGM_KEY e_GetKey, float vol = 1.0f);
	void StopBGM();
	void StopSE();
	void ReStartBGM();
	void ReStartSE();
private:
	SoundManager();
	std::unordered_map <E_BGM_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_BGM;	// モデルデータを格納しておく
	std::unordered_map <E_SE_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_SE;	// モデルデータを格納しておく

	IXAudio2SourceVoice* m_pSpeakerBGM;	// BGMスピーカー
	IXAudio2SourceVoice* m_pSpeakerSE;	// SEスピーカー
};
