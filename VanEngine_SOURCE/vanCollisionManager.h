#pragma once
#include "CommonInclude.h"
#include "vanCollider.h"

namespace van
{
#define LAYER_MAX (UINT)LAYER::MAX

	union COlliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	using namespace enums;
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Release();

		static void Clear();
		static void CollisionLayerCheck(LAYER left, LAYER right, bool enable);	// �浹 üũ �Ұ��� ���Ұ��� 
		static void LayerCollision(class Scene* scene, LAYER left, LAYER right);	// ���̾�� ���� �浹üũ
		static void ColliderCollision(Collider* left, Collider* right);						// �浹�� ����
		static bool Intersect(Collider* left, Collider* reight);							// �浹���� Ȯ��


	private:
		static std::map<UINT64, bool> _mCollisionMap;
		static std::bitset<LAYER_MAX> _mLayerMasks[LAYER_MAX];	//bitset = <> ����ŭ �޸� ����Ʈ
	};
}

