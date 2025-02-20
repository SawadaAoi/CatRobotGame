/* ========================================
	CatRobotGame/
	------------------------------------
	UIオブジェクト(フェード(アイリスアウト))用cpp
	------------------------------------
	UIObjectFadeIrisOut.cpp
========================================== */

// =============== インクルード ===================
#include "UIObjectFadeIrisOut.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"

#include "TextureManager.h"
#include "ShaderManager.h"

// =============== 定数定義 =======================
const Vector2<float> IRIS_OUT_CIRCLE_POS = { 0.5f, 0.5f };
const float IRIS_OUT_TEXTURE_SCALE = 30.0f;
#define EASE_IN_CUBIC(t) (t * t * t)

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
=========================================== */
UIObjectFadeIrisOut::UIObjectFadeIrisOut(SceneBase* pScene)
	:UIObjectFade(pScene)
	, m_eIrisOutType(IRIS_OUT_TEXTURE)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================= */
void UIObjectFadeIrisOut::InitLocal()
{
	__super::InitLocal();

	m_pCompSprite->SetTexture(GET_TEXTURE_DATA(TEX_KEY::FADE_IRIS_OUT));
	m_pCompSprite->SetAlpha(1.0f);

	switch (m_eIrisOutType)
	{
	case UIObjectFadeIrisOut::IRIS_OUT_CIRCLE:
		m_pCompSprite->SetPixelShader(GET_PS_DATA(PS_KEY::PS_FADE_IRIS_OUT_CIRCLE));
		break;
	case UIObjectFadeIrisOut::IRIS_OUT_TEXTURE:
		m_pCompSprite->SetPixelShader(GET_PS_DATA(PS_KEY::PS_FADE_IRIS_OUT_TEXTURE));
		break;
	}
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================= */
void UIObjectFadeIrisOut::UpdateLocal()
{
	switch (m_eFadeType)
	{
	case FADE_NONE:	m_pCompSprite->SetIsVisible(false);	break;
	case FADE_IN:	FadeIn();							break;
	case FADE_OUT:	FadeOut();							break;
	}

	float fScale = 0.0f;
	switch (m_eIrisOutType)
	{
	case UIObjectFadeIrisOut::IRIS_OUT_CIRCLE:
		fScale = 1.0f - m_fRatio;
		break;
	case UIObjectFadeIrisOut::IRIS_OUT_TEXTURE:	
		fScale = EASE_IN_CUBIC(m_fRatio) * IRIS_OUT_TEXTURE_SCALE;
		break;
	}

	float fData[3] = { IRIS_OUT_CIRCLE_POS.x, IRIS_OUT_CIRCLE_POS.y, fScale };
	m_pCompSprite->GetPixelShader()->WriteBuffer(0, fData);
}

/* ========================================
	フェード開始関数
	-------------------------------------
	内容：フェード開始処理
	-------------------------------------
	引数1：フェードタイプ
	引数2：フェード時間
=========================================== */
void UIObjectFadeIrisOut::StartFade(E_FadeType eFadeType, float fFadeTime)
{
	m_eFadeType = eFadeType;
	m_fFadeTime = fFadeTime;
	switch (m_eFadeType)
	{
	case UIObjectFade::FADE_NONE:
		break;
	case UIObjectFade::FADE_IN:
		StartFadeIn();
		break;
	case UIObjectFade::FADE_OUT:
		StartFadeOut();
		break;
	}

	switch (m_eIrisOutType)
	{
	case UIObjectFadeIrisOut::IRIS_OUT_CIRCLE:
		m_pCompSprite->SetPixelShader(GET_PS_DATA(PS_KEY::PS_FADE_IRIS_OUT_CIRCLE));
		break;
	case UIObjectFadeIrisOut::IRIS_OUT_TEXTURE:
		m_pCompSprite->SetPixelShader(GET_PS_DATA(PS_KEY::PS_FADE_IRIS_OUT_TEXTURE));
		break;
	}
}

/* ========================================
	フェードイン開始関数
	-------------------------------------
	内容：フェードイン開始処理
=========================================== */
void UIObjectFadeIrisOut::StartFadeIn()
{
	m_fRatio = 1.0f;
	m_pCompSprite->SetIsVisible(true);
}


/* ========================================
	フェードアウト開始関数
	-------------------------------------
	内容：フェードアウト開始処理
=========================================== */
void UIObjectFadeIrisOut::StartFadeOut()
{
	m_fRatio = 0.0f;
	m_pCompSprite->SetIsVisible(true);

	float fScale = 0.0f;
	switch (m_eIrisOutType)
	{
	case UIObjectFadeIrisOut::IRIS_OUT_CIRCLE:	fScale = 1.0f;	break;
	case UIObjectFadeIrisOut::IRIS_OUT_TEXTURE:	fScale = 0.0f;	break;
	}

	float fData[3] = { IRIS_OUT_CIRCLE_POS.x, IRIS_OUT_CIRCLE_POS.y, fScale };
	m_pCompSprite->GetPixelShader()->WriteBuffer(0, fData);
}

/* ========================================
	フェードイン関数
	-------------------------------------
	内容：フェードイン処理
========================================= */
void UIObjectFadeIrisOut::FadeIn()
{
	m_fRatio -= 1.0f / m_fFadeTime * DELTA_TIME;
	if (m_fRatio <= 0.0f)
	{
		m_fRatio = 0.0f;
		m_eFadeType = FADE_NONE;
	}
}

/* ========================================
	フェードアウト関数
	-------------------------------------
	内容：フェードアウト処理
========================================= */
void UIObjectFadeIrisOut::FadeOut()
{
	m_fRatio += 1.0f / m_fFadeTime * DELTA_TIME;
	if (m_fRatio >= 1.0f)
	{
		m_fRatio = 1.0f;
		m_eFadeType = FADE_NONE;
	}
}

/* ========================================
	セッター(アイリスアウト種類)関数
	-------------------------------------
	引数：E_IrisOutType　アイリスアウト種類
=========================================== */
void UIObjectFadeIrisOut::SetIrisOutType(E_IrisOutType eIrisOutType)
{
	m_eIrisOutType = eIrisOutType;
}