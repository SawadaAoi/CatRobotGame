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
	セッター(テキスト)関数
	-------------------------------------
	引数：std::string		テキスト
=========================================== */
void UIObjectText::SetText(std::string sText)
{
	m_pCompText->SetText(sText);
}