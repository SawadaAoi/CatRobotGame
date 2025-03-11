/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト(セレクトメニュー)用ヘッダ
	------------------------------------
	説明：縦に並べられたメニューを表示するUIオブジェクト
		　※タイトル画面などで使用
	------------------------------------
	UIObjectSelectMenu.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIObjectBase.h"
#include <functional>
#include "DirectWriteCustomFont.h"

// =============== 前方宣言 ===================
class UIObjectText;

// =============== クラス定義 ===================
class UIObjectSelectMenu :
    public UIObjectBase
{
public:
	// メニュー関数型
    using MenuFunc = std::function<void()>;
public:
	UIObjectSelectMenu(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	void AddMenu(std::string sName, MenuFunc func);

	// ゲッター
	int GetSelectNum() const;

	// セッター
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
	std::vector<MenuFunc>		m_MenuFuncs;	// メニュー関数(選択したときに実行する)
	std::vector<std::string>	m_MenuNames;	// メニュー名
	std::vector<UIObjectText*>	m_pSelectMenu;	// メニューテキスト

	int m_nSelectNum;		// 選択番号
	int m_nSelectNumOld;	// 選択番号(前回)

	int m_nSelectNumMax;	// 選択最大数

	float			m_vTextSpace;	// テキスト間隔
	int				m_fTextSize;	// テキストサイズ
	FontType		m_fTextFont;	// テキストフォント
	D2D1::ColorF	m_TextColor;	// テキストカラー

};

