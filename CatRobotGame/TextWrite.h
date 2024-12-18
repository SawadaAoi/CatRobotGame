/* ========================================
	DX22/Dropin
	------------------------------------
	文字描画用ヘッダ
	------------------------------------
	説明:文字を画面に描画するためのクラス
	------------------------------------
	TextWrite.h
========================================== */
#pragma once

// =============== インクルード ===================
#include <memory>
#include "DirectWriteCustomFont.h"
#include <string>
#include "Vector2.h"
#include "WindowAPI.h"
#include "SettingWindowAPI.h"

// =============== 定数定義 =======================
#define TEXT_WRITE TextWrite::GetInstance() 

namespace SCREEN_POS	// 位置
{
	const float RIGHT	=  WindowConfig::SCREEN_WIDTH  / 2;	// 右
	const float LEFT	= -WindowConfig::SCREEN_WIDTH  / 2;	// 左
	const float TOP		=  WindowConfig::SCREEN_HEIGHT / 2;	// 上
	const float BOTTOM	= -WindowConfig::SCREEN_HEIGHT / 2;	// 下

	// 画面位置(XY座標)
	const Vector2<float> LEFT_TOP		= { LEFT ,	TOP };		// 画面左上
	const Vector2<float> RIGHT_TOP		= { RIGHT , TOP };		// 画面右上
	const Vector2<float> LEFT_BOTTOM	= { LEFT ,	BOTTOM };	// 画面左下
	const Vector2<float> RIGHT_BOTTOM	= { RIGHT , BOTTOM };	// 画面右下
	const Vector2<float> CENTER			= { 0.0f, 0.0f };		// 画面中央
}

// =============== 列挙体定義 =====================
enum E_Pivot
{
	LEFT_TOP,
	LEFT_BOTTOM,
	RIGHT_TOP,
	RIGHT_BOTTOM,
	CENTER,
	LEFT_CENTER,
	RIGHT_CENTER,
};

// =============== クラス定義 =====================
class TextWrite
{
public:
	static TextWrite& GetInstance();
    void DrawWriteText(const std::string text = "入力無し", 
		Vector2<float> pos = {0.0f,0.0f}, E_Pivot pivot = E_Pivot::LEFT_TOP, bool bScreenOutCheck = true);

	void SetFontType(FontType type);
	void SetFontColor(D2D1::ColorF color);
	void SetFontWeight(DWRITE_FONT_WEIGHT weight);
	void SetFontSize(float size);
	
private:
    TextWrite();
    TextWrite(const TextWrite&) = delete;

	void operator=(const TextWrite&) = delete;

	Vector2<float> AdjustPosOriginCenter(Vector2<float> pos);
	Vector2<float> ScreenOutCheck(Vector2<float> pos, std::string text);
	Vector2<float> AdjustPivot(Vector2<float> pos, E_Pivot pivot, std::string text);

	float GetTextWidth(std::string text);

    static inline std::unique_ptr<DirectWriteCustomFont> m_pWriteObj;
	static inline FontData m_pFontData;
};
