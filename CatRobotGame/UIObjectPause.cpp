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
#include "SoundManager.h"
#include "ColorVec3.h"

#include "WindowAPI.h"
#include "Input.h"


// =============== 定数定義 =======================
const Vector2<float> TITLE_POS = Vector2<float>(0.0f, 150.0f);	// タイトル座標
const Vector2<float> BG_SCALE = Vector2<float>(600.0f, 400.0f);	// 背景スケール

// メニューUI
const float MENU_TEXT_SIZE = 40.0f;	// テキストサイズ
const float MENU_TEXT_SPACE = 80.0f;	// テキスト間隔

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
=========================================== */
UIObjectPause::UIObjectPause(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pTitleText(nullptr)
	, m_pBG(nullptr)
	, m_pSelectMenuUI(nullptr)
	, m_pOperationUI(nullptr)
	, m_bOperationDisp(false)
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
	m_pTitleText->GetTransform()->SetPosition(TITLE_POS);
	AddChildUI(m_pTitleText);

	// ポーズメニューUIの初期化
	m_pBG = m_pOwnerScene->AddSceneUI<UIObjectBase>("PauseBG");
	m_pBG->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_FRAME_3));
	m_pBG->GetTransform()->SetScale(BG_SCALE);
	m_pBG->SetDrawPriority(-1);
	AddChildUI(m_pBG);

	// メニューUIの初期化
	m_pSelectMenuUI = m_pOwnerScene->AddSceneUI<UIObjectSelectMenu>("SelectMenuUI");
	m_pSelectMenuUI->SetTextSpace(MENU_TEXT_SPACE);
	m_pSelectMenuUI->SetTextSize(MENU_TEXT_SIZE);
	m_pSelectMenuUI->SetTextColor(D2D1::ColorF::Black);

	m_pSelectMenuUI->AddMenu("そうさせつめい", [this]() {FuncDispOperation(); });
	m_pSelectMenuUI->AddMenu("ステージセレクトにもどる",	[this]() {FuncBackToStageSelect(); });

	AddChildUI(m_pSelectMenuUI);


	// 操作説明UIを表示
	m_pOperationUI = m_pOwnerScene->AddSceneUI<UIObjectBase>("OperationUI");
	m_pOperationUI->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_GAME_OPERATION));
	m_pOperationUI->GetTransform()->SetScale(Vector2<float>(1200.0f, 800.0f));
	m_pOperationUI->GetSprite()->SetIsVisible(false);	// 非表示

	AddChildUI(m_pOperationUI);

	// BGM停止
	STOP_BGM();
	STOP_SE();
}

/* ========================================
	終了関数
	-------------------------------------
	内容：終了処理
========================================== */
void UIObjectPause::UninitLocal()
{
	// BGM再開
	RESTART_BGM();
	RESTART_SE();
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================== */
void UIObjectPause::UpdateLocal()
{
	// 操作説明表示中にエンターキーを押したらメニューを有効化
	if (m_bOperationDisp && Input::IsKeyTrigger(VK_RETURN))
	{
		m_pSelectMenuUI->SetState(UI_ACTIVE);	// 有効化した瞬間FuncDispOperationが呼ばれる
	}
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
	if (m_bOperationDisp)
	{
		m_pOperationUI->GetSprite()->SetIsVisible(false);	// 操作説明UIを非表示
	}
	else
	{
		m_pOperationUI->GetSprite()->SetIsVisible(true);	// 操作説明UIを表示
		m_pSelectMenuUI->SetState(UI_PAUSE);				// メニューを無効化
	}

	m_bOperationDisp = !m_bOperationDisp;
}
