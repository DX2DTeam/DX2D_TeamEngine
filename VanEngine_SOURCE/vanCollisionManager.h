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
		static void CollisionLayerCheck(LAYER left, LAYER right, bool enable);	// 충돌 체크 할건지 안할건지 
		static void LayerCollision(class Scene* scene, LAYER left, LAYER right);	// 레이어들 전부 충돌체크
		static void ColliderCollision(Collider* left, Collider* right);						// 충돌시 동작
		static bool Intersect(Collider* left, Collider* reight);							// 충돌상태 확인


	private:
		static std::map<UINT64, bool> _mCollisionMap;
		static std::bitset<LAYER_MAX> _mLayerMasks[LAYER_MAX];	//bitset = <> 수만큼 메모리 바이트
	};
}

