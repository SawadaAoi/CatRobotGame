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
#pragma once


// =============== �C���N���[�h ===================
#include "Sound.h"
#include <unordered_map>
#include <memory>


// =============== �萔��` =======================
#define SOUND_MNG_INST SoundManager::GetInstance()	// �C���X�^���X�擾

#define BGM_KEY			SoundManager::E_BGM_KEY		// �L�[�ȗ�
#define SE_KEY			SoundManager::E_SE_KEY		// �L�[�ȗ�
#define PLAY_SE(x)		SOUND_MNG_INST.PlaySE(x)	// ���ʉ��Đ�
#define PLAY_BGM(x)		SOUND_MNG_INST.PlayBGM(x)	// BGM�Đ�
#define STOP_BGM()		SOUND_MNG_INST.StopBGM()	// BGM��~
#define STOP_SE()		SOUND_MNG_INST.StopSE()		// SE��~
#define RESTART_BGM()	SOUND_MNG_INST.ReStartBGM()	// BGM�ĊJ
#define RESTART_SE()	SOUND_MNG_INST.ReStartSE()	// SE�ĊJ


// =============== �N���X��` =====================
class SoundManager
{
public:

	// BGM�L�[
	enum E_BGM_KEY
	{
		BGM_TITLE,
		BGM_SELECT,
		BGM_GAME_1,

		BGM_MAX,
	};

	// SE�L�[
	enum E_SE_KEY
	{
		SE_MENU_CURSOR,		// ���j���[�J�[�\��
		SE_MENU_DECIDE,		// ���j���[����
		SE_PLAYER_JUMP,		// �v���C���[�̃W�����v
		SE_PLAYER_SHOT,		// �v���C���[�̃V���b�g
		SE_PLAYER_DAMAGE,	// �v���C���[�̃_���[�W
		SE_COIN_GET,		// �R�C���擾
		SE_BLOCK_BREAK,		// �u���b�N�j��
		SE_GAME_CLEAR,		// �Q�[���N���A
		SE_GAME_OVER,		// �Q�[���I�[�o�[

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
	std::unordered_map <E_BGM_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_BGM;	// ���f���f�[�^���i�[���Ă���
	std::unordered_map <E_SE_KEY, XAUDIO2_BUFFER*> m_apSoundDatas_SE;	// ���f���f�[�^���i�[���Ă���

	IXAudio2SourceVoice* m_pSpeakerBGM;	// BGM�X�s�[�J�[
	IXAudio2SourceVoice* m_pSpeakerSE;	// SE�X�s�[�J�[
};
