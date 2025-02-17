/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト(テキスト)用cpp
	------------------------------------
	UIObjectText.cpp
========================================== */

// =============== インクルード =====================
#include "UIObjectText.h"
#include "UIComponentText.h"
#include "UIComponentSprite.h"

#include "TextWrite.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
=========================================== */
UIObjectText::UIObjectText(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pCompText(nullptr)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void UIObjectText::InitLocal()
{
	m_pCompText = AddComponent<UIComponentText>();
	GetComponent<UIComponentSprite>()->SetIsVisible(false);


}

/* ========================================
	出力データ個別関数
	-------------------------------------
	内容：オブジェクト毎に出力するデータを設定
	-------------------------------------
	引数1：ファイル
=========================================== */
void UIObjectText::OutPutLocalData(std::ofstream& file)
{
	S_SaveData data;

	// テキスト
	strncpy(data.sText, m_pCompText->GetText().c_str(), sizeof(data.sText) - 1);
	data.sText[sizeof(data.sText) - 1] = '\0';
	// フォントサイズ
	data.nFontSize = m_pCompText->GetFontSize();
	// フォントタイプ
	data.eFontType = static_cast<int>(m_pCompText->GetFontType());

	// フォントカラー
	data.nFontColor[0] = static_cast<int>(m_pCompText->GetFontColor().r);
	data.nFontColor[1] = static_cast<int>(m_pCompText->GetFontColor().g);
	data.nFontColor[2] = static_cast<int>(m_pCompText->GetFontColor().b);
	data.nFontColor[3] = static_cast<int>(m_pCompText->GetFontColor().a);

	// フォントウェイト
	data.nWeight = static_cast<int>(m_pCompText->GetFontWeight());
	// ピボット
	data.ePivot = static_cast<int>(m_pCompText->GetPivot());
	// 画面外チェック
	data.bScreenOutCheck = m_pCompText->GetScreenOutCheck();

	// ファイルに書き込み
	file.write((char*)&data, sizeof(S_SaveData));
}

/* ========================================
	入力データ個別関数
	-------------------------------------
	内容：オブジェクト毎に入力するデータを設定
	-------------------------------------
	引数1：ファイル
=========================================== */
void UIObjectText::InputLocalData(std::ifstream& file)
{
	S_SaveData data;
	file.read((char*)&data, sizeof(S_SaveData));

	// テキスト
	m_pCompText->SetText(data.sText);
	// フォントサイズ
	m_pCompText->SetFontSize(data.nFontSize);
	// フォントタイプ
	m_pCompText->SetFontType(static_cast<FontType>(data.eFontType));
	// フォントカラー
	FontColor color = 0x00000000;
	color.r = data.nFontColor[0];
	color.g = data.nFontColor[1];
	color.b = data.nFontColor[2];
	color.a = data.nFontColor[3];
	m_pCompText->SetFontColor(color);
	// フォントウェイト
	m_pCompText->SetFontWeight(static_cast<DWRITE_FONT_WEIGHT>(data.nWeight));
	// ピボット
	m_pCompText->SetPivot(static_cast<E_Pivot>(data.ePivot));
	// 画面外チェック
	m_pCompText->SetScreenOutCheck(data.bScreenOutCheck);

}

/* ========================================
	ゲッター(テキスト)関数
	-------------------------------------
	戻値：std::string		テキスト
=========================================== */
std::string UIObjectText::GetText()
{
	return m_pCompText->GetText();
}

/* ========================================
	ゲッター(テキストコンポーネント)関数
	-------------------------------------
	戻値：UIComponentText*		テキストコンポーネント
=========================================== */
UIComponentText* UIObjectText::GetCompText()
{
	return m_pCompText;
}


/* ========================================
	セッター(テキスト)関数
	-------------------------------------
	引数：std::string		テキスト
=========================================== */
void UIObjectText::SetText(std::string sText)
{
	m_pCompText->SetText(sText);
}