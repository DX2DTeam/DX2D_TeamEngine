#pragma once
#include "vanEnums.h"
#include "vanEntity.h"
#include "vanLayer.h"

namespace van
{
	using namespace van::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Layer& GetLayer(UINT index) { return mLayers[index]; }
		void AddGameObject(GameObject* gameObject, UINT layerIndex);
		void RemoveLayer(enums::LAYER type);

		int GetStarCount() { return mStarCount; }
		void SetStarCount(int value) { mStarCount = value; }
		
	private:
		Layer mLayers[LAYER::MAX];
		int mStarCount;
	};
}
