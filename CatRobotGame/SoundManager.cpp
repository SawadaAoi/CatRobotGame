/* ========================================
	DX22/Dropin
	------------------------------------
	�����Ǘ��pcpp
	------------------------------------
	SoundManager.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SoundManager.h"
#include <string>

// =============== �萔��` =======================
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
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F����
=========================================== */
SoundManager::SoundManager()
	: m_pSpeakerBGM(nullptr)
	, m_pSpeakerSE(nullptr)
{


}

/* ========================================
	�폜�����֐�
	-------------------------------------
	���e�F�f�[�^���폜����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void SoundManager::Uninit()
{
	// BGM�̍Đ����~
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// �Đ��̒�~
		m_pSpeakerBGM->DestroyVoice();	// ���S�ɔj��
	}

	// SE�̍Đ����~
	if (m_pSpeakerSE)
	{
		m_pSpeakerSE->Stop();			// �Đ��̒�~
		m_pSpeakerSE->DestroyVoice();	// ���S�ɔj��
	}


}

/* ========================================
	�C���X�^���X(�V���O���g��)�擾�֐�
	-------------------------------------
	���e�FCSoundDataManager�N���X�̃C���X�^���X���擾
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�FCSoundDataManager�N���X�̃C���X�^���X
=========================================== */
SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

/* ========================================
	�����������֐�
	-------------------------------------
	���e�F�����f�[�^�̓ǂݍ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void SoundManager::Init()
{
	// BGM�̓ǂݍ���
	for (std::pair<E_BGM_KEY, std::string> PathMap : SOUND_BGM_PATH)
	{
		E_BGM_KEY eNowKey = PathMap.first;		// ���݂̃L�[
		std::string sNowPath = PathMap.second;	// ���݂̕ۑ��ʒu�p�X

		XAUDIO2_BUFFER* pSoundData = new XAUDIO2_BUFFER();				// �摜�f�[�^�쐬
		pSoundData = LoadSound(sNowPath.c_str());
		if (pSoundData == nullptr)	// �摜�f�[�^�ǂݍ���
		{
			MessageBox(NULL, sNowPath.c_str(), "Error", MB_OK);	//�G���[���b�Z�[�W�̕\��
		}

		m_apSoundDatas_BGM.insert(std::make_pair(eNowKey, pSoundData));	// �摜�f�[�^�z��ɒǉ�
	}

	// SE�̓ǂݍ���
	for (std::pair<E_SE_KEY, std::string> PathMap : SOUND_SE_PATH)
	{
		E_SE_KEY eNowKey = PathMap.first;		// ���݂̃L�[
		std::string sNowPath = PathMap.second;	// ���݂̕ۑ��ʒu�p�X

		XAUDIO2_BUFFER* pSoundData = new XAUDIO2_BUFFER();				// �摜�f�[�^�쐬
		pSoundData = LoadSound(sNowPath.c_str());
		if (pSoundData == nullptr)	// �摜�f�[�^�ǂݍ���
		{
			MessageBox(NULL, sNowPath.c_str(), "Error", MB_OK);	//�G���[���b�Z�[�W�̕\��
		}

		m_apSoundDatas_SE.insert(std::make_pair(eNowKey, pSoundData));	// �摜�f�[�^�z��ɒǉ�
	}
}

/* ========================================
	SE�Đ��֐�
	-------------------------------------
	���e�F���ʉ��̍Đ�
	-------------------------------------
	����1�FSE�L�[
	����2�F����
	����3�F���[�v�Đ��t���O(true�Ń��[�v�Đ�)
	-------------------------------------
	�ߒl�F����
=========================================== */
void SoundManager::PlaySE(E_SE_KEY e_GetKey, float vol, bool loopFlg)
{
	// SE�̍Đ�
	m_pSpeakerSE = PlaySound(m_apSoundDatas_SE[e_GetKey], loopFlg);
	m_pSpeakerSE->SetVolume(vol);
}

/* ========================================
	BGM�Đ��֐�
	-------------------------------------
	���e�FBGM�̍Đ�
	-------------------------------------
	����1�FBGM�L�[
	����2�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void SoundManager::PlayBGM(E_BGM_KEY e_GetKey, float vol)
{
	// BGM�̍Đ�
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// �Đ��̒�~
		m_pSpeakerBGM->DestroyVoice();	// ���S�ɔj��
	
	}

	m_pSpeakerBGM = PlaySound(m_apSoundDatas_BGM[e_GetKey], true);
	m_pSpeakerBGM->SetVolume(vol);
}

/* ========================================
	BGM��~�֐�
	-------------------------------------
	���e�F�Đ�����BGM���~
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void SoundManager::StopBGM()
{
	// BGM�̍Đ����~
	if (m_pSpeakerBGM)
	{
		m_pSpeakerBGM->Stop();			// �Đ��̒�~
	}
}

/* ========================================
	���ʉ���~�֐�
	-------------------------------------
	���e�F�Đ�����SE���~
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void SoundManager::StopSE()
{
	// SE�̍Đ����~
	if (m_pSpeakerSE)
	{
		m_pSpeakerSE->Stop();			// �Đ��̒�~
	}
}


