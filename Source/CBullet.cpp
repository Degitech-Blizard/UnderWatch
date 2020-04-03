#include "DXUT.h"
#include "CBullet.h"
#include "CEnemy01.h"
#include "CEnemyBase.h"
#include "CPlayer.h"
CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}


void CBullet::Awake()
{
	AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_PLAYER_BULLET"]); 
	AddComponent<CSphereCollider3D>()->SetSphere(CSphere(Vector3(0, 0, 0), 1));
	this->m_vOld = this->Transform->GetPosition();
	this->m_fTime = 0.f;
}

void CBullet::Start()
{
}

void CBullet::Update()
{
	m_fTime += DeltaTime;
	if (m_fTime > 10.f) this->m_pObject->Destroy();

	m_vOld = this->Transform->GetPosition();
	this->Transform->Translation(m_vDir * DeltaTime * m_fSpeed);


	CRay Ray = CAMERA.RayCastAtObject(m_vOld, m_vDir, D3DXVec3Length(&(m_vDir * DeltaTime * m_fSpeed)));
	if (this->m_pObject->GetObjectTag() == Tag::PlayerBullet)
	{
		CRaycastHit Hit = Physic.RayCast(Ray, Tag::Enemy);
		if (Hit.GetHitObject())
		{
			OnCollisionEnter(Hit.GetHitObject());
				//Hit.GetHitObject()->GetComponent<CEnemyBase>()->Hit(1);
			this->m_pObject->Destroy();
		}
	}
	else 	if (this->m_pObject->GetObjectTag() == Tag::Player)
	{
		CRaycastHit Hit = Physic.RayCast(Ray, Tag::Player);
		if (Hit.GetHitObject())
		{
			OnCollisionEnter(Hit.GetHitObject());
			this->m_pObject->Destroy();
		}
	}



}

void CBullet::LateUpdate()
{

}

void CBullet::OnDestroy()
{
}

void CBullet::OnRender()
{
}

void CBullet::OnEnable()
{
}

void CBullet::OnDisable()
{
}



void CBullet::OnCollisionEnter(CObject * _pObject)
{
	if (m_pObject->GetObjectTag() == Tag::PlayerBullet)
	{
		if (_pObject->GetObjectTag() == Tag::Enemy)
		{
			_pObject->GetComponent<CEnemyBase>()->Hit(1);


			CObject * pEffect = OBJECT.AddObject();
			pEffect->Transform->SetPosition(_pObject->Transform->GetPosition() + Vector3(0, 128, 0));
			pEffect->Transform->SetScale(Vector3(0.25f, 0.25f, 0.25f));

			pEffect->AddComponent<CEffect>()->SetEffect("2D_EFFECT_EXPLOSION", 1/60);

			m_pObject->Destroy();

		}
	}
	else if (m_pObject->GetObjectTag() == Tag::EnemyBullet)
	{
		if (_pObject->GetObjectTag() == Tag::Player)
		{
			SOUND.Play("SND_PLAYER_HIT", FALSE);
			_pObject->GetComponent<CPlayer>()->m_fCurHp -= 10;
			m_pObject->Destroy();
		}
	}
}

void CBullet::OnCollisionStay(CObject * _pObject)
{
}

void CBullet::OnCollisionExit(CObject * _pObject)
{
}
