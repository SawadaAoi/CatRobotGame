/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g(�t�F�[�h(�A�C���X�A�E�g))�p�w�b�_
	------------------------------------
	�����F��ʂ��~�^�A�e�N�X�`���^�ŃA�C���X�A�E�g����
	------------------------------------
	UIObjectFadeIrisOut
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIObjectFade.h"

// =============== �N���X ===================
class UIObjectFadeIrisOut :
    public UIObjectFade
{
public:
	enum E_IrisOutType
	{
		IRIS_OUT_CIRCLE,
		IRIS_OUT_TEXTURE,
	};
public:
	UIObjectFadeIrisOut(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	void StartFade(E_FadeType eFadeType, float fFadeTime) override;

	// �Z�b�^�[
	void SetIrisOutType(E_IrisOutType eIrisOutType);

private:
	void StartFadeIn();
	void StartFadeOut();
	void FadeIn();
	void FadeOut();
private:
	E_IrisOutType m_eIrisOutType;
};

