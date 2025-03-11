/* ========================================
	DX22Base/
	------------------------------------
	UI�R���|�[�l���g(�g�k�G�t�F�N�g)�pcpp
	------------------------------------
	UIComponentEffectScale.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UIComponentEffectScale.h"
#include "UIComponentText.h"
#include "UIObjectBase.h"

// =============== �萔��` =======================
const float DEFAULT_ANIME_SPEED = 5.0f;
const float DEFAULT_ANIME_RANGE = 0.2f;

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F�����I�u�W�F�N�g
=========================================== */
UIComponentEffectScale::UIComponentEffectScale(UIObjectBase* pOwner)
	: UIComponentBase(pOwner, UIOrderSelectionScaler)
	, m_pCompText(nullptr)
	, m_bOnEffect(false)
	, m_fAnimCnt(0.0f)
	, m_fAnimSpeed(DEFAULT_ANIME_SPEED)
	, m_fAnimRange(DEFAULT_ANIME_RANGE)
	, m_fBaseFontSize(0.0f)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
=========================================== */
void UIComponentEffectScale::Init()
{
	m_pCompText = m_pOwnerObj->GetComponent<UIComponentText>();

	if (m_pCompText) m_fBaseFontSize = m_pCompText->GetFontSize();
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void UIComponentEffectScale::Update()
{
	// �e�L�X�g�R���|�[�l���g���Ȃ��ꍇ�͎擾
	if (!m_pCompText)
	{
		m_pCompText = m_pOwnerObj->GetComponent<UIComponentText>();
		if (m_pCompText) m_fBaseFontSize = m_pCompText->GetFontSize();
		return;	
	}

	// �G�t�F�N�g�������̏ꍇ�͏�����
	if (!m_bOnEffect)
	{
		m_fAnimCnt = 0.0f;							// �J�E���g��������
		m_pCompText->SetFontSize(m_fBaseFontSize);	// �e�L�X�g�̃T�C�Y��������
		return;
	}

	m_fAnimCnt += DELTA_TIME;

	float fScale = 1.0f + sinf(m_fAnimCnt * m_fAnimSpeed) * m_fAnimRange;	// �g�k�l
	m_pCompText->SetFontSize(m_fBaseFontSize * fScale);						// �e�L�X�g�̃T�C�Y��ύX
}

/* ========================================
	�Q�b�^�[(�G�t�F�N�g�L���t���O)�֐�
	-------------------------------------
	�ߒl�Fbool �G�t�F�N�g�L���t���O
=========================================== */
bool UIComponentEffectScale::GetOnEffect()
{
	return m_bOnEffect;
}

/* ========================================
	�Z�b�^�[(�G�t�F�N�g�L���t���O)�֐�
	-------------------------------------
	����1�Fbool �G�t�F�N�g�L���t���O
=========================================== */
void UIComponentEffectScale::SetOnEffect(bool bOnEffect)
{
	m_bOnEffect = bOnEffect;
}

/* ========================================
	�Z�b�^�[(��{�t�H���g�T�C�Y)�֐�
	-------------------------------------
	����1�Ffloat ��{�t�H���g�T�C�Y
=========================================== */
void UIComponentEffectScale::SetBaseFontSize(float fBaseFontSize)
{
	m_fBaseFontSize = fBaseFontSize;
}

#ifdef _DEBUG
/* ========================================
	�f�o�b�O�֐�
	-------------------------------------
	���e�F�f�o�b�O�p�̏���
	-------------------------------------
	����1�F�E�B���h�E	DebugUI::Window&
=========================================== */
void UIComponentEffectScale::Debug(DebugUI::Window& window)
{
	using namespace DebugUI;

	Item* pGroupUIEffectScale = Item::CreateGroup("UI_EffectScale");

	pGroupUIEffectScale->AddGroupItem(Item::CreateBind("OnEffect", Item::Bool, &m_bOnEffect));

	pGroupUIEffectScale->AddGroupItem(Item::CreateValue("AnimCnt", Item::Float));

	pGroupUIEffectScale->AddGroupItem(Item::CreateBind("AnimeSpeed", Item::Float, &m_fAnimSpeed));
	pGroupUIEffectScale->AddGroupItem(Item::CreateBind("AnimeRange", Item::Float, &m_fAnimRange));


	window.AddItem(pGroupUIEffectScale);

}

#endif // _DEBUG