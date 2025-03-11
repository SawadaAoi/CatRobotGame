/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト(セレクトメニュー))用cpp
	------------------------------------
	UIObjectSelectMenu.cpp
========================================== */

// =============== インクルード ===================
#include "UIObjectSelectMenu.h"
#include "UIObjectText.h"
#include "UIComponentEffectScale.h"
#include "UIComponentTransform.h"
#include "UIComponentText.h"
#include "UIComponentSprite.h"
#include "SceneBase.h"
#include "Input.h"
#include "SoundManager.h"

// =============== 定数定義 =======================
const float			DEFAULT_TEXT_SPACE	= 65.0f;
const int			DEFAULT_TEXT_SIZE	= 60;
const FontType		DEFAULT_TEXT_FONT	= FontType::Letrogo;
const D2D1::ColorF	DEFAULT_TEXT_COLOR	= D2D1::ColorF::Black;

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
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
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void UIObjectSelectMenu::InitLocal()
{
	GetSprite()->SetIsVisible(false);
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
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

	// スペースキーで選択
	if (Input::IsKeyTrigger(VK_RETURN))
	{
		m_MenuFuncs[m_nSelectNum]();

		PLAY_SE(SE_KEY::SE_MENU_DECIDE);
	}

}

/* ========================================
	メニュー追加関数
	-------------------------------------
	内容：選択メニューを追加
	-------------------------------------
	引数1：メニュー名
	引数2：メニュー関数
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
	テキスト初期化関数
	-------------------------------------
	内容：テキスト初期化
		　※m_nSelectNumMaxは配列の最後の要素番号
=========================================== */
void UIObjectSelectMenu::InitText()
{
	// テキストUIオブジェクト生成
	UIObjectText* pText = 
		m_pOwnerScene->AddSceneUI<UIObjectText>("SelectMenu_" + std::to_string(m_nSelectNumMax));

	pText->SetIsSave(false);
	pText->AddComponent<UIComponentEffectScale>();

	AddChildUI(pText);

	m_pSelectMenu.push_back(pText);
}

/* ========================================
	全テキスト初期化関数
	-------------------------------------
	内容：全テキスト初期化
		　※間隔やフォントサイズなどを変更したときに使用
=========================================== */
void UIObjectSelectMenu::InitAllText()
{
	// 中心位置を文字同士の真ん中に合わせる(上にずらす)
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
	ゲッター(選択番号)関数
	-------------------------------------
	戻値：int 選択番号
=========================================== */
int UIObjectSelectMenu::GetSelectNum() const
{
	return m_nSelectNum;
}

/* ========================================
	セッター(選択番号)関数
	-------------------------------------
	引数1：int 選択番号
=========================================== */
void UIObjectSelectMenu::SetSelectNum(int nSelectNum)
{
	m_nSelectNum = nSelectNum;
}

/* ========================================
	セッター(メニュー関数)関数
	-------------------------------------
	引数1：int 選択番号
	引数2：std::string メニュー名
	引数3：MenuFunc メニュー関数
=========================================== */
void UIObjectSelectMenu::SetMenuFunc(int nSelectNum, std::string sName, MenuFunc func)
{
	m_MenuNames[nSelectNum] = sName;
	m_MenuFuncs[nSelectNum] = func;

	InitAllText();
}

/* ========================================
	セッター(テキスト間隔)関数
	-------------------------------------
	引数1：float テキスト間隔
=========================================== */
void UIObjectSelectMenu::SetTextSpace(float fSpace)
{
	m_vTextSpace = fSpace;
	InitAllText();
}

/* ========================================
	セッター(テキストサイズ)関数
	-------------------------------------
	引数1：int テキストサイズ
=========================================== */
void UIObjectSelectMenu::SetTextSize(int fSize)
{
	m_fTextSize = fSize;
	InitAllText();
}

/* ========================================
	セッター(テキストフォント)関数
	-------------------------------------
	引数1：FontType フォントタイプ
=========================================== */
void UIObjectSelectMenu::SetTextFont(FontType font)
{
	m_fTextFont = font;
	InitAllText();
}

/* ========================================
	セッター(テキストカラー)関数
	-------------------------------------
	引数1：D2D1::ColorF カラー	
=========================================== */
void UIObjectSelectMenu::SetTextColor(D2D1::ColorF color)
{
	m_TextColor = color;
	InitAllText();
}
