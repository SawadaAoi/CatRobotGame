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
#include "UIObjectBase.h"
#include "UIObjectText.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"
#include "UIComponentText.h"

#include "SceneBase.h"
#include "SceneManager.h"
#include "TextureManager.h"
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
	, m_pBG(nullptr)
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
	// マスクの設定(ゲーム画面を薄い黒で覆う)
	GetSprite()->SetColor(ColorVec3::BLACK);
	GetSprite()->SetAlpha(0.4f);
	Vector2<float> vScreenSize;
	vScreenSize.x = static_cast<float>(WINDOW_INST.GetScreenSize().nWidth);
	vScreenSize.y = static_cast<float>(WINDOW_INST.GetScreenSize().nHeight);
	GetTransform()->SetScale(vScreenSize);
	SetDrawPriority(-2);

	// 見出しテキストの初期化
	m_pTitleText = m_pOwnerScene->AddSceneUI<UIObjectText>("PauseTitleText");
	m_pTitleText->GetCompText()->SetFontType(FontType::Letrogo);
	m_pTitleText->GetCompText()->SetText("ポーズ");
	m_pTitleText->GetTransform()->SetPosition({ 0.0f, 150.0f });
	AddChildUI(m_pTitleText);

	// ポーズメニューUIの初期化
	m_pBG = m_pOwnerScene->AddSceneUI<UIObjectBase>("PauseBG");
	m_pBG->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_FRAME_3));
	m_pBG->GetTransform()->SetScale({ 600.0f, 400.0f });
	m_pBG->SetDrawPriority(-1);
	AddChildUI(m_pBG);

	// メニューUIの初期化
	m_pSelectMenuUI = m_pOwnerScene->AddSceneUI<UIObjectSelectMenu>("SelectMenuUI");
	m_pSelectMenuUI->AddMenu("ステージセレクトにもどる", [this]() {FuncBackToStageSelect(); });
	m_pSelectMenuUI->AddMenu("そうさせつめい", [this]() {FuncDispOperation(); });
	m_pSelectMenuUI->SetTextSpace(80.0f);
	m_pSelectMenuUI->SetTextSize(40.0f);
	m_pSelectMenuUI->SetTextColor(D2D1::ColorF::Black);

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
