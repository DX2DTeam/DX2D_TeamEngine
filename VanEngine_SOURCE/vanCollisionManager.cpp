#include "vanCollisionManager.h"
#include "vanSceneManager.h"

namespace van
{
	std::map<UINT64, bool> CollisionManager::_mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::_mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				if (_mLayerMasks[row][col] == true)
				{
					LayerCollision(activeScene, (LAYER)row, (LAYER)col);
				}
			}
		}
	}
	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Release()
	{
	}
	void CollisionManager::Clear()
	{
		_mLayerMasks->reset();
		_mCollisionMap.clear();
	}
	void CollisionManager::CollisionLayerCheck(LAYER left, LAYER right, bool enable)
	{
		int row = -1;
		int col = -1;

		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}

		_mLayerMasks[row][col] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene, LAYER left, LAYER right)
	{
		// finds left layer objects
		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		// finds right layer Objects
		Layer& rightLayer = scene->GetLayer(right);
		std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		// finds right layer Objects
		for (GameObject* left : lefts)
		{
			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// �� �浹ü�� ID�� Ȯ��
		COlliderID ID;
		ID.left = (UINT)left->GetCollisionNumber();
		ID.right = (UINT)right->GetCollisionNumber();


		// ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
		std::map<UINT64, bool>::iterator iter
			= _mCollisionMap.find(ID.id);

		// Ȥ�� �浹������ ���ٸ� �������ָ�ȴ�
		if (iter == _mCollisionMap.end())
		{
			_mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = _mCollisionMap.find(ID.id);
		}


		//�浹�Լ� ȣ��
		if (Intersect(left, right))
		{
			// �浹 ���λ���
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);

				iter->second = true;

			}
			else // ó�� �浹�ϴ� ����
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// �浹�� ������������
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector3 leftPos = left->GetPosition();
		Vector3 rightPos = right->GetPosition();

		Vector3 leftSize = left->GetSize();
		Vector3 rightSize = right->GetSize();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
		{
			return true;
		}

		return false;
	}
}