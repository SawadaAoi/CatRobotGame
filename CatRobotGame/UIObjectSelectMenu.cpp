/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g(�Z���N�g���j���[))�pcpp
	------------------------------------
	UIObjectSelectMenu.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UIObjectSelectMenu.h"
#include "UIObjectText.h"
#include "UIComponentEffectScale.h"
#include "UIComponentTransform.h"
#include "UIComponentText.h"
#include "UIComponentSprite.h"
#include "SceneBase.h"
#include "Input.h"
#include "SoundManager.h"

// =============== �萔��` =======================
const float			DEFAULT_TEXT_SPACE	= 65.0f;
const int			DEFAULT_TEXT_SIZE	= 60;
const FontType		DEFAULT_TEXT_FONT	= FontType::Letrogo;
const D2D1::ColorF	DEFAULT_TEXT_COLOR	= D2D1::ColorF::Black;

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectSelectMenu::UIObjectSelectMenu(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_nSelectNum(0)
	, m_nSelectNumOld(1)
	, m_nSelectNumMax(0)
	, m_vTextSpace(DEFAULT_TEXT_SPACE)
	, m_fTextSize(DEFAULT_TEXT_SIZE)
	, m_fTextFont(DEFAULT_TEXT_FONT)
	, m_TextColor(DEFAULT_TEXT_COLOR)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
=========================================== */
void UIObjectSelectMenu::InitLocal()
{
	GetSprite()->SetIsVisible(false);
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void UIObjectSelectMenu::UpdateLocal()
{
	if (m_pSelectMenu.empty()) return;

	if (Input::IsKeyTrigger(VK_UP))
	{
		m_nSelectNum = (m_nSelectNum + m_nSelectNumMax - 1) % m_nSelectNumMax;

		PLAY_SE(SE_KEY::SE_MENU_CURSOR);
	}
	else if (Input::IsKeyTrigger(VK_DOWN))
	{
		m_nSelectNum = (m_nSelectNum + 1) % m_nSelectNumMax;

		PLAY_SE(SE_KEY::SE_MENU_CURSOR);
	}

	if (m_nSelectNum != m_nSelectNumOld)
	{
		m_pSelectMenu[m_nSelectNumOld]->GetComponent<UIComponentEffectScale>()->SetOnEffect(false);
		m_pSelectMenu[m_nSelectNum]->GetComponent<UIComponentEffectScale>()->SetOnEffect(true);

		m_nSelectNumOld = m_nSelectNum;
	}

	// �X�y�[�X�L�[�őI��
	if (Input::IsKeyTrigger(VK_RETURN))
	{
		m_MenuFuncs[m_nSelectNum]();

		PLAY_SE(SE_KEY::SE_MENU_DECIDE);
	}

}

/* ========================================
	���j���[�ǉ��֐�
	-------------------------------------
	���e�F�I�����j���[��ǉ�
	-------------------------------------
	����1�F���j���[��
	����2�F���j���[�֐�
=========================================== */
void UIObjectSelectMenu::AddMenu(std::string sName, MenuFunc func)
{
	m_MenuNames.push_back(sName);
	m_MenuFuncs.push_back(func);

	InitText();	
	m_nSelectNumMax++;

	InitAllText();
}

/* ========================================
	�e�L�X�g�������֐�
	-------------------------------------
	���e�F�e�L�X�g������
		�@��m_nSelectNumMax�͔z��̍Ō�̗v�f�ԍ�
=========================================== */
void UIObjectSelectMenu::InitText()
{
	// �e�L�X�gUI�I�u�W�F�N�g����
	UIObjectText* pText = 
		m_pOwnerScene->AddSceneUI<UIObjectText>("SelectMenu_" + std::to_string(m_nSelectNumMax));

	pText->SetIsSave(false);
	pText->AddComponent<UIComponentEffectScale>();

	AddChildUI(pText);

	m_pSelectMenu.push_back(pText);
}

/* ========================================
	�S�e�L�X�g�������֐�
	-------------------------------------
	���e�F�S�e�L�X�g������
		�@���Ԋu��t�H���g�T�C�Y�Ȃǂ�ύX�����Ƃ��Ɏg�p
=========================================== */
void UIObjectSelectMenu::InitAllText()
{
	// ���S�ʒu�𕶎����m�̐^�񒆂ɍ��킹��(��ɂ��炷)
	Vector2<float> vBasePos = GetTransform()->GetPosition();
	vBasePos.y += ((m_nSelectNumMax - 1) * m_vTextSpace) / 2;

	for (int i = 0; i < m_nSelectNumMax; i++)
	{
		m_pSelectMenu[i]->GetCompText()->SetText(m_MenuNames[i]); 
		Vector2<float> vPos = vBasePos;
		vPos.y -= m_vTextSpace * i;
		m_pSelectMenu[i]->GetTransform()->SetPosition(vPos);
		m_pSelectMenu[i]->GetComponent<UIComponentEffectScale>()->SetBaseFontSize(m_fTextSize);
		m_pSelectMenu[i]->GetCompText()->SetFontType(m_fTextFont);
		m_pSelectMenu[i]->GetCompText()->SetFontColor(m_TextColor);
	}
}

/* ========================================
	�Q�b�^�[(�I��ԍ�)�֐�
	-------------------------------------
	�ߒl�Fint �I��ԍ�
=========================================== */
int UIObjectSelectMenu::GetSelectNum() const
{
	return m_nSelectNum;
}

/* ========================================
	�Z�b�^�[(�I��ԍ�)�֐�
	-------------------------------------
	����1�Fint �I��ԍ�
=========================================== */
void UIObjectSelectMenu::SetSelectNum(int nSelectNum)
{
	m_nSelectNum = nSelectNum;
}

/* ========================================
	�Z�b�^�[(���j���[�֐�)�֐�
	-------------------------------------
	����1�Fint �I��ԍ�
	����2�Fstd::string ���j���[��
	����3�FMenuFunc ���j���[�֐�
=========================================== */
void UIObjectSelectMenu::SetMenuFunc(int nSelectNum, std::string sName, MenuFunc func)
{
	m_MenuNames[nSelectNum] = sName;
	m_MenuFuncs[nSelectNum] = func;

	InitAllText();
}

/* ========================================
	�Z�b�^�[(�e�L�X�g�Ԋu)�֐�
	-------------------------------------
	����1�Ffloat �e�L�X�g�Ԋu
=========================================== */
void UIObjectSelectMenu::SetTextSpace(float fSpace)
{
	m_vTextSpace = fSpace;
	InitAllText();
}

/* ========================================
	�Z�b�^�[(�e�L�X�g�T�C�Y)�֐�
	-------------------------------------
	����1�Fint �e�L�X�g�T�C�Y
=========================================== */
void UIObjectSelectMenu::SetTextSize(int fSize)
{
	m_fTextSize = fSize;
	InitAllText();
}

/* ========================================
	�Z�b�^�[(�e�L�X�g�t�H���g)�֐�
	-------------------------------------
	����1�FFontType �t�H���g�^�C�v
=========================================== */
void UIObjectSelectMenu::SetTextFont(FontType font)
{
	m_fTextFont = font;
	InitAllText();
}

/* ========================================
	�Z�b�^�[(�e�L�X�g�J���[)�֐�
	-------------------------------------
	����1�FD2D1::ColorF �J���[	
=========================================== */
void UIObjectSelectMenu::SetTextColor(D2D1::ColorF color)
{
	m_TextColor = color;
	InitAllText();
}
