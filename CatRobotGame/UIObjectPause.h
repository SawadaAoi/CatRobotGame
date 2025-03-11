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

// =============== �N���X��` =====================
class UIObjectPause :
    public UIObjectBase
{
public:
	UIObjectPause(SceneBase* pScene);
	void InitLocal() override;


	DEFINE_UI_OBJECT_TYPE(UIObjectPause)
private:
	void FuncBackToStageSelect();	// �X�e�[�W�I���ɖ߂�
	void FuncDispOperation();		// ��������\��
private:
	UIObjectSelectMenu* m_pSelectMenuUI;	// �Z���N�g���j���[UI
};

