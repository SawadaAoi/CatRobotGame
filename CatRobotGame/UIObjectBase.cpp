/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト基底用cpp
	------------------------------------
	UIObjectBase.cpp
========================================== */
#pragma once

// =============== インクルード =====================
#include "UIObjectBase.h"
#include "SceneBase.h"			// シーン基底クラス
#include "UIComponentBase.h"	// UIコンポーネント基底クラス
#include <windows.h>
#include "UIComponentTransform.h"
#include "UIComponentSprite.h"	
#include "SceneManager.h"
#include "TextureManager.h"

#include "UITypeRegistry.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
=========================================== */
UIObjectBase::UIObjectBase(SceneBase* pScene)
	: m_pOwnerScene(pScene)
	, m_pComponents()
	, m_pCompTransform(nullptr)
	, m_pCompSprite(nullptr)
	, m_sName("NoName")
	, m_eState(E_State::STATE_ACTIVE)
	, m_pParentUI(nullptr)
	, m_pChildUIs()
	, m_bIsFold(false)					// オブジェクト一覧折りたたみフラグをfalseに設定
	, m_nDrawPriority(0)				// 描画優先度を0に設定
	, m_bIsSave(true)					// セーブフラグをtrueに設定
	, m_bIs3DObjBackDraw(false)			// 3Dオブジェクト後ろ描画フラグをfalseに設定
	, m_bIsDestroy(false)				// オブジェクト破棄フラグをfalseに設定
	, m_fDestroyTime(0.0f)				// 破棄時間を0に設定
	, m_fDestroyTimeCnt(0.0f)			// 破棄時間カウントを0に設定
{
	// 所有シーンがnullptrの場合はエラーを出力
	if (pScene == nullptr)
	{
		OutputDebugStringA("UIObjectBase::UIObjectBase() : 所有シーンがnullptrです。\n");
	}

}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
	-------------------------------------
	引数：オブジェクト名
=========================================== */
void UIObjectBase::Init(std::string sName)
{
	m_pComponents.clear();	// コンポーネントリストをクリア
	SetName(sName);			// オブジェクト名を設定
	InitDefaultComponent();	// デフォルトコンポーネントを追加

	InitLocal();			// 個別初期化処理
}


/* ========================================
	終了関数
	-------------------------------------
	内容：終了処理
=========================================== */
void UIObjectBase::Uninit()
{
	// 所持コンポーネント配列の全要素を削除
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Uninit();
		pComponent.reset();	// メモリ解放

	}
	m_pComponents.clear();	// クリア
	UninitLocal();	// 個別終了処理
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void UIObjectBase::Update()
{
	// 所持コンポーネント配列の全要素を更新
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update();
	}
	UpdateLocal();	// 個別更新処理

	// 子オブジェクトの更新
	for (auto& pChild : m_pChildUIs)
	{
		if (pChild->GetState() == UI_DEAD)	continue;	// 死亡状態でない場合は更新しない
		if (pChild->GetState() == UI_PAUSE) continue;	// 一時停止状態の場合は更新しない
		pChild->Update();
	}

	if (m_bIsDestroy)
	{
		// 破棄時間経過で破棄
		m_fDestroyTimeCnt += DELTA_TIME;
		if (m_fDestroyTimeCnt >= m_fDestroyTime)
		{
			SetState(UI_DEAD);	// 削除フラグが立っている場合は状態を死亡に変更
			DestroyChild();					// 子オブジェクトも状態を死亡に変更
		}
	}
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
=========================================== */
void UIObjectBase::Draw()
{
	// 所持コンポーネント配列の全要素を描画
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Draw();
	}
	DrawLocal();	// 個別描画処理

}

/* ========================================
	UI削除関数
	-------------------------------------
	内容：UIに削除フラグを立てる
		　※直接削除状態にしない理由は、衝突処理後に削除するため
	-------------------------------------
	引数1：削除時間(何秒後に削除するか)
		 　※デフォルトは0秒
=========================================== */
void UIObjectBase::Destroy(float nTime)
{
	m_bIsDestroy = true;
	m_fDestroyTime = nTime;	// 通常は即時削除
}

