/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g(�Z���N�g���j���[)�p�w�b�_
	------------------------------------
	�����F�c�ɕ��ׂ�ꂽ���j���[��\������UI�I�u�W�F�N�g
		�@���^�C�g����ʂȂǂŎg�p
	------------------------------------
	UIObjectSelectMenu.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIObjectBase.h"
#include <functional>
#include "DirectWriteCustomFont.h"

// =============== �O���錾 ===================
class UIObjectText;

// =============== �N���X��` ===================
class UIObjectSelectMenu :
    public UIObjectBase
{
public:
	// ���j���[�֐��^
    using MenuFunc = std::function<void()>;
public:
	UIObjectSelectMenu(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	void AddMenu(std::string sName, MenuFunc func);

	// �Q�b�^�[
	int GetSelectNum() const;

	// �Z�b�^�[
	void SetSelectNum(int nSelectNum);
	void SetMenuFunc(int nSelectNum, std::string sName, MenuFunc func);
	void SetTextSpace(float fSpace);
	void SetTextSize(int fSize);
	void SetTextFont(FontType font);
	void SetTextColor(D2D1::ColorF color);

	DEFINE_UI_OBJECT_TYPE(UIObjectSelectMenu)
private:
	void InitText();
	void InitAllText();
private:
	std::vector<MenuFunc>		m_MenuFuncs;	// ���j���[�֐�(�I�������Ƃ��Ɏ��s����)
	std::vector<std::string>	m_MenuNames;	// ���j���[��
	std::vector<UIObjectText*>	m_pSelectMenu;	// ���j���[�e�L�X�g

	int m_nSelectNum;		// �I��ԍ�
	int m_nSelectNumOld;	// �I��ԍ�(�O��)

	int m_nSelectNumMax;	// �I���ő吔

	float			m_vTextSpace;	// �e�L�X�g�Ԋu
	int				m_fTextSize;	// �e�L�X�g�T�C�Y
	FontType		m_fTextFont;	// �e�L�X�g�t�H���g
	D2D1::ColorF	m_TextColor;	// �e�L�X�g�J���[

};

