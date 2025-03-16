/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�|�[�Y���j���[)�p�w�b�_
	------------------------------------
	�����F�|�[�Y���j���[��UI�I�u�W�F�N�g
	------------------------------------
	UIObjectPause.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIObjectBase.h"


// =============== �O���錾 =======================
class UIObjectSelectMenu;
class UIObjectText;

// =============== �N���X��` =====================
class UIObjectPause :
    public UIObjectBase
{
public:
	UIObjectPause(SceneBase* pScene);
	void InitLocal() override;
	void UninitLocal() override;
	void UpdateLocal() override;

	DEFINE_UI_OBJECT_TYPE(UIObjectPause)
private:
	void FuncBackToStageSelect();	// �X�e�[�W�I���ɖ߂�
	void FuncDispOperation();		// ��������\��
private:
	UIObjectText* m_pTitleText;				// �^�C�g���e�L�X�g
	UIObjectSelectMenu* m_pSelectMenuUI;	// �Z���N�g���j���[UI
	UIObjectBase* m_pBG;
	UIObjectBase* m_pOperationUI;

	bool m_bOperationDisp;	// ��������\���t���O
};

