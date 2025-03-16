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
#include "SoundManager.h"
#include "ColorVec3.h"

#include "WindowAPI.h"
#include "Input.h"


// =============== �萔��` =======================
const Vector2<float> TITLE_POS = Vector2<float>(0.0f, 150.0f);	// �^�C�g�����W
const Vector2<float> BG_SCALE = Vector2<float>(600.0f, 400.0f);	// �w�i�X�P�[��

// ���j���[UI
const float MENU_TEXT_SIZE = 40.0f;	// �e�L�X�g�T�C�Y
const float MENU_TEXT_SPACE = 80.0f;	// �e�L�X�g�Ԋu

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectPause::UIObjectPause(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pTitleText(nullptr)
	, m_pBG(nullptr)
	, m_pSelectMenuUI(nullptr)
	, m_pOperationUI(nullptr)
	, m_bOperationDisp(false)
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
	m_pTitleText->GetTransform()->SetPosition(TITLE_POS);
	AddChildUI(m_pTitleText);

	// �|�[�Y���j���[UI�̏�����
	m_pBG = m_pOwnerScene->AddSceneUI<UIObjectBase>("PauseBG");
	m_pBG->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_FRAME_3));
	m_pBG->GetTransform()->SetScale(BG_SCALE);
	m_pBG->SetDrawPriority(-1);
	AddChildUI(m_pBG);

	// ���j���[UI�̏�����
	m_pSelectMenuUI = m_pOwnerScene->AddSceneUI<UIObjectSelectMenu>("SelectMenuUI");
	m_pSelectMenuUI->SetTextSpace(MENU_TEXT_SPACE);
	m_pSelectMenuUI->SetTextSize(MENU_TEXT_SIZE);
	m_pSelectMenuUI->SetTextColor(D2D1::ColorF::Black);

	m_pSelectMenuUI->AddMenu("���������߂�", [this]() {FuncDispOperation(); });
	m_pSelectMenuUI->AddMenu("�X�e�[�W�Z���N�g�ɂ��ǂ�",	[this]() {FuncBackToStageSelect(); });

	AddChildUI(m_pSelectMenuUI);


	// �������UI��\��
	m_pOperationUI = m_pOwnerScene->AddSceneUI<UIObjectBase>("OperationUI");
	m_pOperationUI->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_GAME_OPERATION));
	m_pOperationUI->GetTransform()->SetScale(Vector2<float>(1200.0f, 800.0f));
	m_pOperationUI->GetSprite()->SetIsVisible(false);	// ��\��

	AddChildUI(m_pOperationUI);

	// BGM��~
	STOP_BGM();
	STOP_SE();
}

/* ========================================
	�I���֐�
	-------------------------------------
	���e�F�I������
========================================== */
void UIObjectPause::UninitLocal()
{
	// BGM�ĊJ
	RESTART_BGM();
	RESTART_SE();
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void UIObjectPause::UpdateLocal()
{
	// ��������\�����ɃG���^�[�L�[���������烁�j���[��L����
	if (m_bOperationDisp && Input::IsKeyTrigger(VK_RETURN))
	{
		m_pSelectMenuUI->SetState(UI_ACTIVE);	// �L���������u��FuncDispOperation���Ă΂��
	}
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
	if (m_bOperationDisp)
	{
		m_pOperationUI->GetSprite()->SetIsVisible(false);	// �������UI���\��
	}
	else
	{
		m_pOperationUI->GetSprite()->SetIsVisible(true);	// �������UI��\��
		m_pSelectMenuUI->SetState(UI_PAUSE);				// ���j���[�𖳌���
	}

	m_bOperationDisp = !m_bOperationDisp;
}
