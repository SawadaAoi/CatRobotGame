/* ========================================
	DX22Base/
	------------------------------------
	テキストコンポーネント用ヘッダ
	------------------------------------
	説明：文字を表示するコンポーネント
	------------------------------------
	UIComponentText.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIComponentBase.h"
#include "TextWrite.h"

// =============== 前方宣言 =======================
class UIComponentTransform;

// =============== 定数定義 =======================
#define FontColor D2D1::ColorF

// =============== クラス定義 =====================
class UIComponentText :
    public UIComponentBase
{
public:
    UIComponentText(UIObjectBase* pOwner);
    virtual void Init() override;
    virtual void Draw() override;

    // セッター
    void SetText(const std::string& text);
	void SetFontSize(int size);
	void SetFontType(FontType type);
	void SetFontColor(D2D1::ColorF color);
	void SetFontWeight(DWRITE_FONT_WEIGHT weight);

	// ゲッター
    std::string GetText() const;
	int GetFontSize() const;
	FontType GetFontType() const;
	D2D1::ColorF GetFontColor() const;
	DWRITE_FONT_WEIGHT GetFontWeight() const;


	DEFINE_UI_COMPONENT_TYPE
#ifdef _DEBUG
	void Debug(DebugUI::Window& window) override;
#endif // _DEBUG
private:
    UIComponentTransform* m_pCompTransform;

	std::string			m_sText;			// 表示する文字列
	int					m_nFontSize;		// フォントサイズ
	FontType			m_eFontType;		// フォントタイプ
	D2D1::ColorF		m_Color;			// フォントカラー
	DWRITE_FONT_WEIGHT	m_Weight;			// フォントウェイト
	E_Pivot				m_ePivot;			// ピボット
	bool				m_bScreenOutCheck;	// 画面外チェック


};