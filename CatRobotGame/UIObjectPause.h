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

// =============== クラス定義 =====================
class UIObjectPause :
    public UIObjectBase
{
public:
	UIObjectPause(SceneBase* pScene);
	void InitLocal() override;


	DEFINE_UI_OBJECT_TYPE(UIObjectPause)
private:
	void FuncBackToStageSelect();	// ステージ選択に戻る
	void FuncDispOperation();		// 操作説明表示
private:
	UIObjectSelectMenu* m_pSelectMenuUI;	// セレクトメニューUI
};

