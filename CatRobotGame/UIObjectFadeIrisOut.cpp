/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�t�F�[�h(�A�C���X�A�E�g))�pcpp
	------------------------------------
	UIObjectFadeIrisOut.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UIObjectFadeIrisOut.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"

#include "TextureManager.h"
#include "ShaderManager.h"

// =============== �萔��` =======================
const Vector2<float> IRIS_OUT_CIRCLE_POS = { 0.5f, 0.5f };
const float IRIS_OUT_TEXTURE_SCALE = 30.0f;
#define EASE_IN_CUBIC(t) (t * t * t)

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectFadeIrisOut::UIObjectFadeIrisOut(SceneBase* pScene)
	:UIObjectFade(pScene)
	, m_eIrisOutType(IRIS_OUT_TEXTURE)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
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
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
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
	�t�F�[�h�J�n�֐�
	-------------------------------------
	���e�F�t�F�[�h�J�n����
	-------------------------------------
	����1�F�t�F�[�h�^�C�v
	����2�F�t�F�[�h����
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
	�t�F�[�h�C���J�n�֐�
	-------------------------------------
	���e�F�t�F�[�h�C���J�n����
=========================================== */
void UIObjectFadeIrisOut::StartFadeIn()
{
	m_fRatio = 1.0f;
	m_pCompSprite->SetIsVisible(true);
}


/* ========================================
	�t�F�[�h�A�E�g�J�n�֐�
	-------------------------------------
	���e�F�t�F�[�h�A�E�g�J�n����
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
	�t�F�[�h�C���֐�
	-------------------------------------
	���e�F�t�F�[�h�C������
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
	�t�F�[�h�A�E�g�֐�
	-------------------------------------
	���e�F�t�F�[�h�A�E�g����
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
	�Z�b�^�[(�A�C���X�A�E�g���)�֐�
	-------------------------------------
	�����FE_IrisOutType�@�A�C���X�A�E�g���
=========================================== */
void UIObjectFadeIrisOut::SetIrisOutType(E_IrisOutType eIrisOutType)
{
	m_eIrisOutType = eIrisOutType;
}