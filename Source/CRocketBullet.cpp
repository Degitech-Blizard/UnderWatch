#include "DXUT.h"
#include "CRocketBullet.h"
#include "CEnemy01.h"
#include "CEnemyBase.h"

CRocketBullet::CRocketBullet()
{
}


CRocketBullet::~CRocketBullet()
{
}

void CRocketBullet::Awake()
{
	this->AddComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(10, 10, 10)));
	AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_PLAYER_ROCKET"]);
}

void CRocketBullet::Start()
{
}

void CRocketBullet::Update()
{
	m_fTime += DeltaTime;
	if (m_fTime > 2.f) this->m_pObject->Destroy();

	this->Transform->Rotate(0, 0, 540 * DeltaTime);
	this->Transform->Translation(m_vDir * DeltaTime * 4000);
	this->GetComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(1, 1, D3DXVec3Length(&(m_vDir * DeltaTime * 2000.f)))));
	this->GetComponent<CBoxCollider3D>()->SetOffset(Vector3(0, 0, -D3DXVec3Length(&(m_vDir * DeltaTime * 2000.f))));
}

void CRocketBullet::LateUpdate()
{
	if (m_listEnemy.empty() == false)
	{
		float distance = 99999990.f;
		CObject * pObject = nullptr;
		for (auto iter : m_listEnemy)
		{
			if (distance > abs(D3DXVec3Length(&(iter->Transform->GetPosition() - this->Transform->GetPosition()))))
			{
				distance = abs(D3DXVec3Length(&(iter->Transform->GetPosition() - this->Transform->GetPosition())));
				pObject = iter;
			}
		}
		list<CObject *> a = OBJECT.GetCotainObject(pObject->Transform->GetPosition(), 450, Tag::Enemy);
		for (auto iter : a)
		{
			iter->GetComponent<CEnemyBase>()->Hit(8);
		}

		SOUND.Play("SND_PLAYER_EXPLOSION", false);
		CObject * pEffect = OBJECT.AddObject();
		pEffect->Transform->SetPosition(pObject->Transform->GetPosition() + Vector3(0, 64, 0));
		pEffect->Transform->SetScale(Vector3(0.4f, 0.4f, 0.4f));

		pEffect->AddComponent<CEffect>()->SetEffect("2D_EFFECT_EXPLOSION", 0.f);

		m_pObject->Destroy();
		m_listEnemy.clear();
	}
}

void CRocketBullet::OnDestroy()
{
}

void CRocketBullet::OnRender()
{
}

void CRocketBullet::OnEnable()
{
}

void CRocketBullet::OnDisable()
{
}

void CRocketBullet::OnCollisionEnter(CObject * _pObject)
{
	if (_pObject->GetObjectTag() == Tag::Enemy)
	{
		m_listEnemy.push_back(_pObject);
	}
}

void CRocketBullet::OnCollisionStay(CObject * _pObject)
{
}

void CRocketBullet::OnCollisionExit(CObject * _pObject)
{
}
