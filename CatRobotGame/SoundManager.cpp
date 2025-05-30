/* ========================================
	DX22/Dropin
	------------------------------------
	音声管理用cpp
	------------------------------------
	SoundManager.cpp
========================================== */

// =============== インクルード ===================
#include "SoundManager.h"
#include <string>

// =============== 定数定義 =======================
using std::string;
const std::unordered_map < SE_KEY, string > SOUND_SE_PATH
{
	{SE_KEY::SE_MENU_CURSOR,	"Assets/Sound/SE/SE_MenuCursor.mp3"		},
	{SE_KEY::SE_MENU_DECIDE,	"Assets/Sound/SE/SE_MenuDecide.mp3"		},
	{SE_KEY::SE_PLAYER_JUMP,	"Assets/Sound/SE/SE_PlayerJump.mp3"		},
	{SE_KEY::SE_PLAYER_SHOT,	"Assets/Sound/SE/SE_PlayerShot.mp3"		},
	{SE_KEY::SE_PLAYER_DAMAGE,	"Assets/Sound/SE/SE_PlayerDamage.mp3"	},
	{SE_KEY::SE_COIN_GET,		"Assets/Sound/SE/SE_CoinGet.mp3"		},
	{SE_KEY::SE_BLOCK_BREAK,	"Assets/Sound/SE/SE_BlockBreak.mp3"		},
	{SE_KEY::SE_GAME_CLEAR,		"Assets/Sound/SE/SE_GameClear.mp3"		},
	{SE_KEY::SE_GAME_OVER,		"Assets/Sound/SE/SE_GameOver.mp3"		},

};

const std::unordered_map < BGM_KEY, string > SOUND_BGM_PATH
{
	{BGM_KEY::BGM_TITLE,	"Assets/Sound/BGM/BGM_Title.mp3"	},
	{BGM_KEY::BGM_SELECT,	"Assets/Sound/BGM/BGM_StageSelect.mp3"	},
	{BGM_KEY::BGM_GAME_1,	"Assets/Sound/BGM/BGM_Game_1.mp3"	},
};


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
=========================================== */
SoundManager::SoundManager()
	: m_pSpeakerBGM(nullptr)
	, m_pSpeakerSE(nullptr)
{


}

/* ========================================
	削除処理関数
	-------------------------------------
	内容：データを削除する
=========================================== */
void SoundManager::Uninit()
{
	// BGMの再生を停止
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// 再生の停止
		m_pSpeakerBGM->DestroyVoice();	// 完全に破棄
	}

	// SEの再生を停止
	if (m_pSpeakerSE)
	{
		m_pSpeakerSE->Stop();			// 再生の停止
		m_pSpeakerSE->DestroyVoice();	// 完全に破棄
	}

}

/* ========================================
	インスタンス(シングルトン)取得関数
	-------------------------------------
	内容：CSoundDataManagerクラスのインスタンスを取得
	-------------------------------------
	戻値：CSoundDataManagerクラスのインスタンス
=========================================== */
SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

/* ========================================
	音声初期化関数
	-------------------------------------
	内容：音声データの読み込み
=========================================== */
void SoundManager::Init()
{
	// BGMの読み込み
	for (std::pair<E_BGM_KEY, std::string> PathMap : SOUND_BGM_PATH)
	{
		E_BGM_KEY eNowKey = PathMap.first;		// 現在のキー
		std::string sNowPath = PathMap.second;	// 現在の保存位置パス

		XAUDIO2_BUFFER* pSoundData = new XAUDIO2_BUFFER();				// 画像データ作成
		pSoundData = Sound::Load(sNowPath.c_str());
		if (pSoundData == nullptr)	// 画像データ読み込み
		{
			MessageBox(NULL, sNowPath.c_str(), "Error", MB_OK);	//エラーメッセージの表示
		}

		m_apSoundDatas_BGM.insert(std::make_pair(eNowKey, pSoundData));	// 画像データ配列に追加
	}

	// SEの読み込み
	for (std::pair<E_SE_KEY, std::string> PathMap : SOUND_SE_PATH)
	{
		E_SE_KEY eNowKey = PathMap.first;		// 現在のキー
		std::string sNowPath = PathMap.second;	// 現在の保存位置パス

		XAUDIO2_BUFFER* pSoundData = new XAUDIO2_BUFFER();				// 画像データ作成
		pSoundData = Sound::Load(sNowPath.c_str());
		if (pSoundData == nullptr)	// 画像データ読み込み
		{
			MessageBox(NULL, sNowPath.c_str(), "Error", MB_OK);	//エラーメッセージの表示
		}

		m_apSoundDatas_SE.insert(std::make_pair(eNowKey, pSoundData));	// 画像データ配列に追加
	}
}

/* ========================================
	SE再生関数
	-------------------------------------
	内容：効果音の再生
	-------------------------------------
	引数1：SEキー
	引数2：音量
	引数3：ループ再生フラグ(trueでループ再生)
=========================================== */
void SoundManager::PlaySE(E_SE_KEY e_GetKey, float vol, bool loopFlg)
{
	// SEの再生
	m_pSpeakerSE = Sound::Play(m_apSoundDatas_SE[e_GetKey], loopFlg);
	m_pSpeakerSE->SetVolume(vol);
}

/* ========================================
	BGM再生関数
	-------------------------------------
	内容：BGMの再生
	-------------------------------------
	引数1：BGMキー
	引数2：音量
=========================================== */
void SoundManager::PlayBGM(E_BGM_KEY e_GetKey, float vol)
{
	// BGMの再生
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// 再生の停止
		m_pSpeakerBGM->DestroyVoice();	// 完全に破棄
	
	}

	m_pSpeakerBGM = Sound::Play(m_apSoundDatas_BGM[e_GetKey], true);
	m_pSpeakerBGM->SetVolume(vol);
}

/* ========================================
	BGM停止関数
	-------------------------------------
	内容：再生中のBGMを停止
=========================================== */
void SoundManager::StopBGM()
{
	// BGMの再生を停止
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// 再生の停止
	}
}

/* ========================================
	効果音停止関数
	-------------------------------------
	内容：再生中のSEを停止
=========================================== */
void SoundManager::StopSE()
{
	// SEの再生を停止
	if (m_pSpeakerSE)
	{
		m_pSpeakerSE->Stop();			// 再生の停止
	}
}

/* ========================================
	BGM再開関数
	-------------------------------------
	内容：停止中のBGMを再開
=========================================== */
void SoundManager::ReStartBGM()
{
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Start();
	}
}

/* ========================================
	SE再開関数
	-------------------------------------
	内容：停止中のSEを再開
=========================================== */
void SoundManager::ReStartSE()
{
	if (m_pSpeakerSE)
	{
		m_pSpeakerSE->Start();
	}
}