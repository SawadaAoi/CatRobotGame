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
#ifndef _SOUND_MANAGER_H__
#define _SOUND_MANAGER_H__

// =============== インクルード ===================
#include "Sound.h"
#include <unordered_map>
#include <memory>


// =============== 定数定義 =======================
#define BGM_KEY SoundManager::E_BGM_KEY	// キー省略
#define SE_KEY SoundManager::E_SE_KEY	// キー省略
#define PLAY_SE(x) SoundManager::GetInstance().PlaySE(x)	// 効果音再生
#define PLAY_BGM(x) SoundManager::GetInstance().PlayBGM(x)	// BGM再生
#define STOP_BGM() SoundManager::GetInstance().StopBGM()	// BGM停止
#define STOP_SE() SoundManager::GetInstance().StopSE()	// SE停止



class SoundManager
{
public:

	// BGMキー
	enum E_BGM_KEY
	{
		BGM_TITLE = 0,
		BGM_SELECT,
		BGM_GAME,
		BGM_RESULT,

		BGM_MAX,
	};

	// SEキー
	enum E_SE_KEY
	{
		SE_PLYR_BLOCK_DEL,
		SE_PLYR_BLOCK_PUT,
		SE_PLYR_DAMAGE,
		SE_PLYR_DIE,
		SE_PLYR_PUSH,
		SE_PLYR_SHOT,
		SE_ENEY_STOP,
		SE_ENEY_HOLE_DROP,
		SE_ENEY_BLOCK_COL,
		SE_STAGE_CLEAR,
		SE_GAME_CLEAR,
		SE_GAME_OVER,
		SE_TIMER_ADD_SCORE,	
		SE_UI_CURSOR,
		SE_UI_SELECT,
		SE_COL_BILLIARD_BALL,
		SE_CALL_SAWADA_GAMES,

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
private:
	SoundManager();
	std::unordered_map <E_BGM_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_BGM;	// モデルデータを格納しておく
	std::unordered_map <E_SE_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_SE;	// モデルデータを格納しておく

	IXAudio2SourceVoice* m_pSpeakerBGM;	// BGMスピーカー
	IXAudio2SourceVoice* m_pSpeakerSE;	// SEスピーカー
};


#endif // !_SOUND_MANAGER_H__
