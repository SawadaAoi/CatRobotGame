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
#include "UIObjectBase.h"
#include "UIObjectText.h"
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"
#include "UIComponentText.h"

#include "SceneBase.h"
#include "SceneManager.h"
#include "TextureManager.h"
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
	, m_pBG(nullptr)
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
	// �}�X�N�̐ݒ�(�Q�[����ʂ𔖂����ŕ���)
	GetSprite()->SetColor(ColorVec3::BLACK);
	GetSprite()->SetAlpha(0.4f);
	Vector2<float> vScreenSize;
	vScreenSize.x = static_cast<float>(WINDOW_INST.GetScreenSize().nWidth);
	vScreenSize.y = static_cast<float>(WINDOW_INST.GetScreenSize().nHeight);
	GetTransform()->SetScale(vScreenSize);
	SetDrawPriority(-2);

	// ���o���e�L�X�g�̏�����
	m_pTitleText = m_pOwnerScene->AddSceneUI<UIObjectText>("PauseTitleText");
	m_pTitleText->GetCompText()->SetFontType(FontType::Letrogo);
	m_pTitleText->GetCompText()->SetText("�|�[�Y");
	m_pTitleText->GetTransform()->SetPosition({ 0.0f, 150.0f });
	AddChildUI(m_pTitleText);

	// �|�[�Y���j���[UI�̏�����
	m_pBG = m_pOwnerScene->AddSceneUI<UIObjectBase>("PauseBG");
	m_pBG->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_FRAME_3));
	m_pBG->GetTransform()->SetScale({ 600.0f, 400.0f });
	m_pBG->SetDrawPriority(-1);
	AddChildUI(m_pBG);

	// ���j���[UI�̏�����
	m_pSelectMenuUI = m_pOwnerScene->AddSceneUI<UIObjectSelectMenu>("SelectMenuUI");
	m_pSelectMenuUI->AddMenu("�X�e�[�W�Z���N�g�ɂ��ǂ�", [this]() {FuncBackToStageSelect(); });
	m_pSelectMenuUI->AddMenu("���������߂�", [this]() {FuncDispOperation(); });
	m_pSelectMenuUI->SetTextSpace(80.0f);
	m_pSelectMenuUI->SetTextSize(40.0f);
	m_pSelectMenuUI->SetTextColor(D2D1::ColorF::Black);

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
