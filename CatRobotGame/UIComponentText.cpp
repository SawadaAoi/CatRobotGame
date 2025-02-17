/* ========================================
	DX22Base/
	------------------------------------
	テキストコンポーネント用cpp
	------------------------------------
	UIComponentText.cpp
========================================== */

// =============== インクルード ===================
#include "UIComponentText.h"
#include "UIComponentTransform.h"
#include "UIObjectBase.h"
#include <string>
#include <codecvt>
#include <locale>
#include <windows.h>
#include "ObjectBase.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所持オブジェクト
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
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void UIComponentText::Init()
{
	m_pCompTransform = m_pOwnerObj->GetComponent<UIComponentTransform>();
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
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
	ゲッター(文字列)関数
	-------------------------------------
	戻り値：std::string 文字列
=========================================== */
std::string UIComponentText::GetText() const
{
	return m_sText;
}

/* ========================================
	ゲッター(フォントサイズ)関数
	-------------------------------------
	戻り値：int サイズ
=========================================== */
int UIComponentText::GetFontSize() const
{
	return m_nFontSize;
}

/* ========================================
	ゲッター(フォントタイプ)関数
	-------------------------------------
	戻り値：FontType フォントタイプ
=========================================== */
FontType UIComponentText::GetFontType() const
{
	return m_eFontType;
}

/* ========================================
	ゲッター(フォントカラー)関数
	-------------------------------------
	戻り値：D2D1::ColorF カラー
=========================================== */
D2D1::ColorF UIComponentText::GetFontColor() const
{
	return m_Color;
}

/* ========================================
	ゲッター(フォントウェイト)関数
	-------------------------------------
	戻り値：DWRITE_FONT_WEIGHT ウェイト
=========================================== */
DWRITE_FONT_WEIGHT UIComponentText::GetFontWeight() const
{
	return m_Weight;
}

/* ========================================
	ゲッター(ピボット)関数
	-------------------------------------
	戻り値：E_Pivot ピボット
=========================================== */
E_Pivot UIComponentText::GetPivot() const
{
	return m_ePivot;
}

/* ========================================
	ゲッター(画面外チェック)関数
	-------------------------------------
	戻り値：bool チェック
=========================================== */
bool UIComponentText::GetScreenOutCheck() const
{
	return m_bScreenOutCheck;
}

/* ========================================
	セッター(文字列)関数
	-------------------------------------
	引数：std::string 文字列
=========================================== */
void UIComponentText::SetText(const std::string& text)
{
	m_sText = text;

}

/* ========================================
	セッター(フォントサイズ)関数
	-------------------------------------
	引数：int サイズ
=========================================== */
void UIComponentText::SetFontSize(int size)
{
	m_nFontSize = size;
}

/* ========================================
	セッター(フォントタイプ)関数
	-------------------------------------
	引数：FontType フォントタイプ
=========================================== */
void UIComponentText::SetFontType(FontType type)
{
	m_eFontType = type;
}

/* ========================================
	セッター(フォントカラー)関数
	-------------------------------------
	引数：D2D1::ColorF カラー
=========================================== */
void UIComponentText::SetFontColor(D2D1::ColorF color)
{
	m_Color = color;
}

/* ========================================
	セッター(フォントウェイト)関数
	-------------------------------------
	引数：DWRITE_FONT_WEIGHT ウェイト
=========================================== */
void UIComponentText::SetFontWeight(DWRITE_FONT_WEIGHT weight)
{
	m_Weight = weight;
}

/* ========================================
	セッター(ピボット)関数
	-------------------------------------
	引数：E_Pivot ピボット
=========================================== */
void UIComponentText::SetPivot(E_Pivot pivot)
{
	m_ePivot = pivot;
}

/* ========================================
	セッター(画面外チェック)関数
	-------------------------------------
	引数：bool チェック
=========================================== */
void UIComponentText::SetScreenOutCheck(bool check)
{
	m_bScreenOutCheck = check;
}


#ifdef _DEBUG
/* ========================================
	デバッグ関数
	-------------------------------------
	内容：デバッグ用の処理
	-------------------------------------
	引数1：ウィンドウ	DebugUI::Window&
=========================================== */
void UIComponentText::Debug(DebugUI::Window& window)
{
	using namespace DebugUI;

	Item* pGroupUIText = Item::CreateGroup("UI_Text");

	// テキスト
	pGroupUIText->AddGroupItem(Item::CreateValue("Text", Item::Kind::Path));
	window.AddItem(pGroupUIText);
	pGroupUIText->AddGroupItem(Item::CreateValue("UseTextBox", Item::Bool, false, true));

	// 文字サイズ
	pGroupUIText->AddGroupItem(Item::CreateBind("FontSize", Item::Kind::Int, &m_nFontSize));
	// フォントタイプ
	pGroupUIText->AddGroupItem(Item::CreateList("FontType", [this](const void* arg)
	{
		std::string listText = reinterpret_cast<const char*>(arg);
		int nListNo = WIN_UI_INFO["UI_Text"]["FontType"].GetListNo(listText.c_str());

		m_eFontType = static_cast<FontType>(nListNo);
	}, false, true));

	// フォントカラー
	pGroupUIText->AddGroupItem(Item::CreateBind("FontColor",Item::Kind::Color, &m_Color));

	// 画面内調整フラグ
	pGroupUIText->AddGroupItem(Item::CreateBind("ScreenOutCheck", Item::Kind::Bool, &m_bScreenOutCheck));

	// ピボット
	pGroupUIText->AddGroupItem(Item::CreateList("Pivot", [this](const void* arg)
	{
		std::string listText = reinterpret_cast<const char*>(arg);
		int nListNo = WIN_UI_INFO["UI_Text"]["Pivot"].GetListNo(listText.c_str());

		m_ePivot = static_cast<E_Pivot>(nListNo);
	}, false, true));

	// フォントタイプリスト
	WIN_UI_INFO["UI_Text"]["FontType"].AddListItem("IPAexMin");
	WIN_UI_INFO["UI_Text"]["FontType"].AddListItem("Letlogo");
	WIN_UI_INFO["UI_Text"]["FontType"].AddListItem("SmartFontUI");

	// フォントタイプリストの初期値
	WIN_UI_INFO["UI_Text"]["FontType"].SetListNo(m_eFontType);

	// テキスト
	WIN_UI_INFO["UI_Text"]["Text"].SetPath(m_sText.c_str());
	WIN_UI_INFO["UI_Text"]["UseTextBox"].SetBool(false);

	// フォントカラー
	DirectX::XMFLOAT4 color = { m_Color.r, m_Color.g, m_Color.b, m_Color.a };
	WIN_UI_INFO["UI_Text"]["FontColor"].SetColor(color);

	// ピボットリスト
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
