/* ========================================
	CatRobotGame/
	------------------------------------
	���X�|�[���p�w�b�_
	------------------------------------
	�����F�Փ˂����烊�X�|�[������I�u�W�F�N�g
	------------------------------------
	ObjectRespawn.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "ObjectBase.h"

// =============== �O���錾 =======================
class ComponentCollisionAABB;

// =============== �N���X =======================
class ObjectRespawn :
    public ObjectBase
{
public:
	// ���X�|�[�����
	enum E_RespawnType
	{
		RT_RELOAD_SCENE,	// �V�[�����ēǂݍ���
		RT_POSITION,		// ���܂����ʒu���烊�X�|�[��
	};

public:
	ObjectRespawn(SceneBase* pScene);

	void InitLocal() override;
	void UpdateLocal() override;

	void OnCollisionEnter(ObjectBase* pHit) override;

	// �Q�b�^�[
	E_RespawnType GetRespawnType() const;
	Vector3<float> GetRespawnPosition() const;

	// �Z�b�^�[
	void SetRespawnType(E_RespawnType type);
	void SetRespawnPosition(const Vector3<float>& pos);

	DEFINE_OBJECT_TYPE(ObjectRespawn)
private:
	E_RespawnType	m_RespawnType;			// ���X�|�[�����
	Vector3<float>	m_RespawnPosition;		// ���X�|�[���ʒu

	bool			m_IsReloadScene;		// �V�[���ēǂݍ��݃t���O

	ComponentCollisionAABB* m_pCompColAABB;	// �����蔻��
};

