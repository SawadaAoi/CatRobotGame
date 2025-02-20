/* ========================================
	CatRobotGame/
	------------------------------------
	UIオブジェクト(フェード)用cpp
	------------------------------------
	UIObjectFade.cpp
========================================== */

// =============== インクルード ===================
#include "UIObjectFade.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"

#include "TextureManager.h"
#include "ShaderManager.h"

#include "WindowAPI.h"

// =============== 定数定義 =======================
const Vector3<float> COLOR_BLACK = { 0.0f, 0.0f, 0.0f };


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
=========================================== */
UIObjectFade::UIObjectFade(SceneBase* pScene)
	:UIObjectBase(pScene)
	, m_eFadeType(FADE_NONE)
	, m_fFadeTime(0.0f)
	, m_fRatio(0.0f)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================== */
void UIObjectFade::InitLocal()
{
	m_pCompSprite->SetColor(COLOR_BLACK);
	Vector2<float> vTexSize;
	vTexSize.x = static_cast<float>(WINDOW_INST.GetScreenSize().nWidth);
	vTexSize.y = static_cast<float>(WINDOW_INST.GetScreenSize().nHeight);
	m_pCompTransform->SetScale(vTexSize);

}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================== */
void UIObjectFade::UpdateLocal()
{
	switch (m_eFadeType)
	{
	case FADE_NONE:	m_pCompSprite->SetIsVisible(false);	break;
	case FADE_IN:	FadeIn();							break;
	case FADE_OUT:	FadeOut();							break;
	}
}

/* ========================================
	フェード開始関数
	-------------------------------------
	内容：フェード開始
	-------------------------------------
	引数1：フェードタイプ
	引数2：フェード時間
========================================== */
void UIObjectFade::StartFade(E_FadeType eFadeType, float fFadeTime)
{
	m_eFadeType = eFadeType;
	m_fFadeTime = fFadeTime;
	switch (m_eFadeType)
	{
	case UIObjectFade::FADE_NONE:
		break;
	case UIObjectFade::FADE_IN:
		m_fRatio = 1.0f;

		m_pCompSprite->SetAlpha(m_fRatio);
		m_pCompSprite->SetIsVisible(true);
		break;
	case UIObjectFade::FADE_OUT:
		m_fRatio = 0.0f;
		m_pCompSprite->SetAlpha(m_fRatio);
		m_pCompSprite->SetIsVisible(true);
		break;
	}
}

/* ========================================
	フェードイン関数
	-------------------------------------
	内容：フェードイン処理
========================================== */
void UIObjectFade::FadeIn()
{
	m_fRatio -= 1.0f / m_fFadeTime * DELTA_TIME;
	if (m_fRatio <= 0.0f)
	{
		m_fRatio = 0.0f;
		m_eFadeType = FADE_NONE;

	}
	m_pCompSprite->SetAlpha(m_fRatio);
}

/* ========================================
	フェードアウト関数
	-------------------------------------
	内容：フェードアウト処理
========================================== */
void UIObjectFade::FadeOut()
{
	m_fRatio += 1.0f / m_fFadeTime * DELTA_TIME;
	if (m_fRatio >= 1.0f)
	{
		m_fRatio = 1.0f;
		m_eFadeType = FADE_NONE;

	}
	m_pCompSprite->SetAlpha(m_fRatio);
}

/* ========================================
	ゲッター(フェード種類)関数
	-------------------------------------
	戻値：E_FadeType 現在のフェード種類
=========================================== */
UIObjectFade::E_FadeType UIObjectFade::GetFadeType()
{
	return m_eFadeType;
}
