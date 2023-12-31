#include "vanPlayer.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanRigidbody.h"
#include "vanResourceManager.h"
#include "vanCollider.h"
#include "vanSceneManager.h"
#include "..//VanEngine_Windows//vanPlayerScript.h"

van::Player::Player() :
	mbDead(false),
	mbCollisionCheck(false),
	mCollisionOther(nullptr),
	mPlayerDir(PlayerDir::Left),
	mbDoubleJumpCheck(false)
{
}

van::Player::~Player()
{
}

void van::Player::Initialize()
{

	Transform* tr = AddComponent<Transform>();
	tr->SetPosition(Vector3(-2.0f, -2.0f, 0.0f));
	tr->SetScale(Vector3(0.05f, 0.05f, 0.0f));

	MeshRenderer* meshRenderer = AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
	meshRenderer->SetShader(ResourceManager::Find<Shader>(L"PlayerShader"));

	Rigidbody* rb = AddComponent<Rigidbody>();

	Collider* col = AddComponent<Collider>();
	col->SetScale(Vector3(0.028f, 0.05f, 0.0f));
	col->SetPosition(tr->GetPosition());
	col->SetMesh(ResourceManager::Find<Mesh>(L"RectangleColliderMesh"));
	col->SetVisible(false);

	PlayerScript* playerScript = AddComponent<PlayerScript>();

	GameObject::Initialize();
}

void van::Player::Update()
{
	GameObject::Update();

	Transform* tr = GetComponent<Transform>();
	Vector3 pos = tr->GetPosition();

	if (pos.y < -1.0f)
		mbDead = true;

	if (mbDoubleJumpCheck)
	{
		tr->SetColor(1.0f, 1.0f, 0.0f, 0.0f);		// 아이템 먹을시 플레이어 색변환 현재값 흰색
	}
	else
	{
		tr->SetColor(0.0f, 0.5f, 1.f, 1.f);
	}

}

void van::Player::LateUpdate()
{
	GameObject::LateUpdate();
}

void van::Player::Render()
{
	GameObject::Render();
}

void van::Player::OnCollisionEnter(Collider* other)
{
	mCollisionOther = other;
}

void van::Player::OnCollisionStay(Collider* other)
{
}

void van::Player::OnCollisionExit(Collider* other)
{
	mCollisionOther = nullptr;
}
