/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g(�t�F�[�h)�p�w�b�_
	------------------------------------
	�����F�V�[���؂�ւ����̃t�F�[�h�C���E�A�E�g���s��
	------------------------------------
	UIObjectFade.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIObjectBase.h"

// =============== �萔��` =======================
#define FADE_MODE_NONE UIObjectFade::E_FadeType::FADE_NONE
#define FADE_MODE_IN UIObjectFade::E_FadeType::FADE_IN
#define FADE_MODE_OUT UIObjectFade::E_FadeType::FADE_OUT

// =============== �N���X ===================
class UIObjectFade :
    public UIObjectBase
{
public:
	enum E_FadeType
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT,
	};

public:
	UIObjectFade(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	virtual void StartFade(E_FadeType eFadeType, float fFadeTime);

	// �Q�b�^�[
	E_FadeType GetFadeType();
private:
	void FadeIn();
	void FadeOut();
protected:
	E_FadeType	m_eFadeType;
	float		m_fFadeTime;
	float		m_fRatio;

};

