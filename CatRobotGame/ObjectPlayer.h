/* ========================================
	DX22Base/
	------------------------------------
	�I�u�W�F�N�g(�v���C���[)�p�w�b�_
	------------------------------------
	�����F�v���C���[�p
	------------------------------------
	ObjectPlayer.h
========================================== */
#pragma once

// =============== �C���N���[�h =====================
#include "ObjectBase.h"
#include <memory>


class ComponentTransform;
class ComponentGroundRaycast;
class ComponentRigidbody;
class ComponentModelAnime;
class ComponentPlayerController;

// =============== �N���X��` =====================
class ObjectPlayer :
    public ObjectBase
{
public:
	ObjectPlayer(SceneBase* pScene);
	void InitLocal();
	void UpdateLocal();
	void DrawLocal();

	// �Q�b�^�[
	DEFINE_OBJECT_TYPE(ObjectPlayer)	// �I�u�W�F�N�g�̎��ID�擾�֐�

private:
	ComponentGroundRaycast* m_pCompGroundRaycast;
	ComponentRigidbody* m_pCompRigidbody;
	ComponentModelAnime* m_pCompModelAnime;
	ComponentPlayerController* m_pCompPlayerController;
};

