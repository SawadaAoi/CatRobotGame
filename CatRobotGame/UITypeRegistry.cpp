/* ========================================
	DX22Base/
	------------------------------------
	UI種類登録用cpp
	------------------------------------
	UITypeRegistry.cpp
========================================== */

// =============== インクルード ===================
#include "UITypeRegistry.h"


/* ========================================
	インスタンス取得関数
	-------------------------------------
	内容：インスタンスを取得する
	-------------------------------------
	戻値：インスタンス
=========================================== */
UITypeRegistry& UITypeRegistry::GetInstance()
{
	static UITypeRegistry instance;
	return instance;
}

/* ========================================
	UIクラス登録関数
	-------------------------------------
	内容：UIクラスをマップに登録する
	-------------------------------------
	引数1：UIクラス名
	引数2：UI生成関数
=========================================== */
void UITypeRegistry::Register(const std::string& sClassName, CreateFunction* func)
{
	m_UITypeMap[sClassName] = func;
}

/* ========================================
	UI生成関数
	-------------------------------------
	内容：クラス名文字列からUIを生成する
	-------------------------------------
	引数：UIクラス名
	-------------------------------------
	戻値：UIポインタ
=========================================== */
UIObjectBase* UITypeRegistry::CreateUI(const std::string& sClassName)
{
	// クラス名が登録されているか確認
	if (m_UITypeMap.find(sClassName) != m_UITypeMap.end())
	{
		return m_UITypeMap.at(sClassName)();
	}
	return nullptr;
}


/* ========================================
	ゲッター(UIマップ)関数
	-------------------------------------
	戻値：unordered_map<std::string, CreateFunction*>& UIマップ
=========================================== */
std::unordered_map<std::string, UITypeRegistry::CreateFunction*>& UITypeRegistry::GetUITypeMap()
{
	return m_UITypeMap;
}
