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
	{SE_KEY::SE_PLYR_BLOCK_DEL,			"Assets/Sound/SE/SE_PlayerBlockDelete.mp3"		},
	{SE_KEY::SE_PLYR_BLOCK_PUT,			"Assets/Sound/SE/SE_PlayerBlockPut.mp3"			},
	{SE_KEY::SE_PLYR_DAMAGE,			"Assets/Sound/SE/SE_PlayerDamage.mp3"			},
	{SE_KEY::SE_PLYR_DIE,				"Assets/Sound/SE/SE_PlayerDie.mp3"				},
	{SE_KEY::SE_PLYR_PUSH,				"Assets/Sound/SE/SE_PlayerEnemyPush.mp3"		},
	{SE_KEY::SE_PLYR_SHOT,				"Assets/Sound/SE/SE_PlayerShot.mp3"				},
	{SE_KEY::SE_ENEY_STOP,				"Assets/Sound/SE/SE_EnemyStop.mp3"				},
	{SE_KEY::SE_ENEY_HOLE_DROP,			"Assets/Sound/SE/SE_EnemyHoleDrop.mp3"			},
	{SE_KEY::SE_ENEY_BLOCK_COL,			"Assets/Sound/SE/SE_EnemyBlockCollision.mp3"	},
	{SE_KEY::SE_STAGE_CLEAR,			"Assets/Sound/SE/SE_StageClear.mp3"				},
	{SE_KEY::SE_GAME_CLEAR,				"Assets/Sound/SE/SE_GameClear.mp3"				},
	{SE_KEY::SE_GAME_OVER,				"Assets/Sound/SE/SE_GameOver.mp3"				},
	{SE_KEY::SE_TIMER_ADD_SCORE,		"Assets/Sound/SE/SE_TimerAddScore.mp3"			},
	{SE_KEY::SE_UI_CURSOR,				"Assets/Sound/SE/SE_UI_Cursor.mp3"				},
	{SE_KEY::SE_UI_SELECT,				"Assets/Sound/SE/SE_UI_Select.mp3"				},
	{SE_KEY::SE_COL_BILLIARD_BALL,		"Assets/Sound/SE/SE_Col_BilliardBall.mp3"		},
	{SE_KEY::SE_CALL_SAWADA_GAMES,		"Assets/Sound/SE/SE_CallSawadaGames.wav"		}
};

const std::unordered_map < BGM_KEY, string > SOUND_BGM_PATH
{
	{BGM_KEY::BGM_TITLE,	"Assets/Sound/BGM/BGM_Title.mp3"	},
	{BGM_KEY::BGM_SELECT,	"Assets/Sound/BGM/BGM_StageSelect.mp3"	},
	{BGM_KEY::BGM_GAME,		"Assets/Sound/BGM/BGM_Game.mp3"	},
	{BGM_KEY::BGM_RESULT,	"Assets/Sound/BGM/BGM_Result.mp3"	},
};


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：無し
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
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
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
	引数1：無し
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
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void SoundManager::Init()
{
	// BGMの読み込み
	for (std::pair<E_BGM_KEY, std::string> PathMap : SOUND_BGM_PATH)
	{
		E_BGM_KEY eNowKey = PathMap.first;		// 現在のキー
		std::string sNowPath = PathMap.second;	// 現在の保存位置パス

		XAUDIO2_BUFFER* pSoundData = new XAUDIO2_BUFFER();				// 画像データ作成
		pSoundData = LoadSound(sNowPath.c_str());
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
		pSoundData = LoadSound(sNowPath.c_str());
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
	-------------------------------------
	戻値：無し
=========================================== */
void SoundManager::PlaySE(E_SE_KEY e_GetKey, float vol, bool loopFlg)
{
	// SEの再生
	m_pSpeakerSE = PlaySound(m_apSoundDatas_SE[e_GetKey], loopFlg);
	m_pSpeakerSE->SetVolume(vol);
}

/* ========================================
	BGM再生関数
	-------------------------------------
	内容：BGMの再生
	-------------------------------------
	引数1：BGMキー
	引数2：音量
	-------------------------------------
	戻値：無し
=========================================== */
void SoundManager::PlayBGM(E_BGM_KEY e_GetKey, float vol)
{
	// BGMの再生
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// 再生の停止
		m_pSpeakerBGM->DestroyVoice();	// 完全に破棄
	
	}

	m_pSpeakerBGM = PlaySound(m_apSoundDatas_BGM[e_GetKey], true);
	m_pSpeakerBGM->SetVolume(vol);
}

/* ========================================
	BGM停止関数
	-------------------------------------
	内容：再生中のBGMを停止
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
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
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void SoundManager::StopSE()
{
	// SEの再生を停止
	if (m_pSpeakerSE)
	{
		m_pSpeakerSE->Stop();			// 再生の停止
	}
}