/* ========================================
	親オブジェクト設定関数
	-------------------------------------
	内容：親オブジェクトを設定する
	-------------------------------------
	引数1：親に設定するオブジェクト
=========================================== */
void UIObjectBase::SetParentUI(UIObjectBase* pParentObj)
{
	// 既に設定されている親オブジェクトから自身を削除
	if (m_pParentUI)
		m_pParentUI->RemoveChildUI(this);

	m_pParentUI = pParentObj;	// 自オブジェクトの更新

	// 自身のトランスフォームを再計算
	m_pCompTransform->RecalculateLocalTransform();

	// 既に親オブジェクトが更新済みかチェック
	// ※子オブジェクト追加関数から呼び出された場合
	for (auto& pChild : m_pParentUI->m_pChildUIs)
	{
		if (pChild == this)	return;
	}

	m_pParentUI->AddChildUI(this);	// 親オブジェクトの更新
}

/* ========================================
	子オブジェクト追加関数
	-------------------------------------
	内容：子オブジェクトを追加する
	-------------------------------------
	引数1：子オブジェクトにするオブジェクト
=========================================== */
void UIObjectBase::AddChildUI(UIObjectBase* pChildObj)
{
	// 既に子オブジェクトに登録されている場合は追加しない
	for (auto& pChild : m_pChildUIs)
	{
		if (pChild == pChildObj)	return;
}
	m_pChildUIs.push_back(pChildObj);	// 自オブジェクトの更新

	// 既に子オブジェクトが更新済みかチェック
	// ※親オブジェクト設定関数から呼び出された場合
	if (pChildObj->GetParentUI() == this) return;

	pChildObj->SetParentUI(this);	// 子オブジェクトの更新

}

/* ========================================
	親オブジェクト解除関数
	-------------------------------------
	内容：親オブジェクトを解除する
=========================================== */
void UIObjectBase::RemoveParentUI()
{
	// 親オブジェクトがない場合は処理しない
	if (m_pParentUI == nullptr) return;

	m_pParentUI->RemoveChildUI(this);	// 親オブジェクトから自身を削除
	m_pParentUI = nullptr;					// 親オブジェクトを空に設定

	// 自身のTransformコンポーネントの親解除処理
	this->GetComponent<UIComponentTransform>()->ClearParent();
}

/* ========================================
	子オブジェクト削除関数
	-------------------------------------
	内容：子オブジェクトを削除する
	-------------------------------------
	引数1：削除する子オブジェクト
=========================================== */
void UIObjectBase::RemoveChildUI(UIObjectBase* pChildObj)
{
	// 子オブジェクトを検索して配列から削除
	m_pChildUIs.erase(
		std::remove(m_pChildUIs.begin(), m_pChildUIs.end(), pChildObj), m_pChildUIs.end());


	pChildObj->m_pParentUI = nullptr;								// 親オブジェクトを空に設定
	pChildObj->GetComponent<UIComponentTransform>()->ClearParent();	// Transformコンポーネントの親解除処理
}

/* ========================================
	全子オブジェクト削除関数
	-------------------------------------
	内容：全子オブジェクトを削除する
=========================================== */
void UIObjectBase::RemoveAllChildUIs()
{
	// 子オブジェクトを全て配列から削除
	for (auto pChild : m_pChildUIs)
	{
		pChild->m_pParentUI = nullptr;									// 親オブジェクトを空に設定
		pChild->GetComponent<UIComponentTransform>()->ClearParent();	// Transformコンポーネントの親解除処理

	}
	m_pChildUIs.clear();
}

/* ========================================
	世代数取得関数
	-------------------------------------
	内容：自身の世代数を取得する
	-------------------------------------
	戻り値：世代数
=========================================== */
int UIObjectBase::GetGenerationCount()
{
	// 親オブジェクトがない場合
	if (m_pParentUI == nullptr)
	{
		return 0;
	}
	else
	{
		return m_pParentUI->GetGenerationCount() + 1;
	}
}

