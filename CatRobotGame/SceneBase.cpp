/* ========================================
	DX22Base/
	------------------------------------
	シーン用cpp
	------------------------------------
	SceneBase.cpp
========================================== */

// =============== インクルード =====================
#include "SceneBase.h"
#include "ObjectBase.h"
#include "ObjectCamera.h"
#include "CameraManager.h"
#include "ComponentCollisionBase.h"

// =============== 定数定義 =======================
const int OBJECT_LIST_LINE_NUM = 17;	// オブジェクトリストの行数

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
========================================== */
SceneBase::SceneBase()
	: m_bIsUpdating(false)		// 更新中フラグを初期化
	, m_bIsUpdatingUI(false)	// UI更新中フラグを初期化
	, m_pObjects()				// シーンに所属するオブジェクト一覧
	, m_pStandbyObjects()		// オブジェクトを一時的に保存しておく配列
	, m_pUIObjects()			// シーンに所属するUIオブジェクト一覧
	, m_pStandbyUIObjects()		// UIオブジェクトを一時的に保存しておく配列
	, m_pObjectCollision()		// 各オブジェクトが持つ衝突判定コンポーネント
#ifdef _DEBUG
	, m_pSelectObj(nullptr)		// 一覧で選択中のオブジェクト
	, m_nObjectListSelectNo(-1)	// オブジェクトリストの番号
	, m_pSelectUI(nullptr)		// 一覧で選択中のUIオブジェクト
	, m_nUISelectNo(-1)			// UIオブジェクトリストの番号
#endif // _DEBUG

{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void SceneBase::Init()
{
#ifdef _DEBUG
	InitObjectList();
	InitUIList();
#endif // _DEBUG

	// クリア
	m_pObjects.clear();			// シーンに所属するオブジェクト一覧
	m_pStandbyObjects.clear();	// オブジェクトを一時的に保存しておく配列
	m_pUIObjects.clear();		// シーンに所属するUIオブジェクト一覧
	m_pStandbyUIObjects.clear();	// UIオブジェクトを一時的に保存しておく配列

	m_bIsUpdating = false;		// 更新中フラグを初期化
	InitLocal();				// 個別初期化処理

	CAMERA_MNG_INST.Init(this);	// シーンのカメラを初期化
}

/* ========================================
	終了関数
	-------------------------------------
	内容：終了処理
=========================================== */
void SceneBase::Uninit()
{
#ifdef _DEBUG
	WIN_OBJ_LIST.Clear();
	WIN_OBJ_INFO.Clear();
	WIN_UI_LIST.Clear();
	WIN_UI_INFO.Clear();
	WIN_CAMERA_INFO["CameraList"].RemoveListItemAll();

#endif // _DEBUG

	UninitLocal();	// 個別終了処理

	// 所持UIオブジェクト配列の全要素を削除
	for (auto& pObject : m_pUIObjects)
	{
		pObject->Uninit();
	}
	m_pUIObjects.clear();	// クリア

	// 所持オブジェクト配列の全要素を削除
	for (auto& pObject : m_pObjects)
	{
		pObject->Uninit();
	}
	m_pObjects.clear();	// クリア

	// 一時保存していたオブジェクト配列の全要素を削除
	for (auto& pObject : m_pStandbyObjects)
	{
		pObject->Uninit();
	}
	m_pStandbyObjects.clear();	// クリア
	
	// 一時保存していたUIオブジェクト配列の全要素を削除
	for (auto& pObject : m_pStandbyUIObjects)
	{
		pObject->Uninit();
	}
	m_pStandbyUIObjects.clear();	// クリア

}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void SceneBase::Update()
{
#ifdef _DEBUG
	// リスト未選択時は選択オブジェクトをクリア
	if (m_nObjectListSelectNo == -1) m_pSelectObj = nullptr;
	// UIリスト未選択時は選択UIオブジェクトをクリア
	if (m_nUISelectNo == -1) m_pSelectUI = nullptr;

	ReloadDebugObjectList();	// オブジェクトリスト再読み込み
	ReloadDebugUIList();		// UIオブジェクトリスト再読み込み
#endif // _DEBUG

	SortUIObjects();	// UIオブジェクトを描画順に並び替え
	UpdateObject();		// オブジェクト更新
	UpdateUI();			// UI更新
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
=========================================== */
void SceneBase::Draw()
{
	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_UI);			// ブレンドモード変更(透明度0.0～1.0)
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_DISABLE);	// 深度テスト無効
	// 3Dオブジェクトの背景に描画するUIを描画
	for (auto& pUIObject : m_pUIObjects)
	{
		if (!pUIObject->GetIs3DObjBackDraw()) continue;
		pUIObject->Draw();
	}
	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_ALPHA);				// ブレンドモード元に戻す
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_ENABLE_WRITE_TEST);	// 深度テスト元に戻す


	// 所持オブジェクト配列の全要素を描画
	for (auto& pObject : m_pObjects)
	{
		pObject->Draw();	
	}

	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_UI);			// ブレンドモード変更(透明度0.0～1.0)
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_DISABLE);	// 深度テスト無効
	// 所持UIオブジェクト配列の全要素を描画
	for (auto& pUIObject : m_pUIObjects)
	{
		if (pUIObject->GetIs3DObjBackDraw()) continue;
		pUIObject->Draw();
	}
	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_ALPHA);				// ブレンドモード元に戻す
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_ENABLE_WRITE_TEST);	// 深度テスト元に戻す
	DrawLocal();	// 個別描画処理
}

