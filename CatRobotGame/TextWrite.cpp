/* ========================================
	DX22/Dropin
	------------------------------------
	文字描画用cpp
	------------------------------------
	TextWrite.cpp
========================================== */

// =============== インクルード ===================
#include "TextWrite.h"
#include "DirectXManager.h"
#include <DirectXMath.h>
#include "WindowAPI.h"

// =============== 定数 ===================
const float					DEFAULT_FONT_SIZE	= 50.0f;										// デフォルトフォントサイズ
const FontType				DEFAULT_FONT		= FontType::IPAexMin;						// デフォルトフォント
const D2D1::ColorF			DEFAULT_COLOR		= D2D1::ColorF(D2D1::ColorF::Black);			// デフォルトカラー
const DWRITE_FONT_WEIGHT	DEFAULT_FONT_WEIGHT = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;	// デフォルトフォントの太さ

const float OUT_SCREEN_ADJUST = 0.2f;			// 画面外に出た時の調整値

const float DOUBLE_BYTE_TEXT_MULTIPLE = 1.0f;	// 全角文字の横幅倍率
const float SINGLE_BYTE_TEXT_MULTIPLE = 0.5f;	// 半角文字の横幅倍率
const float TEXT_HEIGHT_MULTIPLE = 1.3f;		// 文字の高さ倍率