/* ========================================
	子孫判定関数
	-------------------------------------
	内容：指定したUIが子孫かどうかを判定する
	-------------------------------------
	引数1：判定するUI
	-------------------------------------
	戻り値：子孫かどうか
=========================================== */
bool UIObjectBase::CheckIsDescendant(UIObjectBase* pUI)
{
	// 子オブジェクトがない場合は処理しない
	if (m_pChildUIs.empty()) return false;

	// 子オブジェクトを検索
	for (auto pChild : m_pChildUIs)
	{
		// 子オブジェクトが対象のオブジェクトと一致した場合はtrueを返す
		if (pChild == pUI) return true;

		// 子オブジェクトの子孫を再帰的に検索
		if (pChild->GetChildUIs().size() > 0)
		{
			// 子オブジェクトの子孫を再帰的に検索
			if (pChild->CheckIsDescendant(pUI)) return true;
		}
	}

	return false;
}


/* ========================================
	コピー関数
	-------------------------------------
	内容：オブジェクトをコピーする
	-------------------------------------
	戻り値：コピーされたオブジェクト
=========================================== */
UIObjectBase* UIObjectBase::Copy()
{
	// Transformを取得
	UIComponentTransform* pTransform = this->GetComponent<UIComponentTransform>();

	UIObjectBase* pCopyUI = UI_TYPE_REGISTRY_INST.CreateUI(this->GetUIClassName());	// コピー用オブジェクト生成
	pCopyUI->Init(m_pOwnerScene->CreateUniqueUIName(this->GetName()));				// 初期化
	pCopyUI->SetDrawPriority(this->GetDrawPriority());								// 描画優先度を設定

	// Transformコンポーネントのコピー
	UIComponentTransform* pCopyTrans = pCopyUI->GetComponent<UIComponentTransform>();
	pCopyTrans->SetPosition(GetTransform()->GetPosition());
	pCopyTrans->SetRotation(GetTransform()->GetRotation());
	pCopyTrans->SetScale(GetTransform()->GetScale());

	// Spriteコンポーネントのコピー
	UIComponentSprite* pCopySprite = pCopyUI->GetComponent<UIComponentSprite>();
	pCopySprite->SetTexture(m_pCompSprite->GetTexture());
	pCopySprite->SetIsVisible(m_pCompSprite->GetIsVisible());

	m_pOwnerScene->AddSceneUI(pCopyUI);	// シーンにオブジェクトを追加

	// 親子関係を再現
	// 親オブジェクトがある場合
	if (this->GetParentUI())
	{
		pCopyUI->SetParentUI(this->GetParentUI());
	}

	// 子オブジェクトがある場合
	if (this->GetChildUIs().size() > 0)
	{
		for (auto& pChild : this->GetChildUIs())
		{
			UIObjectBase* pCopyChild = pChild->Copy();
			pCopyUI->AddChildUI(pCopyChild);
		}
	}

	return pCopyUI;
}


/* ========================================
	デフォルトコンポーネント追加関数
	-------------------------------------
	内容：オブジェクトにデフォルトで持たせる
		　コンポーネントを追加する
=========================================== */
void UIObjectBase::InitDefaultComponent()
{
	m_pCompTransform = AddComponent<UIComponentTransform>();	// Transformコンポーネントを追加	
	m_pCompSprite = AddComponent<UIComponentSprite>();		// Spriteコンポーネントを追加
}

/* ========================================
	子オブジェクト死亡状態遷移関数
	-------------------------------------
	内容：子オブジェクトを全て死亡状態に遷移
=========================================== */
void UIObjectBase::DestroyChild()
{
	// 子オブジェクト全ての削除フラグを立てる
	for (auto& pChild : m_pChildUIs)
	{
		pChild->SetState(UI_DEAD);
		pChild->DestroyChild();
	}
}

