/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g(�e�L�X�g)�pcpp
	------------------------------------
	UIObjectText.cpp
========================================== */

// =============== �C���N���[�h =====================
#include "UIObjectText.h"
#include "UIComponentText.h"
#include "UIComponentSprite.h"

#include "TextWrite.h"

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectText::UIObjectText(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pCompText(nullptr)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
=========================================== */
void UIObjectText::InitLocal()
{
	m_pCompText = AddComponent<UIComponentText>();
	GetComponent<UIComponentSprite>()->SetIsVisible(false);


}

/* ========================================
	�o�̓f�[�^�ʊ֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g���ɏo�͂���f�[�^��ݒ�
	-------------------------------------
	����1�F�t�@�C��
=========================================== */
void UIObjectText::OutPutLocalData(std::ofstream& file)
{
	S_SaveData data;

	// �e�L�X�g
	strncpy(data.sText, m_pCompText->GetText().c_str(), sizeof(data.sText) - 1);
	data.sText[sizeof(data.sText) - 1] = '\0';
	// �t�H���g�T�C�Y
	data.nFontSize = m_pCompText->GetFontSize();
	// �t�H���g�^�C�v
	data.eFontType = static_cast<int>(m_pCompText->GetFontType());

	// �t�H���g�J���[
	data.nFontColor[0] = static_cast<int>(m_pCompText->GetFontColor().r);
	data.nFontColor[1] = static_cast<int>(m_pCompText->GetFontColor().g);
	data.nFontColor[2] = static_cast<int>(m_pCompText->GetFontColor().b);
	data.nFontColor[3] = static_cast<int>(m_pCompText->GetFontColor().a);

	// �t�H���g�E�F�C�g
	data.nWeight = static_cast<int>(m_pCompText->GetFontWeight());
	// �s�{�b�g
	data.ePivot = static_cast<int>(m_pCompText->GetPivot());
	// ��ʊO�`�F�b�N
	data.bScreenOutCheck = m_pCompText->GetScreenOutCheck();

	// �t�@�C���ɏ�������
	file.write((char*)&data, sizeof(S_SaveData));
}

/* ========================================
	���̓f�[�^�ʊ֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g���ɓ��͂���f�[�^��ݒ�
	-------------------------------------
	����1�F�t�@�C��
=========================================== */
void UIObjectText::InputLocalData(std::ifstream& file)
{
	S_SaveData data;
	file.read((char*)&data, sizeof(S_SaveData));

	// �e�L�X�g
	m_pCompText->SetText(data.sText);
	// �t�H���g�T�C�Y
	m_pCompText->SetFontSize(data.nFontSize);
	// �t�H���g�^�C�v
	m_pCompText->SetFontType(static_cast<FontType>(data.eFontType));
	// �t�H���g�J���[
	FontColor color = 0x00000000;
	color.r = data.nFontColor[0];
	color.g = data.nFontColor[1];
	color.b = data.nFontColor[2];
	color.a = data.nFontColor[3];
	m_pCompText->SetFontColor(color);
	// �t�H���g�E�F�C�g
	m_pCompText->SetFontWeight(static_cast<DWRITE_FONT_WEIGHT>(data.nWeight));
	// �s�{�b�g
	m_pCompText->SetPivot(static_cast<E_Pivot>(data.ePivot));
	// ��ʊO�`�F�b�N
	m_pCompText->SetScreenOutCheck(data.bScreenOutCheck);

}

/* ========================================
	�Q�b�^�[(�e�L�X�g)�֐�
	-------------------------------------
	�ߒl�Fstd::string		�e�L�X�g
=========================================== */
std::string UIObjectText::GetText()
{
	return m_pCompText->GetText();
}

/* ========================================
	�Q�b�^�[(�e�L�X�g�R���|�[�l���g)�֐�
	-------------------------------------
	�ߒl�FUIComponentText*		�e�L�X�g�R���|�[�l���g
=========================================== */
UIComponentText* UIObjectText::GetCompText()
{
	return m_pCompText;
}


/* ========================================
	�Z�b�^�[(�e�L�X�g)�֐�
	-------------------------------------
	�����Fstd::string		�e�L�X�g
=========================================== */
void UIObjectText::SetText(std::string sText)
{
	m_pCompText->SetText(sText);
}