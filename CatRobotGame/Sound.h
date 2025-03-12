/* ========================================
	CatRobotGame/
	------------------------------------
	�����p�w�b�_
	------------------------------------
	�����F�����̓ǂݍ��݁A�Đ����s��
		�@InitSound�֐���LoadTexture�֐�����ɌĂяo���ƃG���[
		�@��������COM�I�u�W�F�N�g�𗘗p���邽��
		�@���X�i�[
		�@ ���𕷂����߂́u���v�ɑ����B3D�T�E���h�ŕK�v�B
		�@�\�[�X
		�@ ���𔭂���u�����v�ɑ����B�X�s�[�J�[�BXAudio2�ł�Voice�ƌĂ΂��B
		�@�o�b�t�@
		�@ ���f�[�^���i�[���Ă����o�b�t�@�BWAV�t�@�C���AOGG�t�@�C���Ȃǂ��烍�[�h�B
	------------------------------------
	Sound.h
========================================== */
#pragma once


// =============== �C���N���[�h ===================
#include <map>
#include <string>
#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

// =============== �N���X��` =====================
class Sound
{
public:
	// �T�E���h�f�[�^
	struct SoundData
	{
		WAVEFORMATEX		format;		// WAV�t�H�[�}�b�g
		BYTE*				pBuffer;	// �T�E���h�f�[�^
		DWORD				bufSize;	// �f�[�^�T�C�Y
		XAUDIO2_BUFFER		sound;		// �T�E���h�o�b�t�@
	};
	// MP3�t�H�[�}�b�g���
	struct MP3FormatInfo
	{
		DWORD	offset;		// �I�t�Z�b�g
		DWORD	dataSize;	// �f�[�^�T�C�Y
	};
	// MP3�t���[�����
	struct MP3FrameInfo
	{
		BYTE	channel;	// �`�����l����
		BYTE	padding;	// �p�f�B���O
		DWORD	sampleRate;	// �T���v�����O���[�g
		DWORD	bitRate;	// �r�b�g���[�g
		DWORD	frameSize;	// �t���[���T�C�Y
	};
public:
	typedef std::pair<std::string, SoundData> SoundKey;	// �T�E���h�L�[
	typedef std::map<std::string, SoundData> SoundList;	// �T�E���h���X�g
public:
	static HRESULT Init();
	static void Uninit();

	static XAUDIO2_BUFFER* Load(const char* file, bool loop = false);				// �T�E���h�f�[�^�ǂݍ���
	static IXAudio2SourceVoice* Play(XAUDIO2_BUFFER* pSound, bool loopFlg = false);	// �T�E���h�Đ�
private:
	static HRESULT LoadWav(const char* file, SoundData* pData);
	static HRESULT LoadMP3(const char* file, SoundData* pData);
	static DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo* pFormat);
	static DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo* pFrame);
	static DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo* pFrame, SoundData* pData);
private:
	static inline IXAudio2*					m_pXAudio = nullptr;		// XAudio2(�����Ǘ�)
	static inline IXAudio2MasteringVoice*	m_pMasterVoice = nullptr;	// �}�X�^�[�{�C�X(�����o��)
	static inline SoundList					m_SoundList;				// �T�E���h���X�g
};