/* ========================================
	出力データ個別関数
	-------------------------------------
	内容：オブジェクト毎に出力するデータを設定
	-------------------------------------
	引数1：ファイル
=========================================== */
void UIObjectBase::OutPutLocalData(std::ofstream& file)
{
}

/* ========================================
	入力データ個別関数
	-------------------------------------
	内容：オブジェクト毎に入力するデータを設定
	-------------------------------------
	引数1：ファイル
=========================================== */
void UIObjectBase::InputLocalData(std::ifstream& file)
{
}

/* ========================================
	ゲッター(トランスフォーム)関数
	-------------------------------------
	戻値：ComponentTransform* トランスフォームコンポーネントのポインタ
=========================================== */
UIComponentTransform* UIObjectBase::GetTransform() const
{
	return m_pCompTransform;
}

/* ========================================
	ゲッター(スプライト)関数
	-------------------------------------
	戻値：ComponentSprite* スプライトコンポーネントのポインタ
=========================================== */
UIComponentSprite* UIObjectBase::GetSprite() const
{
	return m_pCompSprite;
}

/* ========================================
	ゲッター(所持シーン)関数
	-------------------------------------
	戻値：所有シーンのポインタ
=========================================== */
SceneBase* UIObjectBase::GetOwnerScene() const
{
	return m_pOwnerScene;
}

/* ========================================
	ゲッター(オブジェクト状態)関数
	-------------------------------------
	戻値：オブジェクト状態
=========================================== */
UIObjectBase::E_State UIObjectBase::GetState() const
{
	return m_eState;
}

/* ========================================
	ゲッター(オブジェクトID)関数
	-------------------------------------
	戻値：オブジェクトID
=========================================== */
size_t UIObjectBase::GetTypeID() const
{
	return GetStaticTypeID();
}

/* ========================================
	ゲッター(静的オブジェクトID)関数
	-------------------------------------
	戻値：静的オブジェクトID
=========================================== */
size_t UIObjectBase::GetStaticTypeID()
{
	static size_t nID = reinterpret_cast<size_t>(&GetStaticTypeID); 
	return nID;													
}

/* ========================================
	ゲッター(オブジェクトクラス名)関数
	-------------------------------------
	戻値：オブジェクトクラス名
=========================================== */
std::string UIObjectBase::GetUIClassName() const
{
	return "UIObjectBase";
}

/* ========================================
	ゲッター(オブジェクト名)関数
	-------------------------------------
	戻値：オブジェクト名
=========================================== */
std::string UIObjectBase::GetName() const
{
	return m_sName;
}

/* ========================================
	ゲッター(セーブフラグ)関数
	-------------------------------------
	戻値：セーブフラグ
=========================================== */
bool UIObjectBase::GetIsSave() const
{
	return m_bIsSave;
}

/* ========================================
	ゲッター(オブジェクト一覧折りたたみフラグ)関数
	-------------------------------------
	戻値：オブジェクト一覧折りたたみフラグ
=========================================== */
bool UIObjectBase::GetIsFold() const
{
	return m_bIsFold;
}

/* ========================================
	ゲッター(描画優先度)関数
	-------------------------------------
	戻値：描画優先度
=========================================== */
int UIObjectBase::GetDrawPriority() const
{
	return m_nDrawPriority;
}

/* ========================================
	ゲッター(3Dオブジェクト後ろ描画フラグ)関数
	-------------------------------------
	戻値：3Dオブジェクト後ろ描画フラグ
=========================================== */
bool UIObjectBase::GetIs3DObjBackDraw() const
{
	return m_bIs3DObjBackDraw;
}

/* ========================================
	ゲッター(親オブジェクト)関数
	-------------------------------------
	戻値：親オブジェクト
=========================================== */
UIObjectBase* UIObjectBase::GetParentUI() const
{
	return m_pParentUI;
}

/* ========================================
	ゲッター(子オブジェクト)関数
	-------------------------------------
	戻値：子オブジェクト
=========================================== */
std::vector<UIObjectBase*> UIObjectBase::GetChildUIs() const
{
	return m_pChildUIs;
}

