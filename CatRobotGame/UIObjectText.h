/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g(�e�L�X�g)�p�w�b�_
	------------------------------------
	�����F�e�L�X�g��\������UI�I�u�W�F�N�g
	------------------------------------
	UIObjectText.h
========================================== */
#pragma once

// =============== �C���N���[�h =====================
#include "UIObjectBase.h"

// =============== �O���錾 =====================
class UIComponentText;

// =============== �N���X��` =====================
class UIObjectText :
    public UIObjectBase
{
public:
	struct S_SaveData
	{
		char	sText[256];			// �e�L�X�g
		int		nFontSize;			// �t�H���g�T�C�Y
		int		eFontType;			// �t�H���g�^�C�v
		int     nFontColor[4];		// �t�H���g�J���[
		int		nWeight;			// �t�H���g�E�F�C�g
		int		ePivot;				// �s�{�b�g
		bool	bScreenOutCheck;	// ��ʊO�`�F�b�N
	};
public:
	UIObjectText(SceneBase* pScene);

	void InitLocal() override;

	void OutPutLocalData(std::ofstream& file) override;
	void InputLocalData(std::ifstream& file) override;

	// �Q�b�^�[
	std::string GetText();
	UIComponentText* GetCompText();

	// �Z�b�^�[
	void SetText(std::string sText);
	

	DEFINE_UI_OBJECT_TYPE(UIObjectText)

private:
	UIComponentText* m_pCompText;	// �e�L�X�g�R���|�[�l���g
};

