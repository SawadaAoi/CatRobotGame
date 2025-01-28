/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト(テキスト)用ヘッダ
	------------------------------------
	説明：テキストを表示するUIオブジェクト
	------------------------------------
	UIObjectText.h
========================================== */
#pragma once

// =============== インクルード =====================
#include "UIObjectBase.h"

// =============== 前方宣言 =====================
class UIComponentText;

// =============== クラス定義 =====================
class UIObjectText :
    public UIObjectBase
{
public:
	struct S_SaveData
	{
		char sText[256];	// テキスト
	};
public:
	UIObjectText(SceneBase* pScene);

	void InitLocal() override;

	void OutPutLocalData(std::ofstream& file) override;
	void InputLocalData(std::ifstream& file) override;

	// ゲッター
	std::string GetText();
	UIComponentText* GetCompText();

	// セッター
	void SetText(std::string sText);
	

	DEFINE_UI_OBJECT_TYPE(UIObjectText)

private:
	UIComponentText* m_pCompText;	// テキストコンポーネント
};