/* ========================================
	セッター(オブジェクト状態)関数
	-------------------------------------
	引数1：オブジェクト状態
=========================================== */
void UIObjectBase::SetState(E_State eState)
{
	m_eState = eState;
}

/* ========================================
	セッター(オブジェクト名)関数
	-------------------------------------
	引数1：オブジェクト名
=========================================== */
void UIObjectBase::SetName(std::string sName)
{
	m_sName = sName;
}

/* ========================================
	セッター(セーブフラグ)関数
	-------------------------------------
	引数1：セーブフラグ
=========================================== */
void UIObjectBase::SetIsSave(bool bIsSave)
{
	m_bIsSave = bIsSave;
}

/* ========================================
	セッター(UI一覧折りたたみフラグ)関数
	-------------------------------------
	引数1：UI一覧折りたたみフラグ
=========================================== */
void UIObjectBase::SetIsFold(bool bIsFold)
{
	m_bIsFold = bIsFold;
}

/* ========================================
	セッター(描画優先度)関数
	-------------------------------------
	引数1：描画優先度
=========================================== */
void UIObjectBase::SetDrawPriority(int nPriority)
{
	m_nDrawPriority = nPriority;
}

/* ========================================
	セッター(3Dオブジェクト後ろ描画フラグ)関数
	-------------------------------------
	引数1：3Dオブジェクト後ろ描画フラグ
=========================================== */
void UIObjectBase::SetIs3DObjBackDraw(bool bIsBackDraw)
{
	m_bIs3DObjBackDraw = bIsBackDraw;
}

#ifdef _DEBUG
/* ========================================
	デバッグ用関数
	-------------------------------------
	内容：デバッグ用の処理
		　例：UI情報(所持コンポーネント等)の表示
=========================================== */
void UIObjectBase::Debug()
{
	using namespace DebugUI;

	Window& pUIInfo = WIN_UI_INFO;

	// オブジェクト詳細情報を更新
	pUIInfo.AddItem(Item::CreateValue("UIName", Item::Text, false));	// 名前
	pUIInfo["UIName"].SetText(this->GetName().c_str());				// オブジェクト名を設定

	Item* pGroupUIBase = Item::CreateGroup("UIBase");	// UI基本情報グループ

	// オブジェクト名変更
	pGroupUIBase->AddGroupItem(Item::CreateCallBack("ChangeName", Item::Kind::Command, [this](bool isWrite, void* arg)	// 名前変更ボタン
	{
		ChangeName();
	}));
	pGroupUIBase->AddGroupItem(Item::CreateValue("UIReName", Item::Path, false, true));	// 変更後の名前

	pGroupUIBase->AddGroupItem(InitParentList());	// 親オブジェクトリスト

	pGroupUIBase->AddGroupItem(Item::CreateBind("DrawPriority", Item::Int, &m_nDrawPriority, false));	// 描画優先度

	pUIInfo.AddItem(pGroupUIBase);	// グループを追加

	pUIInfo["UIBase"]["UIReName"].SetPath(this->GetName().c_str());	// 変更後の名前を設定


	// 各コンポーネント情報をオブジェクト情報ウィンドウに表示
	auto it = m_pComponents.begin();
	while (it != m_pComponents.end())
	{
		(*it)->Debug(pUIInfo);
		++it;
	}
}

