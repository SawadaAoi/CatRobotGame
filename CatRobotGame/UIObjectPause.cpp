/* ========================================
	CatRobotGame/
	------------------------------------
	UIオブジェクト(ポーズメニュー)用cpp
	------------------------------------
	UIObjectPause.cpp
========================================== */

// =============== インクルード ===================
#include "UIObjectPause.h"
#include "UIObjectSelectMenu.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"

#include "SceneBase.h"
#include "SceneManager.h"
#include "ColorVec3.h"

#include "WindowAPI.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
=========================================== */
UIObjectPause::UIObjectPause(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pSelectMenuUI(nullptr)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================== */
void UIObjectPause::InitLocal()
{
	GetSprite()->SetColor(ColorVec3::BLACK);
	GetSprite()->SetAlpha(0.1f);

	Vector2<float> vScreenSize;
	vScreenSize.x = static_cast<float>(WINDOW_INST.GetScreenSize().nWidth);
	vScreenSize.y = static_cast<float>(WINDOW_INST.GetScreenSize().nHeight);
	GetTransform()->SetScale(vScreenSize);

	SetDrawPriority(-1);

	m_pSelectMenuUI = m_pOwnerScene->AddSceneUI<UIObjectSelectMenu>("SelectMenuUI");
	m_pSelectMenuUI->AddMenu("ステージセレクトにもどる", [this]() {FuncBackToStageSelect(); });
	m_pSelectMenuUI->AddMenu("そうさせつめい", [this]() {FuncDispOperation(); });
	m_pSelectMenuUI->SetTextSpace(100.0f);
	m_pSelectMenuUI->SetTextColor(D2D1::ColorF::White);

	AddChildUI(m_pSelectMenuUI);
}


/* ========================================
	メニュー(ステージセレクト)関数
	-------------------------------------
	内容：ステージセレクトに戻るを押した時の処理
========================================== */
void UIObjectPause::FuncBackToStageSelect()
{
	SceneManager::ChangeScene("SceneStageSelect");
}

/* ========================================
	メニュー(操作説明)関数
	-------------------------------------
	内容：操作説明を押した時の処理
========================================== */
void UIObjectPause::FuncDispOperation()
{
}