/* ========================================
	オブジェクト更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void SceneBase::UpdateObject()
{
	m_bIsUpdating = true;	// 更新中フラグを立てる

	// 所持オブジェクト配列の全要素を更新
	for (auto& pObject : m_pObjects)
	{
		pObject->Update();
	}

	m_bIsUpdating = false;	// 更新中フラグを解除

	// 一時保存オブジェクト配列
	for (auto& pObject : m_pStandbyObjects)
	{
		pObject->Update();
		m_pObjects.emplace_back(std::move(pObject));	// オブジェクト配列に移動
	}
	m_pStandbyObjects.clear();	// クリア

	
	UpdateCollision();	// 各当たり判定更新(死亡したオブジェクトをm_bColStatesMapから削除するためにこの位置に記述)
	RemoveDeadObjects();// 死亡状態のオブジェクトを削除
}

/* ========================================
	UI更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void SceneBase::UpdateUI()
{
	m_bIsUpdatingUI = true;	// 更新中フラグを立てる

	// 所持UIオブジェクト配列の全要素を更新
	for (auto& pObject : m_pUIObjects)
	{
		pObject->Update();
	}

	m_bIsUpdatingUI = false;	// 更新中フラグを解除

	// 一時保存UIオブジェクト配列
	for (auto& pObject : m_pStandbyUIObjects)
	{
		pObject->Update();
		m_pUIObjects.emplace_back(std::move(pObject));	// UIオブジェクト配列に移動
	}
	m_pStandbyUIObjects.clear();	// クリア

	RemoveDeadUIObjects();	// 死亡状態のUIオブジェクトを削除
	UpdateLocal();			// 個別更新処理
}

/* ========================================
	UI並び替え関数
	-------------------------------------
	内容：優先順位に従ってUIオブジェクトを並び替え
=========================================== */
void SceneBase::SortUIObjects()
{
	// UIオブジェクトを描画順に並び替え
	std::sort(m_pUIObjects.begin(), m_pUIObjects.end(),
		[](const std::unique_ptr<UIObjectBase>& pUI1, const std::unique_ptr<UIObjectBase>& pUI2)
	{
		return pUI1->GetDrawPriority() < pUI2->GetDrawPriority();
	});
}

/* ========================================
	オブジェクト削除関数
	-------------------------------------
	内容：死亡状態のオブジェクトを削除
=========================================== */
void SceneBase::RemoveDeadObjects()
{
	// ↓のループ内でオブジェクトの状態が変わるので、一時保存用にコピー
	std::map<ObjectBase*, ObjectBase::E_State> pObjectStateMap;	
	for (auto& pObject : m_pObjects)
		pObjectStateMap.insert(std::make_pair(pObject.get(), pObject->GetState()));

	// 死亡状態のオブジェクトを削除
	for (auto it = m_pObjects.begin(); it != m_pObjects.end();)
	{
		ObjectBase* pObject = it->get();
		// 死亡状態かどうか
		if (pObjectStateMap.at(pObject) == OBJ_DEAD)
		{
#ifdef _DEBUG
			// 削除対象オブジェクトが一覧で選択中の場合
			if(m_nObjectListSelectNo == ITEM_OBJ_LIST.GetListNo(pObject->GetListName().c_str()))
			{
				WIN_OBJ_INFO.Clear();	// オブジェクト情報ウィンドウクリア

				m_nObjectListSelectNo = -1;								// 選択番号をリセット
				ITEM_OBJ_LIST.SetListNo(-1);	// 選択番号をリセット
			}
#endif
			// 子オブジェクトがある場合
			if (pObject->GetChildObjects().size() > 0)
			{
				for (auto& pChild : pObject->GetChildObjects())
				{
					this->RemoveSceneObject(pChild);	// 子オブジェクトを削除
				}
			}
			// 親オブジェクトがある場合
			if (pObject->GetParentObject())
			{
				pObject->GetParentObject()->RemoveChildObject(pObject);	// 親オブジェクトから削除
			}

			pObject->Uninit();			// 終了処理
			it = m_pObjects.erase(it);	// 削除

		}
		else
		{
			++it;	// 次の要素へ
		}
	}

}

