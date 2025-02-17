/* ========================================
	DX22Base/
	------------------------------------
	�e�L�X�g�R���|�[�l���g�pcpp
	------------------------------------
	UIComponentText.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UIComponentText.h"
#include "UIComponentTransform.h"
#include "UIObjectBase.h"
#include <string>
#include <codecvt>
#include <locale>
#include <windows.h>
#include "ObjectBase.h"

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F�����I�u�W�F�N�g
=========================================== */
UIComponentText::UIComponentText(UIObjectBase* pOwner)
	: UIComponentBase(pOwner, UIOrderText)
	, m_pCompTransform(nullptr)
	, m_sText("")
	, m_eFontType(FontType::IPAexMin)
	, m_nFontSize(50)
	, m_Color(FontColor::Black)
	, m_Weight(DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN)
	, m_ePivot(E_Pivot::CENTER)
	, m_bScreenOutCheck(true)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
=========================================== */
void UIComponentText::Init()
{
	m_pCompTransform = m_pOwnerObj->GetComponent<UIComponentTransform>();
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
=========================================== */
void UIComponentText::Draw()
{
	if (CHECK_DISP_COMPUI("UI_Text"))
	{
		if (WIN_UI_INFO["UI_Text"]["UseTextBox"].GetBool())
			m_sText = WIN_UI_INFO["UI_Text"]["Text"].GetPath();

		DirectX::XMFLOAT4 color = WIN_UI_INFO["UI_Text"]["FontColor"].GetColor();
		m_Color.r = color.x;
		m_Color.g = color.y;
		m_Color.b = color.z;
		m_Color.a = color.w;


	}


	TEXT_WRITE.SetFontType(m_eFontType);
	TEXT_WRITE.SetFontSize(m_nFontSize);
	TEXT_WRITE.SetFontColor(m_Color);
	TEXT_WRITE.SetFontWeight(m_Weight);

	TEXT_WRITE.DrawWriteText(m_sText, m_pCompTransform->GetPosition(), m_ePivot, m_bScreenOutCheck);
}



/* ========================================
	�Q�b�^�[(������)�֐�
	-------------------------------------
	�߂�l�Fstd::string ������
=========================================== */
std::string UIComponentText::GetText() const
{
	return m_sText;
}

/* ========================================
	�Q�b�^�[(�t�H���g�T�C�Y)�֐�
	-------------------------------------
	�߂�l�Fint �T�C�Y
=========================================== */
int UIComponentText::GetFontSize() const
{
	return m_nFontSize;
}

/* ========================================
	�Q�b�^�[(�t�H���g�^�C�v)�֐�
	-------------------------------------
	�߂�l�FFontType �t�H���g�^�C�v
=========================================== */
FontType UIComponentText::GetFontType() const
{
	return m_eFontType;
}

/* ========================================
	�Q�b�^�[(�t�H���g�J���[)�֐�
	-------------------------------------
	�߂�l�FD2D1::ColorF �J���[
=========================================== */
D2D1::ColorF UIComponentText::GetFontColor() const
{
	return m_Color;
}

/* ========================================
	�Q�b�^�[(�t�H���g�E�F�C�g)�֐�
	-------------------------------------
	�߂�l�FDWRITE_FONT_WEIGHT �E�F�C�g
=========================================== */
DWRITE_FONT_WEIGHT UIComponentText::GetFontWeight() const
{
	return m_Weight;
}

/* ========================================
	�Q�b�^�[(�s�{�b�g)�֐�
	-------------------------------------
	�߂�l�FE_Pivot �s�{�b�g
=========================================== */
E_Pivot UIComponentText::GetPivot() const
{
	return m_ePivot;
}

/* ========================================
	�Q�b�^�[(��ʊO�`�F�b�N)�֐�
	-------------------------------------
	�߂�l�Fbool �`�F�b�N
=========================================== */
bool UIComponentText::GetScreenOutCheck() const
{
	return m_bScreenOutCheck;
}

/* ========================================
	�Z�b�^�[(������)�֐�
	-------------------------------------
	�����Fstd::string ������
=========================================== */
void UIComponentText::SetText(const std::string& text)
{
	m_sText = text;

}

/* ========================================
	�Z�b�^�[(�t�H���g�T�C�Y)�֐�
	-------------------------------------
	�����Fint �T�C�Y
=========================================== */
void UIComponentText::SetFontSize(int size)
{
	m_nFontSize = size;
}

/* ========================================
	�Z�b�^�[(�t�H���g�^�C�v)�֐�
	-------------------------------------
	�����FFontType �t�H���g�^�C�v
=========================================== */
void UIComponentText::SetFontType(FontType type)
{
	m_eFontType = type;
}

/* ========================================
	�Z�b�^�[(�t�H���g�J���[)�֐�
	-------------------------------------
	�����FD2D1::ColorF �J���[
=========================================== */
void UIComponentText::SetFontColor(D2D1::ColorF color)
{
	m_Color = color;
}

/* ========================================
	�Z�b�^�[(�t�H���g�E�F�C�g)�֐�
	-------------------------------------
	�����FDWRITE_FONT_WEIGHT �E�F�C�g
=========================================== */
void UIComponentText::SetFontWeight(DWRITE_FONT_WEIGHT weight)
{
	m_Weight = weight;
}

/* ========================================
	�Z�b�^�[(�s�{�b�g)�֐�
	-------------------------------------
	�����FE_Pivot �s�{�b�g
=========================================== */
void UIComponentText::SetPivot(E_Pivot pivot)
{
	m_ePivot = pivot;
}

/* ========================================
	�Z�b�^�[(��ʊO�`�F�b�N)�֐�
	-------------------------------------
	�����Fbool �`�F�b�N
=========================================== */
void UIComponentText::SetScreenOutCheck(bool check)
{
	m_bScreenOutCheck = check;
}


#ifdef _DEBUG
/* ========================================
	�f�o�b�O�֐�
	-------------------------------------
	���e�F�f�o�b�O�p�̏���
	-------------------------------------
	����1�F�E�B���h�E	DebugUI::Window&
=========================================== */
void UIComponentText::Debug(DebugUI::Window& window)
{
	using namespace DebugUI;

	Item* pGroupUIText = Item::CreateGroup("UI_Text");

	// �e�L�X�g
	pGroupUIText->AddGroupItem(Item::CreateValue("Text", Item::Kind::Path));
	window.AddItem(pGroupUIText);
	pGroupUIText->AddGroupItem(Item::CreateValue("UseTextBox", Item::Bool, false, true));

	// �����T�C�Y
	pGroupUIText->AddGroupItem(Item::CreateBind("FontSize", Item::Kind::Int, &m_nFontSize));
	// �t�H���g�^�C�v
	pGroupUIText->AddGroupItem(Item::CreateList("FontType", [this](const void* arg)
	{
		std::string listText = reinterpret_cast<const char*>(arg);
		int nListNo = WIN_UI_INFO["UI_Text"]["FontType"].GetListNo(listText.c_str());

		m_eFontType = static_cast<FontType>(nListNo);
	}, false, true));

	// �t�H���g�J���[
	pGroupUIText->AddGroupItem(Item::CreateBind("FontColor",Item::Kind::Color, &m_Color));

	// ��ʓ������t���O
	pGroupUIText->AddGroupItem(Item::CreateBind("ScreenOutCheck", Item::Kind::Bool, &m_bScreenOutCheck));

	// �s�{�b�g
	pGroupUIText->AddGroupItem(Item::CreateList("Pivot", [this](const void* arg)
	{
		std::string listText = reinterpret_cast<const char*>(arg);
		int nListNo = WIN_UI_INFO["UI_Text"]["Pivot"].GetListNo(listText.c_str());

		m_ePivot = static_cast<E_Pivot>(nListNo);
	}, false, true));

	// �t�H���g�^�C�v���X�g
	WIN_UI_INFO["UI_Text"]["FontType"].AddListItem("IPAexMin");
	WIN_UI_INFO["UI_Text"]["FontType"].AddListItem("Letlogo");
	WIN_UI_INFO["UI_Text"]["FontType"].AddListItem("SmartFontUI");

	// �t�H���g�^�C�v���X�g�̏����l
	WIN_UI_INFO["UI_Text"]["FontType"].SetListNo(m_eFontType);

	// �e�L�X�g
	WIN_UI_INFO["UI_Text"]["Text"].SetPath(m_sText.c_str());
	WIN_UI_INFO["UI_Text"]["UseTextBox"].SetBool(false);

	// �t�H���g�J���[
	DirectX::XMFLOAT4 color = { m_Color.r, m_Color.g, m_Color.b, m_Color.a };
	WIN_UI_INFO["UI_Text"]["FontColor"].SetColor(color);

	// �s�{�b�g���X�g
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("LEFT_TOP");
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("LEFT_BOTTOM");
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("RIGHT_TOP");
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("RIGHT_BOTTOM");
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("CENTER");
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("LEFT_CENTER");
	WIN_UI_INFO["UI_Text"]["Pivot"].AddListItem("RIGHT_CENTER");

	WIN_UI_INFO["UI_Text"]["Pivot"].SetListNo(m_ePivot);

}




#endif // _DEBUG
