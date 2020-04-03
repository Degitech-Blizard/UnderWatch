#include "DXUT.h"
#include "CEnemy02.h"
#include "CEnemyBullet.h"
#include "CBullet.h"

CEnemy02::CEnemy02()
{
}


CEnemy02::~CEnemy02()
{
}

void CEnemy02::Awake()
{
	AddComponent<CMeshRenderer>()->SetModel(MODEL["ZOMNIC"]);
	AddComponent<CAnimation3D>()->AddAnimator("IDLE", "ENEMY02_IDLE", 1.f / 60.f, true);
	GetComponent<CAnimation3D>()->AddAnimator("DIE", "ENEMY02_DIE", 1.f / 60.f, FALSE);
	GetComponent<CAnimation3D>()->AddAnimator("LAUNCH", "ENEMY02_LAUNCH", 1.f / 60.f, FALSE);
	GetComponent<CAnimation3D>()->AddAnimator("SHOOT", "ENEMY02_SHOOT", 1.f/60.f, true);
	GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");

	AddComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(35, 130, 35)));
	GetComponent<CBoxCollider3D>()->SetOffset(Vector3(0, 80, 0));
	//	AddComponent<CSphereCollider3D>()->SetSphere(Sphere(this->Transform->GetPosition(),64));

	m_Status = ENEMY02_STATUS::ENEMY02_IDLE;
	this->m_fFireDelay = 1.f;
}

void CEnemy02::Start()
{
	m_pPlayer = OBJECT.FindObjectWithTag(Tag::Player);
	GetComponent<CEnemyBase>()->m_fOffset = 200.f;
	m_fTime = rand() % 6000 / 1000.f + 1.f;
}

void CEnemy02::Update()
{
	switch (m_Status)
	{
	case ENEMY02_STATUS::ENEMY02_IDLE:
	{
		Vector3 Dir = Vector3(-1717, 64, -646) - this->Transform->GetPosition();
		D3DXVec3Normalize(&Dir, &Dir);
		this->Transform->Translation(Dir * 250 * DeltaTime);
		//m_fDegree += 300 * DeltaTime;
		//m_fOffset = sinf(D3DXToRadian(m_fDegree));
		//this->Transform->SetPosition(Vector3(this->Transform->GetPosition().x, this->Transform->GetPosition().y + m_fOffset, +this->Transform->GetPosition().z));
		this->Transform->SetRotation(Vector3(0, D3DXToDegree(atan2f(Dir.x, Dir.z)), 0));

		m_fTime -= DeltaTime;
		if (m_fTime <= 0.f) m_Status = ENEMY02_STATUS::ENEMY02_LAUNCH;
		break;
	}
	case  ENEMY02_STATUS::ENEMY02_LAUNCH:
	{
		GetComponent<CAnimation3D>()->SetHandleAnimator("LAUNCH");
		if (GetComponent<CAnimation3D>()->GetAnimator("LAUNCH")->GetEnable() == FALSE)
		{
			m_fTime2 = 0.f;
			m_Status = ENEMY02_STATUS::ENENMY02_SHOOT;
		}
		break;

	}
	case ENEMY02_STATUS::ENENMY02_SHOOT:
	{
		//Vector3 Dir = Vector3(0, 0, 1);
		//

		GetComponent<CAnimation3D>()->SetHandleAnimator("SHOOT");

		//if (!GetComponent<CAnimation3D>()->GetAnimator("SHOOT")->GetEnable())
		//{
		//	if (m_fTime2 > m_fFireDelay)
		//	{
		//		GetComponent<CAnimation3D>()->GetAnimator("SHOOT")->SetEnable(true);
		//		GetComponent<CAnimation3D>()->GetAnimator("SHOOT")->SetCurFrame(0);
		//		m_fTime2 = 0.f;
		//		m_bFire = true;
		//	}
		//	else
		//	{
		//		m_fTime2 += DeltaTime;


		//	}
		//}


		//if (m_bFire)
		//{
		//	if (GetComponent<CAnimation3D>()->GetAnimator("SHOOT")->GetNormalizedTime() >= 0.7f)
		//	{
		//		Vector3 Dir = Vector3(0, 0, 1);
		//		for (int i = 0; i < 18; i++)
		//		{

		//			float Angle = D3DXToRadian(i * 20);
		//			Matrix matRot;
		//			D3DXMatrixRotationY(&matRot, Angle);
		//			D3DXVec3TransformNormal(&Dir, &Dir, &matRot);
		//			auto pBullet = OBJECT.AddObject("", Tag::EnemyBullet);
		//			pBullet->AddComponent<CBullet>();
		//			pBullet->Transform->SetPosition(this->Transform->GetPosition());
		//			pBullet->GetComponent<CBullet>()->m_vDir = Dir;
		//			pBullet->GetComponent<CBullet>()->m_fSpeed = 400;
		//			pBullet->Transform->SetScale(Vector3(100, 100, 100));
		//			//pBullet->GetComponent<CMeshRenderer>()->SetModel(MODEL["ENEMY02_BULLET"]);
		//		}
		//		m_bFire = false;
		//	}
		//}
		m_fTime2 += DeltaTime;

		if (m_fTime2 > m_fFireDelay)
		{
			m_fTime2 = 0.f;
			Vector3 vDir = Vector3(0, 0, 1);
			m_fRotationOffset += 5.f;
			for (int i = 0; i < 9; i++)
			{

				float Angle = D3DXToRadian(i * 40 + m_fRotationOffset);
				Matrix matRot;
				D3DXMatrixRotationY(&matRot, Angle);
				D3DXVec3TransformNormal(&vDir, &vDir, &matRot);
				auto pBullet = OBJECT.AddObject("", Tag::EnemyBullet);
				pBullet->AddComponent<CBullet>();
				pBullet->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0, 90, 0)) ;
				pBullet->GetComponent<CBullet>()->m_vDir = vDir;
				pBullet->GetComponent<CBullet>()->m_fSpeed = 1200;
				pBullet->Transform->SetScale(Vector3(1, 1, 1));
				pBullet->GetComponent<CMeshRenderer>()->SetModel(MODEL["ENEMY02_BULLET"]);


			}
		}
		break;
	}
	}


}

void CEnemy02::LateUpdate()
{

}

void CEnemy02::OnDestroy()
{
	SCENE.m_iScore += 500;
	CObject * pEffect = OBJECT.AddObject();
	pEffect->Transform->SetPosition(this->Transform->GetPosition());
	pEffect->Transform->SetScale(Vector3(1.f, 1.f, 1.f));

	pEffect->AddComponent<CEffect3D>()->SetEffect("ENEMY02_DIE", 0.f);
}

void CEnemy02::OnRender()
{
}

void CEnemy02::OnEnable()
{
}

void CEnemy02::OnDisable()
{
}

void CEnemy02::OnCollisionEnter(CObject * _pObject)
{
}

void CEnemy02::OnCollisionStay(CObject * _pObject)
{
}

void CEnemy02::OnCollisionExit(CObject * _pObject)
{
}