/* ========================================
	UIオブジェクト削除関数
	-------------------------------------
	内容：死亡状態のUIオブジェクトを削除
=========================================== */
void SceneBase::RemoveDeadUIObjects()
{
	// ↓のループ内でUIオブジェクトの状態が変わるので、一時保存用にコピー
	std::map<UIObjectBase*, UIObjectBase::E_State> pUIObjectStateMap;
	for (auto& pUIObject : m_pUIObjects)
		pUIObjectStateMap.insert(std::make_pair(pUIObject.get(), pUIObject->GetState()));

	// 死亡状態のUIオブジェクトを削除
	for (auto it = m_pUIObjects.begin(); it != m_pUIObjects.end();)
	{
		UIObjectBase* pUIObject = it->get();
		// 死亡状態かどうか
		if (pUIObjectStateMap.at(pUIObject) == UIObjectBase::E_State::STATE_DEAD)
		{
#ifdef _DEBUG
			// 削除対象UIオブジェクトが一覧で選択中の場合
			if (m_nUISelectNo == WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].GetListNo(pUIObject->GetListName().c_str()))
			{
				WIN_UI_INFO.Clear();	// UIオブジェクト情報ウィンドウクリア

				m_nUISelectNo = -1;								// 選択番号をリセット
				WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].SetListNo(-1);	// 選択番号をリセット
			}
#endif
			// 子UIオブジェクトがある場合
			if (pUIObject->GetChildUIs().size() > 0)
			{
				for (auto& pChild : pUIObject->GetChildUIs())
				{
					this->RemoveSceneUI(pChild);	// 子UIオブジェクトを削除
				}
			}
			// 親UIオブジェクトがある場合
			if (pUIObject->GetParentUI())
			{
				pUIObject->GetParentUI()->RemoveChildUI(pUIObject);	// 親UIオブジェクトから削除
			}

			pUIObject->Uninit();			// 終了処理
			it = m_pUIObjects.erase(it);	// 削除
		}
		else
		{
			++it;	// 次の要素へ
		}
	}

}

/* ========================================
	オブジェクト追加関数
	-------------------------------------
	内容：シーンにオブジェクトを追加
		　※ファイルデータからオブジェクトを追加する場合に使用
	-------------------------------------
	引数：追加するオブジェクトポインタ
=========================================== */
void SceneBase::AddSceneObjectBase(ObjectBase* pObject)
{
	// シーンが更新中かどうかをチェックします
	if (m_bIsUpdating)
	{
		// 一時保存用の配列にユニークポインタを移動します
		m_pStandbyObjects.push_back(std::unique_ptr<ObjectBase>(pObject));
	}
	else
	{
		// シーンのオブジェクト配列にユニークポインタを移動します
		m_pObjects.push_back(std::unique_ptr<ObjectBase>(pObject));
	}
}

/* ========================================
	オブジェクト追加関数
	-------------------------------------
	内容：シーンにオブジェクトを追加
		　※ファイルデータからオブジェクトを追加する場合に使用
	-------------------------------------
	戻値：追加したオブジェクトポインタ
=========================================== */
void SceneBase::AddSceneUI(UIObjectBase* pUIObject)
{
	// シーンが更新中かどうかをチェックします
	if (m_bIsUpdatingUI)
	{
		// 一時保存用の配列にユニークポインタを移動します
		m_pStandbyUIObjects.push_back(std::unique_ptr<UIObjectBase>(pUIObject));
	}
	else
	{
		// シーンのUIオブジェクト配列にユニークポインタを移動します
		m_pUIObjects.push_back(std::unique_ptr<UIObjectBase>(pUIObject));
	}
}

/* ========================================
	オブジェクト検索関数
	-------------------------------------
	内容：シーンに所属するオブジェクトを検索
	-------------------------------------
	引数：sName	オブジェクト名
	-------------------------------------
	戻値：取得オブジェクトポインタ
=========================================== */
ObjectBase* SceneBase::FindSceneObject(std::string sName)
{
	// 名前が一致するオブジェクトを検索
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetName() == sName)
		{
			return pObject.get();
		}
	}

	return nullptr;
}

/* ========================================
	UIオブジェクト検索関数
	-------------------------------------
	内容：シーンに所属するUIオブジェクトを検索
	-------------------------------------
	引数：sName	UIオブジェクト名
	-------------------------------------
	戻値：取得UIオブジェクトポインタ
=========================================== */
UIObjectBase* SceneBase::FindSceneUI(std::string sName)
{
	// 名前が一致するUIオブジェクトを検索
	for (auto& pUIObject : m_pUIObjects)
	{
		if (pUIObject->GetName() == sName)
		{
			return pUIObject.get();
		}
	}

	return nullptr;
}

/* ========================================
	オブジェクト削除関数
	-------------------------------------
	内容：シーンに所属するオブジェクトを削除
		　※死亡状態のオブジェクトを削除する場合に使用(子オブジェクトの削除時)
	-------------------------------------
	引数：pObject	削除するオブジェクトポインタ
=========================================== */
void SceneBase::RemoveSceneObject(ObjectBase* pObject)
{
	// 子オブジェクトがある場合
	if (pObject->GetChildObjects().size() > 0)
	{
		for (auto& pChild : pObject->GetChildObjects())
		{
			this->RemoveSceneObject(pChild);	// 子オブジェクトを削除
		}
	}

	pObject->RemoveParentObject();	// 親オブジェクトから削除
	pObject->Destroy();				// 破棄

}

