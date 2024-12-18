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
	�Z�b�^�[(�e�L�X�g)�֐�
	-------------------------------------
	�����Fstd::string		�e�L�X�g
=========================================== */
void UIObjectText::SetText(std::string sText)
{
	m_pCompText->SetText(sText);
}