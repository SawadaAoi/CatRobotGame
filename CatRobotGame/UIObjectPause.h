/* ========================================
	CatRobotGame/
	------------------------------------
	UIオブジェクト(ポーズメニュー)用ヘッダ
	------------------------------------
	説明：ポーズメニューのUIオブジェクト
	------------------------------------
	UIObjectPause.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIObjectBase.h"


// =============== 前方宣言 =======================
class UIObjectSelectMenu;
class UIObjectText;

// =============== クラス定義 =====================
class UIObjectPause :
    public UIObjectBase
{
public:
	UIObjectPause(SceneBase* pScene);
	void InitLocal() override;
	void UninitLocal() override;
	void UpdateLocal() override;

	DEFINE_UI_OBJECT_TYPE(UIObjectPause)
private:
	void FuncBackToStageSelect();	// ステージ選択に戻る
	void FuncDispOperation();		// 操作説明表示
private:
	UIObjectText* m_pTitleText;				// タイトルテキスト
	UIObjectSelectMenu* m_pSelectMenuUI;	// セレクトメニューUI
	UIObjectBase* m_pBG;
	UIObjectBase* m_pOperationUI;

	bool m_bOperationDisp;	// 操作説明表示フラグ
};

