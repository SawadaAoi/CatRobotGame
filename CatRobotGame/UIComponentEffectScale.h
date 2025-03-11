/* ========================================
	DX22Base/
	------------------------------------
	UI�R���|�[�l���g(�g�k�G�t�F�N�g)�p�w�b�_
	------------------------------------
	�����F�������g�k����G�t�F�N�g
	------------------------------------
	UIComponentEffectScale.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIComponentBase.h"

// =============== �N���X =======================
class UIComponentText;


// =============== �N���X =======================
class UIComponentEffectScale :
    public UIComponentBase
{
public:
	UIComponentEffectScale(UIObjectBase* pOwner);
	virtual void Init() override;
	virtual void Update() override;

	// �Q�b�^�[
	bool GetOnEffect();

	// �Z�b�^�[
	void SetOnEffect(bool bOnEffect);
	void SetBaseFontSize(float fBaseFontSize);

#ifdef _DEBUG
	void Debug(DebugUI::Window& window) override;
#endif // _DEBUG

	DEFINE_UI_COMPONENT_TYPE
private:
	UIComponentText* m_pCompText;	// �e�L�X�g�R���|�[�l���g

	bool m_bOnEffect;				// �G�t�F�N�gON/OFF

	float m_fBaseFontSize;			// ��{�̃t�H���g�T�C�Y

	float m_fAnimCnt;				// �A�j���[�V�����J�E���g
	float m_fAnimSpeed;				// �A�j���[�V�������x
	float m_fAnimRange;				// �A�j���[�V�����͈�
};

