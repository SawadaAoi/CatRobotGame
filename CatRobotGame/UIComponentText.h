/* ========================================
	DX22Base/
	------------------------------------
	�e�L�X�g�R���|�[�l���g�p�w�b�_
	------------------------------------
	�����F������\������R���|�[�l���g
	------------------------------------
	UIComponentText.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIComponentBase.h"
#include "TextWrite.h"

// =============== �O���錾 =======================
class UIComponentTransform;

// =============== �萔��` =======================
#define FontColor D2D1::ColorF

// =============== �N���X��` =====================
class UIComponentText :
    public UIComponentBase
{
public:
    UIComponentText(UIObjectBase* pOwner);
    virtual void Init() override;
    virtual void Draw() override;

    // �Z�b�^�[
    void SetText(const std::string& text);
	void SetFontSize(int size);
	void SetFontType(FontType type);
	void SetFontColor(D2D1::ColorF color);
	void SetFontWeight(DWRITE_FONT_WEIGHT weight);

	// �Q�b�^�[
    std::string GetText() const;
	int GetFontSize() const;
	FontType GetFontType() const;
	D2D1::ColorF GetFontColor() const;
	DWRITE_FONT_WEIGHT GetFontWeight() const;


	DEFINE_UI_COMPONENT_TYPE
#ifdef _DEBUG
	void Debug(DebugUI::Window& window) override;
#endif // _DEBUG
private:
    UIComponentTransform* m_pCompTransform;

	std::string			m_sText;			// �\�����镶����
	int					m_nFontSize;		// �t�H���g�T�C�Y
	FontType			m_eFontType;		// �t�H���g�^�C�v
	D2D1::ColorF		m_Color;			// �t�H���g�J���[
	DWRITE_FONT_WEIGHT	m_Weight;			// �t�H���g�E�F�C�g
	E_Pivot				m_ePivot;			// �s�{�b�g
	bool				m_bScreenOutCheck;	// ��ʊO�`�F�b�N


};