#include "DXUT.h"
#include "CBulletEffect.h"
#include "CGun.h"

CBulletEffect::CBulletEffect()
{
}


CBulletEffect::~CBulletEffect()
{
}


void CBulletEffect::Awake()
{
}

void CBulletEffect::Start()
{
	int random = rand() % 4;

	switch (random)
	{
	case 0:
		this->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_FIREEFFECT_1"]);
		break;
	case 1:
		this->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_FIREEFFECT_2"]);
		break;
	case 2:
		this->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_FIREEFFECT_3"]);
		break;
	case 3:
		this->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_FIREEFFECT_4"]);
		break;
	}
	this->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_Billboard);

}

void CBulletEffect::Update()
{
	m_fTime += DeltaTime;
	if (m_fTime > 0.025f)
		this->m_pObject->Destroy();
}

void CBulletEffect::LateUpdate()
{
}

void CBulletEffect::OnDestroy()
{
}

void CBulletEffect::OnRender()
{
}

void CBulletEffect::OnEnable()
{
}

void CBulletEffect::OnDisable()
{
}

void CBulletEffect::OnCollisionEnter(CObject * _pObject)
{
}

void CBulletEffect::OnCollisionStay(CObject * _pObject)
{
}

void CBulletEffect::OnCollisionExit(CObject * _pObject)
{
}