/* ========================================
	UIオブジェクト削除関数
	-------------------------------------
	内容：シーンに所属するUIオブジェクトを削除
		　※死亡状態のUIオブジェクトを削除する場合に使用(子UIオブジェクトの削除時)
	-------------------------------------
	引数：pUIObject	削除するUIオブジェクトポインタ
=========================================== */
void SceneBase::RemoveSceneUI(UIObjectBase* pUIObject)
{
	// 子オブジェクトがある場合
	if (pUIObject->GetChildUIs().size() > 0)
	{
		for (auto& pChild : pUIObject->GetChildUIs())
		{
			this->RemoveSceneUI(pChild);	// 子UIオブジェクトを削除
		}
	}
		
	pUIObject->RemoveParentUI();							// 親UIオブジェクトから削除
	pUIObject->SetState(UIObjectBase::E_State::STATE_DEAD);	// 死亡状態に設定

}


/* ========================================
	衝突判定配列追加関数
	-------------------------------------
	内容：衝突判定を管理する配列に追加
		　衝突判定コンポーネントの初期化で呼ばれる
	-------------------------------------
	引数1：衝突判定コンポーネント
=========================================== */
void SceneBase::AddObjectCollision(ComponentCollisionBase* pCollision)
{
	m_pObjectCollision.emplace_back(pCollision);	// emplace_backで追加(コピーを避ける)
}

/* ========================================
	衝突判定配列削除関数
	-------------------------------------
	内容：衝突判定を管理する配列から削除
		　衝突判定コンポーネントの終了処理で呼ばれる
	-------------------------------------
	引数1：衝突判定コンポーネント
=========================================== */
void SceneBase::RemoveObjectCollision(ComponentCollisionBase* pCollision)
{
	// 衝突判定を管理する配列から削除
	m_pObjectCollision.erase(
		std::remove(m_pObjectCollision.begin(), m_pObjectCollision.end(), pCollision), m_pObjectCollision.end());
}

/* ========================================
	当たり判定配列更新関数
	-------------------------------------
	内容：各オブジェクトが持つ当たり判定
		　コンポーネントを更新する
=========================================== */
void SceneBase::UpdateCollision()
{
	// 例：0と1、0と2、1と2、1と3、2と3、と全ての組み合わせで衝突判定を行う
	for (size_t i = 0; i < m_pObjectCollision.size(); ++i) {
		for (size_t j = i + 1; j < m_pObjectCollision.size(); ++j) {

			// 衝突判定を行うコンポーネントを取得
			ComponentCollisionBase* collisionA = m_pObjectCollision.at(i);
			ComponentCollisionBase* collisionB = m_pObjectCollision.at(j);

			collisionA->UpdateCollision(collisionB);
			collisionB->UpdateCollision(collisionA); 
		}
	}

	// 衝突状態マップ更新(上記の処理で衝突状態が変わったため)
	for (size_t i = 0; i < m_pObjectCollision.size(); ++i) {
		for (size_t j = i + 1; j < m_pObjectCollision.size(); ++j) {

			// 衝突判定を行うコンポーネントを取得
			ComponentCollisionBase* collisionA = m_pObjectCollision.at(i);
			ComponentCollisionBase* collisionB = m_pObjectCollision.at(j);

			collisionA->UpdateCollisionMap(collisionB);
			collisionB->UpdateCollisionMap(collisionA);
		}
	}

}


/* ========================================
	ユニーク名前生成関数
	-------------------------------------
	内容：名前が重複している場合に、
		　連番をつけた名前を生成する
	-------------------------------------
	引数：sName	オブジェクト名
	-------------------------------------
	戻値：調整後の名前
=========================================== */
std::string SceneBase::CreateUniqueName(std::string sName)
{
	std::string sReName = sName;				// 返す名前
	std::vector<ObjectBase*> pSelectObjects;	// 名前が含まれているオブジェクト配列

	// 名前が含まれているオブジェクトを検索
	// 例："Player"の場合、"CameraPlayer","PlayerStart","Player_1"など
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetName().find(sName) != std::string::npos)
		{
			pSelectObjects.push_back(pObject.get());
		}
	}
	// 一時保存オブジェクト配列
	for (auto& pObject : m_pStandbyObjects)
	{
		if (pObject->GetName().find(sName) != std::string::npos)
		{
			pSelectObjects.push_back(pObject.get());
		}
	}
	// 重複していない場合はそのまま返す
	if (pSelectObjects.size() == 0) return sName;	

	int nDupCnt = 0;	// 重複回数
	// 名前が重複している場合は連番を付ける(重複がなくなるまで)
	while (!CheckUniqueName(sReName, pSelectObjects))
	{
		nDupCnt++;
		sReName = sName + "_" + std::to_string(nDupCnt);
	}

	return sReName;

}