/* ========================================
	インスタンス(シングルトン)取得関数
	-------------------------------------
	内容：CTextWriteクラスのインスタンスを取得
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：CTextWriteクラスのインスタンス
=========================================== */
TextWrite& TextWrite::GetInstance()
{
	static TextWrite instance;
	return instance;
}

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：無し
=========================================== */
TextWrite::TextWrite()
{
	// DirectWrite用コンポーネント作成
	m_pWriteObj = std::make_unique<DirectWriteCustomFont>(&m_pFontData);

	// 初期化
	m_pWriteObj->Init(DirectXManager::GetSwapChain());

	// フォントデータを改変
	m_pFontData.fontSize		= DEFAULT_FONT_SIZE;							// フォントサイズ
	m_pFontData.fontWeight		= DEFAULT_FONT_WEIGHT;							// フォントの太さ		
	m_pFontData.Color			= D2D1::ColorF(DEFAULT_COLOR);					// フォントの色
	m_pFontData.font			= m_pWriteObj->GetFontName(DEFAULT_FONT);		// フォント名
	m_pFontData.shadowColor		= D2D1::ColorF(D2D1::ColorF::White);			// 影の色	
	m_pFontData.shadowOffset	= D2D1::Point2F(5.0f, -5.0f);					// 影のオフセット	

	// フォントをセット
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	文字描画関数
	-------------------------------------
	内容：文字を描画する
	-------------------------------------
	引数1：描画する文字列
	引数2：描画位置
	引数3：中心位置
	引数4：画面外チェック
=========================================== */
void TextWrite::DrawWriteText(const std::string text, Vector2<float> pos, E_Pivot pivot, bool bScreenOutCheck)
{
	Vector2<float> fAdjustPos;
	fAdjustPos = AdjustPivot(pos, pivot, text);	// ピボット調整

	// 画面外調整
	if(bScreenOutCheck)	fAdjustPos = ScreenOutCheck(fAdjustPos, text);		

	fAdjustPos = AdjustPosOriginCenter(fAdjustPos);		// 原点を画面中央に調整

	m_pWriteObj->DrawString(text, fAdjustPos, D2D1_DRAW_TEXT_OPTIONS_NONE);
}


/* ========================================
	原点中央調整関数
	-------------------------------------
	内容：原点を画面中央に調整
	-------------------------------------
	引数1：位置
	-------------------------------------
	戻値：調整後の位置
=========================================== */
Vector2<float> TextWrite::AdjustPosOriginCenter(Vector2<float> pos)
{
	Vector2<float> rePos = {	// 原点が画面中央になるように調整
		pos.x + (WINDOW_INST.GetScreenSize().nWidth / 2),
		-pos.y + (WINDOW_INST.GetScreenSize().nHeight / 2)
	};
	return rePos;
}

/* ========================================
	スクリーンアウトチェック関数
	-------------------------------------
	内容：画面外に出たかチェック
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
Vector2<float> TextWrite::ScreenOutCheck(Vector2<float> pos, std::string text)
{
	// テキストの終点位置
	Vector2<float> textEndPos = {
		pos.x + GetTextWidth(text),
		pos.y - m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE	// 文字の底辺の座標
	};

	// 画面外に出たら調整
	// 右端
	if (textEndPos.x > SCREEN_POS::RIGHT)
	{
		pos.x -= textEndPos.x - SCREEN_POS::RIGHT;			// 右にはみ出た分、左に戻す
	}
	// 底辺
	if (textEndPos.y < SCREEN_POS::BOTTOM)
	{
		pos.y += -(WINDOW_INST.GetScreenSize().nHeight / 2) - textEndPos.y;
	}

	return pos;
}


/* ========================================
	ピボット調整関数
	-------------------------------------
	内容：ピボットを調整
	-------------------------------------
	引数1：位置
	引数2：ピボット
	引数3：文字列
	-------------------------------------
	戻値：調整後の位置
=========================================== */
Vector2<float> TextWrite::AdjustPivot(Vector2<float> pos, E_Pivot pivot, std::string text)
{
	Vector2<float> fAdjustPos = pos;	// 調整後の位置

	switch (pivot)
	{
	case LEFT_TOP:
		// 初期状態が左上なので調整なし
		break;
	case LEFT_BOTTOM:
		fAdjustPos.y += m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE;	// 中心位置Y座標を文字の底辺にする為に文字の座標を上にずらす
		break;
	case RIGHT_TOP:
		fAdjustPos.x -= GetTextWidth(text);	// 中心位置X座標を文字の右端にする為に文字の座標を左(横幅分)にずらす
		break;
	case RIGHT_BOTTOM:
		fAdjustPos.x -= GetTextWidth(text);		
		fAdjustPos.y += m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE;	
		break;
	case CENTER:
		fAdjustPos.x -= GetTextWidth(text) / 2;								// 文字の横幅の半分左にずらす
		fAdjustPos.y += (m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE) / 2;	// 文字の高さの半分上にずらす
		break;
	case LEFT_CENTER:
		fAdjustPos.y += (m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE) / 2;	// 文字の高さの半分上にずらす
		break;
	case RIGHT_CENTER:
		fAdjustPos.x -= GetTextWidth(text);									// 文字の横幅分左にずらす
		fAdjustPos.y += (m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE) / 2;	// 文字の高さの半分上にずらす
		break;
	}

	return fAdjustPos;
}

/* ========================================
	文字幅取得関数
	-------------------------------------
	内容：文字の横幅を取得
	-------------------------------------
	引数1：文字列
	-------------------------------------
	戻値：文字の横幅
=========================================== */
float TextWrite::GetTextWidth(std::string text)
{
	float fReWidth = 0.0f;	// 文字の横幅

	// 全ての文字分
	while (!text.empty())
	{
		if (IsDBCSLeadByte(text[0]) == 0)	// 1バイト文字(半角)
		{
			fReWidth += m_pFontData.fontSize * SINGLE_BYTE_TEXT_MULTIPLE;
			text.erase(0, 1);	// 1文字進める
		}
		else // 2バイト文字(全角)
		{
			fReWidth += m_pFontData.fontSize * DOUBLE_BYTE_TEXT_MULTIPLE;
			text.erase(0, 2);	// 2文字進める
		}
	}

	return fReWidth;
}


/* ========================================
	フォント変更関数
	-------------------------------------
	内容：フォントを変更する
	-------------------------------------
	引数1：フォントデータ
	-------------------------------------
	戻値：無し
=========================================== */
void TextWrite::SetFontType(FontType type)
{
	m_pFontData.font = m_pWriteObj->GetFontName(type);
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	フォントカラー変更関数
	-------------------------------------
	内容：フォントカラーを変更する
	-------------------------------------
	引数1：カラー
	-------------------------------------
	戻値：無し
=========================================== */
void TextWrite::SetFontColor(D2D1::ColorF color)
{
	m_pFontData.Color = color;
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	フォント太さ変更関数
	-------------------------------------
	内容：フォントの太さを変更する
	-------------------------------------
	引数1：太さ
	-------------------------------------
	戻値：無し
=========================================== */
void TextWrite::SetFontWeight(DWRITE_FONT_WEIGHT weight)
{
	m_pFontData.fontWeight = weight;
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	フォントサイズ変更関数
	-------------------------------------
	内容：フォントサイズを変更する
	-------------------------------------
	引数1：サイズ
	-------------------------------------
	戻値：無し
=========================================== */
void TextWrite::SetFontSize(float size)
{
	m_pFontData.fontSize = size;
	m_pWriteObj->SetFont(m_pFontData);
}
