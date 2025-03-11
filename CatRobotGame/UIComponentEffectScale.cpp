/* ========================================
	DX22Base/
	------------------------------------
	UIコンポーネント(拡縮エフェクト)用cpp
	------------------------------------
	UIComponentEffectScale.cpp
========================================== */

// =============== インクルード ===================
#include "UIComponentEffectScale.h"
#include "UIComponentText.h"
#include "UIObjectBase.h"

// =============== 定数定義 =======================
const float DEFAULT_ANIME_SPEED = 5.0f;
const float DEFAULT_ANIME_RANGE = 0.2f;

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所持オブジェクト
=========================================== */
UIComponentEffectScale::UIComponentEffectScale(UIObjectBase* pOwner)
	: UIComponentBase(pOwner, UIOrderSelectionScaler)
	, m_pCompText(nullptr)
	, m_bOnEffect(false)
	, m_fAnimCnt(0.0f)
	, m_fAnimSpeed(DEFAULT_ANIME_SPEED)
	, m_fAnimRange(DEFAULT_ANIME_RANGE)
	, m_fBaseFontSize(0.0f)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void UIComponentEffectScale::Init()
{
	m_pCompText = m_pOwnerObj->GetComponent<UIComponentText>();

	if (m_pCompText) m_fBaseFontSize = m_pCompText->GetFontSize();
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void UIComponentEffectScale::Update()
{
	// テキストコンポーネントがない場合は取得
	if (!m_pCompText)
	{
		m_pCompText = m_pOwnerObj->GetComponent<UIComponentText>();
		if (m_pCompText) m_fBaseFontSize = m_pCompText->GetFontSize();
		return;	
	}

	// エフェクトが無効の場合は初期化
	if (!m_bOnEffect)
	{
		m_fAnimCnt = 0.0f;							// カウントを初期化
		m_pCompText->SetFontSize(m_fBaseFontSize);	// テキストのサイズを初期化
		return;
	}

	m_fAnimCnt += DELTA_TIME;

	float fScale = 1.0f + sinf(m_fAnimCnt * m_fAnimSpeed) * m_fAnimRange;	// 拡縮値
	m_pCompText->SetFontSize(m_fBaseFontSize * fScale);						// テキストのサイズを変更
}

/* ========================================
	ゲッター(エフェクト有効フラグ)関数
	-------------------------------------
	戻値：bool エフェクト有効フラグ
=========================================== */
bool UIComponentEffectScale::GetOnEffect()
{
	return m_bOnEffect;
}

/* ========================================
	セッター(エフェクト有効フラグ)関数
	-------------------------------------
	引数1：bool エフェクト有効フラグ
=========================================== */
void UIComponentEffectScale::SetOnEffect(bool bOnEffect)
{
	m_bOnEffect = bOnEffect;
}

/* ========================================
	セッター(基本フォントサイズ)関数
	-------------------------------------
	引数1：float 基本フォントサイズ
=========================================== */
void UIComponentEffectScale::SetBaseFontSize(float fBaseFontSize)
{
	m_fBaseFontSize = fBaseFontSize;
}

#ifdef _DEBUG
/* ========================================
	デバッグ関数
	-------------------------------------
	内容：デバッグ用の処理
	-------------------------------------
	引数1：ウィンドウ	DebugUI::Window&
=========================================== */
void UIComponentEffectScale::Debug(DebugUI::Window& window)
{
	using namespace DebugUI;

	Item* pGroupUIEffectScale = Item::CreateGroup("UI_EffectScale");

	pGroupUIEffectScale->AddGroupItem(Item::CreateBind("OnEffect", Item::Bool, &m_bOnEffect));

	pGroupUIEffectScale->AddGroupItem(Item::CreateValue("AnimCnt", Item::Float));

	pGroupUIEffectScale->AddGroupItem(Item::CreateBind("AnimeSpeed", Item::Float, &m_fAnimSpeed));
	pGroupUIEffectScale->AddGroupItem(Item::CreateBind("AnimeRange", Item::Float, &m_fAnimRange));


	window.AddItem(pGroupUIEffectScale);

}

#endif // _DEBUG