/* ========================================
	ユニーク名前UI生成関数
	-------------------------------------
	内容：名前が重複している場合に、
		　連番をつけた名前を生成する
	-------------------------------------
	引数：sName	UIオブジェクト名
	-------------------------------------
	戻値：調整後の名前
=========================================== */
std::string SceneBase::CreateUniqueUIName(std::string sName)
{
	std::string sReName = sName;			// 返す名前
	std::vector<UIObjectBase*> pSelectUIs;	// 名前が含まれているUIオブジェクト配列

	// 名前が含まれているUIオブジェクトを検索
	// 例："Player"の場合、"CameraPlayer","PlayerStart","Player_1"など
	for (auto& pUI : m_pUIObjects)
	{
		if (pUI->GetName().find(sName) != std::string::npos)
		{
			pSelectUIs.push_back(pUI.get());
		}
	}
	// 重複していない場合はそのまま返す
	if (pSelectUIs.size() == 0) return sName;

	int nDupCnt = 0;	// 重複回数
	// 名前が重複している場合は連番を付ける(重複がなくなるまで)
	while (!CheckUniqueUIName(sReName, pSelectUIs))
	{
		nDupCnt++;
		sReName = sName + "_" + std::to_string(nDupCnt);
	}

	return sReName;
}

/* ========================================
	名前重複チェック関数
	-------------------------------------
	内容：名前が重複しているかチェック
		　名前が含まれているオブジェクトの配列を渡す
	-------------------------------------
	引数1：sName	名前
	引数2：pObjects	オブジェクト配列
	-------------------------------------
	戻値：重複しているかどうか
=========================================== */
bool SceneBase::CheckUniqueName(std::string sName, std::vector<ObjectBase*> pObjects)
{
	for (auto& pObject : pObjects)
	{
		// 同じ名前がある場合
		if (sName == pObject->GetName())
		{
			return false;
		}
	}

	return true;
}

/* ========================================
	名前重複チェック(UI)関数
	-------------------------------------
	内容：名前が重複しているかチェック
		　名前が含まれているオブジェクトの配列を渡す
	-------------------------------------
	引数1：sName	名前
	引数2：pUIs	UI配列
	-------------------------------------
	戻値：重複しているかどうか
=========================================== */
bool SceneBase::CheckUniqueUIName(std::string sName, std::vector<UIObjectBase*> pUIs)
{
	for (auto& pUI : pUIs)
	{
		// 同じ名前がある場合
		if (sName == pUI->GetName())
		{
			return false;
		}
	}

	return true;
}

/* ========================================
	シーン名取得関数
	-------------------------------------
	戻値：シーン名
=========================================== */
std::string SceneBase::GetSceneName()
{
	return "SceneBase";
}

/* ========================================
	全オブジェクト取得関数
	-------------------------------------
	内容：シーンに所属する全てのオブジェクトを取得
	-------------------------------------
	戻値：取得したオブジェクトのポインタ配列
=========================================== */
std::vector<ObjectBase*> SceneBase::GetAllSceneObjects()
{
	std::vector<ObjectBase*> objects;

	for (const auto& pObject : m_pObjects)
	{
		objects.push_back(pObject.get());
	}

	return objects;
}

/* ========================================
	全UIオブジェクト取得関数
	-------------------------------------
	内容：シーンに所属する全てのUIオブジェクトを取得
	-------------------------------------
	戻値：取得したUIオブジェクトのポインタ配列
=========================================== */
std::vector<UIObjectBase*> SceneBase::GetAllSceneUIObjects()
{
	std::vector<UIObjectBase*> objects;

	for (const auto& pUIObject : m_pUIObjects)
	{
		objects.push_back(pUIObject.get());
	}

	return objects;
}

/* ========================================
	タグ別オブジェクト収集関数
	-------------------------------------
	内容：シーンに所属する特定のタグのオブジェクト
		　を全て収集する
	-------------------------------------
	戻値：取得したオブジェクトのポインタ配列
========================================== */
std::vector<ObjectBase*> SceneBase::GetSceneObjectsTag(E_ObjectTag tag)
{
	// 取得したオブジェクトを格納する配列
	std::vector<ObjectBase*> objects;

	// シーンに所属するオブジェクトを検索
	for (const auto& pObject : m_pObjects)
	{
		// オブジェクトの型が一致したら配列に追加
		if (pObject->GetTag() == tag)
		{
			objects.push_back(pObject.get());
		}
	}

	return objects;	// 取得したオブジェクトの配列を返す
}

