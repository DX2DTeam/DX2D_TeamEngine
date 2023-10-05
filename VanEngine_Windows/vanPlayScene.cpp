#include "vanPlayScene.h"
#include "vanResources.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayerScript.h"
#include "vanRigidbody.h"
#include "vanCollisionManager.h"


namespace van
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		{
			// Player
			GameObject* object = new GameObject();
			Transform* tr = object->AddComponent<Transform>();
			tr->SetPosition(Vector3(0.5f, 1.0f, 0.0f));
			tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			MeshRenderer* meshRenderer = object->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"CircleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			Rigidbody* rb = object->AddComponent<Rigidbody>();
			Collider* col = object->AddComponent<Collider>();
			col->SetSize(Vector3(0.05f, 0.05f, 0.0f));
			col->SetPosition(tr->GetPosition());

			AddGameObject(object, LAYER::PLAYER);
			object->AddComponent<PlayerScript>();

			// Floor
			GameObject* object1 = new GameObject();
			Transform* tr1 = object1->AddComponent<Transform>();
			tr1->SetPosition(Vector3(0.3f, -1.5f, 0.0f));
			tr1->SetScale(Vector3(0.5f, 0.25f, 0.5f));

			MeshRenderer* meshRenderer1 = object1->AddComponent<MeshRenderer>();
			meshRenderer1->SetMesh(Resources::Find<Mesh>(L"RectangleMesh"));
			meshRenderer1->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			Collider* col1 = object1->AddComponent<Collider>();
			col1->SetSize(Vector3(0.5f, 0.25f, 0.0f));
			col1->SetPosition(tr1->GetPosition());

			AddGameObject(object1, LAYER::FLOOR);
			//object->AddComponent<PlayerScript2>();

			CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}
