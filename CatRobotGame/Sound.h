/* ========================================
	CatRobotGame/
	------------------------------------
	音声用ヘッダ
	------------------------------------
	説明：音声の読み込み、再生を行う
		　InitSound関数をLoadTexture関数より後に呼び出すとエラー
		　※内部でCOMオブジェクトを利用するため
		　リスナー
		　 音を聞くための「耳」に相当。3Dサウンドで必要。
		　ソース
		　 音を発する「音源」に相当。スピーカー。XAudio2ではVoiceと呼ばれる。
		　バッファ
		　 音データを格納しておくバッファ。WAVファイル、OGGファイルなどからロード。
	------------------------------------
	Sound.h
========================================== */
#pragma once


// =============== インクルード ===================
#include <map>
#include <string>
#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

// =============== クラス定義 =====================
class Sound
{
public:
	// サウンドデータ
	struct SoundData
	{
		WAVEFORMATEX		format;		// WAVフォーマット
		BYTE*				pBuffer;	// サウンドデータ
		DWORD				bufSize;	// データサイズ
		XAUDIO2_BUFFER		sound;		// サウンドバッファ
	};
	// MP3フォーマット情報
	struct MP3FormatInfo
	{
		DWORD	offset;		// オフセット
		DWORD	dataSize;	// データサイズ
	};
	// MP3フレーム情報
	struct MP3FrameInfo
	{
		BYTE	channel;	// チャンネル数
		BYTE	padding;	// パディング
		DWORD	sampleRate;	// サンプリングレート
		DWORD	bitRate;	// ビットレート
		DWORD	frameSize;	// フレームサイズ
	};
public:
	typedef std::pair<std::string, SoundData> SoundKey;	// サウンドキー
	typedef std::map<std::string, SoundData> SoundList;	// サウンドリスト
public:
	static HRESULT Init();
	static void Uninit();

	static XAUDIO2_BUFFER* Load(const char* file, bool loop = false);				// サウンドデータ読み込み
	static IXAudio2SourceVoice* Play(XAUDIO2_BUFFER* pSound, bool loopFlg = false);	// サウンド再生
private:
	static HRESULT LoadWav(const char* file, SoundData* pData);
	static HRESULT LoadMP3(const char* file, SoundData* pData);
	static DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo* pFormat);
	static DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo* pFrame);
	static DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo* pFrame, SoundData* pData);
private:
	static inline IXAudio2*					m_pXAudio = nullptr;		// XAudio2(音声管理)
	static inline IXAudio2MasteringVoice*	m_pMasterVoice = nullptr;	// マスターボイス(音声出力)
	static inline SoundList					m_SoundList;				// サウンドリスト
};