/* ========================================
	タグ別オブジェクト収集関数
	-------------------------------------
	内容：シーンに所属する特定のタグのオブジェクト
		　を一番最初に見つかったものを取得する
	-------------------------------------
	戻値：取得したオブジェクトのポインタ
========================================== */
ObjectBase* SceneBase::GetSceneObjectTag(E_ObjectTag tag)
{
	// シーンに所属するオブジェクトを検索
	for (const auto& pObject : m_pObjects)
	{
		// 一番最初に見つかったオブジェクトを返す
		if (pObject->GetTag() == tag)
		{
			return pObject.get();
		}
	}

	return nullptr;
}


// デバッグ用 ========================================================
#ifdef _DEBUG

/* ========================================
	ウィンドウ初期化(オブジェクト一覧)関数
	-------------------------------------
	内容：オブジェクト一覧の初期化を行う
=========================================== */
void SceneBase::InitObjectList()
{
	using namespace DebugUI;


	// オブジェクト削除ボタン
	WIN_OBJ_LIST.AddItem(Item::CreateCallBack("Remove", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nObjectListSelectNo == -1) return;					// 選択されていない場合は処理しない
		// シーン上のカメラが1つの場合、カメラオブジェクトは削除不可
		if (dynamic_cast<ObjectCamera*>(m_pSelectObj) != nullptr && CAMERA_MNG_INST.GetCameraNum() == 1) return;
		// カメラオブジェクトがアクティブの場合、削除不可
		if (CAMERA_MNG_INST.GetActiveCamera() == m_pSelectObj)	return;

		m_pSelectObj->Destroy();	// オブジェクト削除

	}));

	// オブジェクトフォーカスボタン
	WIN_OBJ_LIST.AddItem(Item::CreateCallBack("Focus", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nObjectListSelectNo == -1) return;					// 選択されていない場合は処理しない
		// 選択されていない場合は処理しない
		if (m_nObjectListSelectNo == -1) return;
		// アクティブカメラはフォーカス移動不可
		if (m_pSelectObj == CAMERA_MNG_INST.GetActiveCamera()) return;

		CAMERA_MNG_INST.FocusMoveCamera(m_pSelectObj);	// カメラを指定オブジェクトにフォーカス移動

	}, false, true));

	// オブジェクト複製ボタン
	WIN_OBJ_LIST.AddItem(Item::CreateCallBack("Copy", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		// 選択されていない場合は処理しない
		if (m_nObjectListSelectNo == -1) return;
		// オブジェクトを複製
		m_pSelectObj->Copy();

	}, false, true));

	// オブジェクト選択時のコールバック関数
	Item::ConstCallback  FuncListClick = [this](const void* arg)
	{
		// クリックされたオブジェクトの情報を表示
		std::string sObjName = reinterpret_cast<const char*>(arg);
		m_nObjectListSelectNo = ITEM_OBJ_LIST.GetListNo(sObjName.c_str());	// 選択番号を取得

		InitObjectInfo(sObjName);
	};

	// オブジェクトリストを作成
	WIN_OBJ_LIST.AddItem(Item::CreateList(ITEM_OBJ_LIST_NAME.c_str(), FuncListClick, false, false, false, OBJECT_LIST_LINE_NUM));

}

/* ========================================
	ウィンドウ初期化(オブジェクト情報)関数
	-------------------------------------
	内容：オブジェクト情報の初期化を行う
		　※一覧のオブジェクト名をクリックする度呼ばれる
	-------------------------------------
	引数：string オブジェクト名
=========================================== */
void SceneBase::InitObjectInfo(std::string sName)
{
	using namespace DebugUI;

	WIN_OBJ_INFO.Clear();	// 表示リセット

	// 名前に"L"が含まれている場合(子オブジェクトの場合)
	if (sName.find(CHILD_HEAD_TEXT) != std::string::npos)
	{
		// "L"を除去した名前に変換
		int nHeadTextCnt = sName.find(CHILD_HEAD_TEXT);							// Lが含まれる位置を取得
		sName = sName.substr(nHeadTextCnt + CHILD_HEAD_TEXT.size());	// L以降の文字列を取得
	}

	// 名前に"*"が含まれている場合(親オブジェクトの場合)
	if (sName.find(PARENT_END_TEXT) != std::string::npos)
	{
		// "*"を除去した名前に変換
		int nEndTextCnt = sName.find(PARENT_END_TEXT);	// *が含まれる位置を取得
		sName = sName.substr(0, nEndTextCnt);	// *以前の文字列を取得
	}

	// 名前が一致するオブジェクトを検索
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetName() == sName)
		{
			// オブジェクト情報を表示
			pObject->Debug();			
			m_pSelectObj = pObject.get();	// 選択中のオブジェクトを保持

			bool bIsFold = pObject->GetIsFold() ? false : true;
			pObject->SetIsFold(bIsFold);	// 折りたたみ状態を変更

			break;
		}
	}
}

