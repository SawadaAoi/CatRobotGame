/* ========================================
	DX22/Dropin
	------------------------------------
	�����Ǘ��p�w�b�_
	------------------------------------
	����:Sound.h���g�p���ĉ������Đ����鏈�����܂Ƃ߂�
	�@�@ �����f�[�^�̓ǂݍ��݁A�Đ��A��~���s��
	------------------------------------
	SoundManager.h
========================================== */
#ifndef _SOUND_MANAGER_H__
#define _SOUND_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Sound.h"
#include <unordered_map>
#include <memory>


// =============== �萔��` =======================
#define BGM_KEY SoundManager::E_BGM_KEY	// �L�[�ȗ�
#define SE_KEY SoundManager::E_SE_KEY	// �L�[�ȗ�
#define PLAY_SE(x) SoundManager::GetInstance().PlaySE(x)	// ���ʉ��Đ�
#define PLAY_BGM(x) SoundManager::GetInstance().PlayBGM(x)	// BGM�Đ�
#define STOP_BGM() SoundManager::GetInstance().StopBGM()	// BGM��~
#define STOP_SE() SoundManager::GetInstance().StopSE()	// SE��~



class SoundManager
{
public:

	// BGM�L�[
	enum E_BGM_KEY
	{
		BGM_TITLE = 0,
		BGM_SELECT,
		BGM_GAME,
		BGM_RESULT,

		BGM_MAX,
	};

	// SE�L�[
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
	std::unordered_map <E_BGM_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_BGM;	// ���f���f�[�^���i�[���Ă���
	std::unordered_map <E_SE_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_SE;	// ���f���f�[�^���i�[���Ă���

	IXAudio2SourceVoice* m_pSpeakerBGM;	// BGM�X�s�[�J�[
	IXAudio2SourceVoice* m_pSpeakerSE;	// SE�X�s�[�J�[
};


#endif // !_SOUND_MANAGER_H__
