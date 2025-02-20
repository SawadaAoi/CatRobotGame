/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�t�F�[�h)�pcpp
	------------------------------------
	UIObjectFade.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UIObjectFade.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"

#include "TextureManager.h"
#include "ShaderManager.h"

#include "WindowAPI.h"

// =============== �萔��` =======================
const Vector3<float> COLOR_BLACK = { 0.0f, 0.0f, 0.0f };


/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectFade::UIObjectFade(SceneBase* pScene)
	:UIObjectBase(pScene)
	, m_eFadeType(FADE_NONE)
	, m_fFadeTime(0.0f)
	, m_fRatio(0.0f)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
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
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
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
	�t�F�[�h�J�n�֐�
	-------------------------------------
	���e�F�t�F�[�h�J�n
	-------------------------------------
	����1�F�t�F�[�h�^�C�v
	����2�F�t�F�[�h����
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
	�t�F�[�h�C���֐�
	-------------------------------------
	���e�F�t�F�[�h�C������
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
	�t�F�[�h�A�E�g�֐�
	-------------------------------------
	���e�F�t�F�[�h�A�E�g����
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
	�Q�b�^�[(�t�F�[�h���)�֐�
	-------------------------------------
	�ߒl�FE_FadeType ���݂̃t�F�[�h���
=========================================== */
UIObjectFade::E_FadeType UIObjectFade::GetFadeType()
{
	return m_eFadeType;
}
