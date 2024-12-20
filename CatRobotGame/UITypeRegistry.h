/* ========================================
    DX22Base/
    ------------------------------------
    UI種類登録用ヘッダ
    ------------------------------------
    説明：文字列からUIを生成するための登録クラス
    ------------------------------------
    UITypeRegistry.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIObjectBase.h"
#include "SceneManager.h"


// =============== 定数定義 =======================
#define UI_TYPE_REGISTRY_INST UITypeRegistry::GetInstance()    // インスタンス取得用マクロ
#define REGISTER_UI_TYPE(className)                                             \
    UITypeRegistry::GetInstance().Register(#className,                          \
        []() -> UIObjectBase* { return new className(SceneManager::GetScene()); })    \

// =============== クラス定義 ===================
class UITypeRegistry
{
public:
    using CreateFunction = UIObjectBase* ();                            // 関数ポインタの型を定義
public:
    static UITypeRegistry& GetInstance();
    void Register(const std::string& sClassName, CreateFunction* func); // マップ(文字列・クラス生成関数)に登録
    UIObjectBase* CreateUI(const std::string& sClassName);              // UI生成

    static void RegisterAllUITypes();                                   // UIの登録を行う関数

    // ゲッター
    std::unordered_map<std::string, CreateFunction*>& GetUITypeMap();
private:
    // 文字列とクラス生成関数のマップ
    std::unordered_map<std::string, CreateFunction*> m_UITypeMap;

};