/* ========================================
	ウィンドウ初期化(UIオブジェクト一覧)関数
	-------------------------------------
	内容：UIオブジェクト一覧の初期化を行う
=========================================== */
void SceneBase::InitUIList()
{

	using namespace DebugUI;

	// UI削除ボタン
	WIN_UI_LIST.AddItem(Item::CreateCallBack("Remove", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nUISelectNo == -1) return;					// 選択されていない場合は処理しない

		m_pSelectUI->SetState(UIObjectBase::E_State::STATE_DEAD);	// 死亡状態に設定

	}));

	// UI複製ボタン
	WIN_UI_LIST.AddItem(Item::CreateCallBack("Copy", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nUISelectNo == -1) return;	// 選択されていない場合は処理しない

		UIObjectBase* pUI = m_pSelectUI->Copy();	// 選択中のUIオブジェクトを複製
	}, false, true));

	// オブジェクト選択時のコールバック関数
	Item::ConstCallback  FuncListClick = [this](const void* arg)
	{
		// クリックされたオブジェクトの情報を表示

		std::string sUIName = reinterpret_cast<const char*>(arg);
		m_nUISelectNo = ITEM_UI_LIST.GetListNo(sUIName.c_str());	// 選択番号を取得

		InitUIInfo(sUIName);
	};

	Item* pList = Item::CreateList(ITEM_UI_LIST_NAME.c_str(), FuncListClick, false);
	WIN_UI_LIST.AddItem(pList);
}

/* ========================================
	ウィンドウ初期化(UIオブジェクト情報)関数
	-------------------------------------
	内容：UIオブジェクト情報の初期化を行う
		　※一覧のオブジェクト名をクリックする度呼ばれる
	-------------------------------------
	引数：string UIオブジェクト名
=========================================== */
void SceneBase::InitUIInfo(std::string sName)
{
	using namespace DebugUI;

	WIN_UI_INFO.Clear();	// 表示リセット

	// 名前に"L"が含まれている場合(子オブジェクトの場合)
	if (sName.find(CHILD_HEAD_TEXT) != std::string::npos)
	{
		// "L"を除去した名前に変換
		int nHeadTextCnt = sName.find(CHILD_HEAD_TEXT);							// Lが含まれる位置を取得
		sName = sName.substr(nHeadTextCnt + CHILD_HEAD_TEXT.size());	// L以降の文字列を取得
	}

	// 名前に"*"が含まれている場合(親オブジェクトの場合)
	if (sName.find(PARENT_END_TEXT) != std::string::npos)
	{
		// "*"を除去した名前に変換
		int nEndTextCnt = sName.find(PARENT_END_TEXT);	// *が含まれる位置を取得
		sName = sName.substr(0, nEndTextCnt);	// *以前の文字列を取得
	}


	// 名前が一致するオブジェクトを検索
	for (auto& pUI : m_pUIObjects)
	{
		if (pUI->GetName() == sName)
		{
			// オブジェクト情報を表示
			pUI->Debug();
			m_pSelectUI = pUI.get();	// 選択中のオブジェクトを保持

			bool bIsFold = pUI->GetIsFold() ? false : true;
			pUI->SetIsFold(bIsFold);	// 折りたたみ状態を変更

			break;
		}
	}
}


/* ========================================
	デバッグ用オブジェクト一覧再読込関数
	-------------------------------------
	内容：オブジェクト一覧を再読み込みする
=========================================== */
void SceneBase::ReloadDebugObjectList()
{
	// オブジェクト一覧をクリア
	ITEM_OBJ_LIST.RemoveListItemAll();

	// オブジェクトを名前の昇順にソートする(オブジェクト一覧を見やすくするため)
	std::vector<ObjectBase*> pSortObjects = GetAllSceneObjects();	// シーンに所属する全てのオブジェクトを取得
	std::sort(pSortObjects.begin(), pSortObjects.end(), [](const ObjectBase* a, const ObjectBase* b)
	{
		return a->GetName() < b->GetName();
	});

	// 全てのオブジェクトをリストに追加
	for (const auto& pObject : pSortObjects)
	{
		if (pObject->GetParentObject()) continue;	// 親オブジェクトがある場合は飛ばす
		// オブジェクト一覧に追加
		ITEM_OBJ_LIST.AddListItem(pObject->GetListName().c_str());

		// 折りたたみ状態ではない場合は子オブジェクトを表示する
		if (!pObject->GetIsFold())
			AddObjectListChild(pObject);
	}

	// 名前変更や、親変更などで、オブジェクト一覧の位置がずれるため、選択中のオブジェクトを再選択する
	// 選択中のオブジェクトがある場合
	if(m_pSelectObj)
	{
		int nSelectNo = ITEM_OBJ_LIST.GetListNo(m_pSelectObj->GetListName().c_str());	// 選択中のオブジェクト番号を取得

		if (m_nObjectListSelectNo != nSelectNo)
		{
			ITEM_OBJ_LIST.SetListNo(nSelectNo);		// 選択中のオブジェクトを選択状態にする
			m_nObjectListSelectNo = nSelectNo;		// 選択中のオブジェクト番号を保持
		}
	}
}

