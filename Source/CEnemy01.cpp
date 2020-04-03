#include "DXUT.h"
#include "CEnemy01.h"
#include "CEnemyBase.h"
#include "CCastle.h"

CEnemy01::CEnemy01()
{
}


CEnemy01::~CEnemy01()
{
}
void CEnemy01::Awake()
{
	Transform->SetPosition(Vector3(0, 128, 0));
	Transform->SetScale(Vector3(1.f, 1.f, 1.f));
	AddComponent<CMeshRenderer>()->SetModel(MODEL["ZOMNIC"]);
	AddComponent<CAnimation3D>()->AddAnimator("IDLE", "ENEMY01_IDLE", 1.f / 60.f, true);
	GetComponent<CAnimation3D>()->AddAnimator("DIE", "ENEMY01_DIE", 1.f / 60.f, FALSE);
	GetComponent<CAnimation3D>()->AddAnimator("BOOM", "ENEMY01_BOOM", 1.f / 60.f, FALSE);
	GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");

	AddComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(35, 130, 35)));
	GetComponent<CBoxCollider3D>()->SetOffset(Vector3(0,80,0));
	//	AddComponent<CSphereCollider3D>()->SetSphere(Sphere(this->Transform->GetPosition(),64));
	m_pPlayer = OBJECT.FindObjectWithTag(Tag::Player);
}

void CEnemy01::Start()
{
	GetComponent<CEnemyBase>()->m_fOffset = 200.f;
}

void CEnemy01::Update()
{
	Vector3 Dir =  Vector3(-1717,30, -646) - this->Transform->GetPosition();
	D3DXVec3Normalize(&Dir, &Dir);
	this->Transform->Translation(Dir * 200 * DeltaTime);
	//m_fDegree += 300 * DeltaTime;
	//m_fOffset = sinf(D3DXToRadian(m_fDegree));
	this->Transform->SetPosition(Vector3(this->Transform->GetPosition().x, this->Transform->GetPosition().y + m_fOffset, +this->Transform->GetPosition().z));
	this->Transform->SetRotation(Vector3(0, D3DXToDegree(atan2f(Dir.x, Dir.z)),0));



}

void CEnemy01::LateUpdate()
{

		if (abs(D3DXVec3Length(&(Vector3(-1717, 30, -646) - this->Transform->GetPosition()))) < 10)
		{
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("BOOM");
	
			if (this->GetComponent<CAnimation3D>()->GetAnimator("BOOM")->GetEnable() == false)
			{
				OBJECT.FindObjectWithName("Castle")->GetComponent<CCastle>()->m_fCurHp -= 30;
				GetComponent<CEnemyBase>()->m_iCurHp = 0.f;
				SCENE.m_iScore -= 100;

			}
		}


}

void CEnemy01::OnDestroy()
{
	//if (this->GetComponent<CAnimation3D>()->GetAnimator("BOOM")->GetEnable() == true)
	{
		SCENE.m_iScore += 100;
		CObject * pEffect = OBJECT.AddObject();
		pEffect->Transform->SetPosition(this->Transform->GetPosition());
		pEffect->Transform->SetScale(Vector3(1.f, 1.f, 1.f));

		pEffect->AddComponent<CEffect3D>()->SetEffect("ENEMY01_DIE", 0.f);
	}
}

void CEnemy01::OnRender()
{
}

void CEnemy01::OnEnable()
{
}

void CEnemy01::OnDisable()
{
}

void CEnemy01::OnCollisionEnter(CObject * _pObject)
{


}

void CEnemy01::OnCollisionStay(CObject * _pObject)
{
}

void CEnemy01::OnCollisionExit(CObject * _pObject)
{
}
