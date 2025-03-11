/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�|�[�Y���j���[)�pcpp
	------------------------------------
	UIObjectPause.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UIObjectPause.h"
#include "UIObjectSelectMenu.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"

#include "SceneBase.h"
#include "SceneManager.h"
#include "ColorVec3.h"

#include "WindowAPI.h"

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectPause::UIObjectPause(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pSelectMenuUI(nullptr)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void UIObjectPause::InitLocal()
{
	GetSprite()->SetColor(ColorVec3::BLACK);
	GetSprite()->SetAlpha(0.1f);

	Vector2<float> vScreenSize;
	vScreenSize.x = static_cast<float>(WINDOW_INST.GetScreenSize().nWidth);
	vScreenSize.y = static_cast<float>(WINDOW_INST.GetScreenSize().nHeight);
	GetTransform()->SetScale(vScreenSize);

	SetDrawPriority(-1);

	m_pSelectMenuUI = m_pOwnerScene->AddSceneUI<UIObjectSelectMenu>("SelectMenuUI");
	m_pSelectMenuUI->AddMenu("�X�e�[�W�Z���N�g�ɂ��ǂ�", [this]() {FuncBackToStageSelect(); });
	m_pSelectMenuUI->AddMenu("���������߂�", [this]() {FuncDispOperation(); });
	m_pSelectMenuUI->SetTextSpace(100.0f);
	m_pSelectMenuUI->SetTextColor(D2D1::ColorF::White);

	AddChildUI(m_pSelectMenuUI);
}


/* ========================================
	���j���[(�X�e�[�W�Z���N�g)�֐�
	-------------------------------------
	���e�F�X�e�[�W�Z���N�g�ɖ߂�����������̏���
========================================== */
void UIObjectPause::FuncBackToStageSelect()
{
	SceneManager::ChangeScene("SceneStageSelect");
}

/* ========================================
	���j���[(�������)�֐�
	-------------------------------------
	���e�F������������������̏���
========================================== */
void UIObjectPause::FuncDispOperation()
{
}