/* ========================================
	デバッグ用オブジェクト一覧子オブジェクト追加関数
	-------------------------------------
	内容：オブジェクト一覧に子オブジェクトを追加
		　※子がある限り再帰的に呼び出される
	-------------------------------------
	引数：ObjectBase* 親オブジェクト
=========================================== */
void SceneBase::AddObjectListChild(ObjectBase* pObject)
{
	// 子オブジェクトがある場合
	if (pObject->GetChildObjects().size() > 0)
	{
		if (pObject->GetIsFold()) return;	// 折りたたみ状態の場合は追加しない

		// 子オブジェクトを名前の昇順にソートする(オブジェクト一覧を見やすくするため)
		std::vector<ObjectBase*> pSortChildObjects = pObject->GetChildObjects();	// 子オブジェクトを取得
		std::sort(pSortChildObjects.begin(), pSortChildObjects.end(), [](const ObjectBase* a, const ObjectBase* b)
		{
			return a->GetName() > b->GetName();
		});

		// 全ての子オブジェクトをリストに追加
		for (auto& pChild : pSortChildObjects)
		{
			// 挿入位置
			int nInsertNo = ITEM_OBJ_LIST.GetListNo(pObject->GetListName().c_str());
			// オブジェクト一覧に追加
			ITEM_OBJ_LIST.InsertListItem(pChild->GetListName().c_str(), nInsertNo + 1);
			// 子オブジェクトを追加
			AddObjectListChild(pChild);	
		}
	}
	else
	{
		return;
	}
}

/* ========================================
	デバッグ用UIオブジェクト一覧再読込関数
	-------------------------------------
	内容：UIオブジェクト一覧を再読み込みする
=========================================== */
void SceneBase::ReloadDebugUIList()
{
	// オブジェクト一覧をクリア
	ITEM_UI_LIST.RemoveListItemAll();

	// オブジェクトを名前の昇順にソートする(オブジェクト一覧を見やすくするため)
	std::vector<UIObjectBase*> pSortUIs = GetAllSceneUIObjects();	// シーンに所属する全てのオブジェクトを取得
	std::sort(pSortUIs.begin(), pSortUIs.end(), [](const UIObjectBase* a, const UIObjectBase* b)
	{
		return a->GetName() < b->GetName();
	});

	// 全てのUIをリストに追加
	for (const auto& pUI : pSortUIs)
	{
		if (pUI->GetParentUI()) continue;	// 親オブジェクトがある場合は飛ばす
		// オブジェクト一覧に追加
		ITEM_UI_LIST.AddListItem(pUI->GetListName().c_str());

		// 折りたたみ状態ではない場合は子オブジェクトを表示する
		if (!pUI->GetIsFold())
			AddUIListChild(pUI);
	}	
	
	// 名前変更や、親変更などで、オブジェクト一覧の位置がずれるため、選択中のオブジェクトを再選択する
	// 選択中のオブジェクトがある場合
	if (m_pSelectUI)
	{
		int nSelectNo = ITEM_UI_LIST.GetListNo(m_pSelectUI->GetListName().c_str());	// 選択中のオブジェクト番号を取得

		if (m_nUISelectNo != nSelectNo)
		{
			ITEM_UI_LIST.SetListNo(nSelectNo);	// 選択中のオブジェクトを選択状態にする
			m_nUISelectNo = nSelectNo;			// 選択中のオブジェクト番号を保持
		}
	}
}

/* ========================================
	デバッグ用UIオブジェクト一覧子オブジェクト追加関数
	-------------------------------------
	内容：UIオブジェクト一覧に子オブジェクトを追加
		　※子がある限り再帰的に呼び出される
	-------------------------------------
	引数：UIObjectBase* 親UIオブジェクト
=========================================== */
void SceneBase::AddUIListChild(UIObjectBase* pUIObject)
{
	// 子オブジェクトがある場合
	if (pUIObject->GetChildUIs().size() > 0)
	{
		if (pUIObject->GetIsFold()) return;	// 折りたたみ状態の場合は追加しない

		// 子オブジェクトを名前の昇順にソートする(オブジェクト一覧を見やすくするため)
		std::vector<UIObjectBase*> pSortChildUIs = pUIObject->GetChildUIs();	// 子オブジェクトを取得
		std::sort(pSortChildUIs.begin(), pSortChildUIs.end(), [](const UIObjectBase* a, const UIObjectBase* b)
		{
			return a->GetName() > b->GetName();
		});

		// 全ての子オブジェクトをリストに追加
		for (auto& pChild : pSortChildUIs)
		{
			// 挿入位置
			int nInsertNo = ITEM_UI_LIST.GetListNo(pUIObject->GetListName().c_str());
			// オブジェクト一覧に追加
			ITEM_UI_LIST.InsertListItem(pChild->GetListName().c_str(), nInsertNo + 1);
			// 子オブジェクトを追加
			AddUIListChild(pChild);
		}
	}
	else
	{
		return;
	}
}

#endif