/* ========================================
	親オブジェクトリスト初期化関数
	-------------------------------------
	内容：親オブジェクトリストの初期化
	-------------------------------------
	戻り値：親オブジェクトリスト
=========================================== */
DebugUI::Item* UIObjectBase::InitParentList()
{
	using namespace DebugUI;

	// 親オブジェクトリスト作成
	Item* pParentList = Item::CreateList("ParentUI", [this](const void* arg)
	{
		std::string sParentName = reinterpret_cast<const char*>(arg);
		ChangeParentList(sParentName);	// 親オブジェクト変更

	}, false, true);

	// シーン上のオブジェクトをリストに追加
	int nParentNo = 0;					// 選択中のオブジェクト番号
	pParentList->AddListItem("None");	// リストの先頭は親オブジェクトなし

	// シーン上のオブジェクトをリストに追加
	for (const auto pObj : SceneManager::GetScene()->GetAllSceneUIObjects())
	{
		if (pObj == this) continue;				// 自身は追加しない
		if (CheckIsDescendant(pObj)) continue;	// 子オブジェクトは除外(自身の子階層に存在する場合は除外

		pParentList->AddListItem(pObj->GetName().c_str());	// シーン上のオブジェクト名を追加
	}
	// 親オブジェクトがある場合
	if (m_pParentUI)
	{
		nParentNo = pParentList->GetListNo(m_pParentUI->GetName().c_str());	// 親オブジェクトを選択
	}

	pParentList->SetListNo(nParentNo);	// 選択中のオブジェクトを設定

	return pParentList;
}

/* ========================================
	名前変更関数
	-------------------------------------
	内容：UI名を変更する
=========================================== */
void UIObjectBase::ChangeName()
{
	std::string sReName = WIN_UI_INFO["UIBase"]["UIReName"].GetPath();	// 変更後の名前
	std::string sOldName = this->GetName();								// 変更前の名前

	if (sReName.empty())		return;	// 変更後の名前が空の場合は処理しない
	if (sReName == sOldName)	return;	// 同じ名前の場合は処理しない

	sReName = SceneManager::GetScene()->CreateUniqueUIName(sReName);	// 重複しない名前に変更

	// オブジェクト名変更
	this->SetName(sReName);												// 内部の名前変更

	WIN_UI_INFO["UIName"].SetText(this->GetName().c_str());		// オブジェクト詳細の名前を変更
}


/* ========================================
	親オブジェクトリスト変更関数
	-------------------------------------
	内容：親オブジェクトを変更する
	-------------------------------------
	引数：新しい親オブジェクト名
=========================================== */
void UIObjectBase::ChangeParentList(std::string sParentName)
{
	UIObjectBase* pParentNew = SceneManager::GetScene()->FindSceneUI(sParentName);	// 親オブジェクト取得

	// 既に設定されている親オブジェクトと同じ場合は処理しない
	if (pParentNew == m_pParentUI) return;

	if (pParentNew)
	{
		this->SetParentUI(pParentNew);	// 新しい親オブジェクトに設定
		// オブジェクト一覧の選択位置を変更
		int nListNo = ITEM_UI_LIST.GetListNo(pParentNew->GetListName().c_str());	// オブジェクト一覧の表示位置取得
		ITEM_UI_LIST.SetListNo(nListNo + 1);
	}
	else
	{
		this->RemoveParentUI();			// 親オブジェクトがない場合(Noneを選択)は解除
		ITEM_UI_LIST.SetListNo(-1);		// オブジェクト一覧の選択位置を変更
	}

	m_bIsFold = false;	// UI一覧を展開
}


/* ========================================
	リスト表示名取得関数
	-------------------------------------
	内容：リスト表示用の名前を取得する
	-------------------------------------
	戻り値：リスト表示用の名前
=========================================== */
std::string UIObjectBase::GetListName()
{
	std::string sName;							// リスト表示名
	int nGeneCnt = this->GetGenerationCount();	// 世代数取得

	// 親オブジェクトがある場合
	if (nGeneCnt > 0)
	{
		// 世代数分のスペースを追加(表示を段階的にするため)
		for (int i = 0; i < nGeneCnt; i++)
		{
			sName += DebugUI::CHILD_HEAD_SPACE;
		}
		sName += DebugUI::CHILD_HEAD_TEXT + this->GetName();
	}
	// 無い場合はそのまま表示
	else
	{
		sName = this->GetName();
	}

	// 子オブジェクトがある場合は末尾に文字を追加
	if (m_pChildUIs.size() > 0)
	{
		sName += DebugUI::PARENT_END_TEXT;
	}

	return sName;
}


#endif // _DEBUG