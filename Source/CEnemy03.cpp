#include "DXUT.h"
#include "CEnemy03.h"
#include "CCastle.h"
#include "CEnemyBase.h"
CEnemy03::CEnemy03()
{
}


CEnemy03::~CEnemy03()
{
}

void CEnemy03::Awake()
{
	Transform->SetPosition(Vector3(0, 0, 0));
	Transform->SetScale(Vector3(1.f, 1.f, 1.f));
	AddComponent<CMeshRenderer>()->SetModel(MODEL["ZOMNIC"]);
	AddComponent<CAnimation3D>()->AddAnimator("IDLE", "ENEMY03_IDLE", 1.f / 60.f, true);
	//GetComponent<CAnimation3D>()->AddAnimator("DIE", "ENEMY01_DIE", 0.1f, FALSE);
	//GetComponent<CAnimation3D>()->AddAnimator("BOOM", "ENEMY01_BOOM", 0.f, FALSE);
	GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");

	AddComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(40,200, 440)));
	//	AddComponent<CSphereCollider3D>()->SetSphere(Sphere(this->Transform->GetPosition(),64));
}

void CEnemy03::Start()
{
	m_pPlayer = OBJECT.FindObjectWithTag(Tag::Player);
	GetComponent<CEnemyBase>()->m_fOffset = 400.f;
}

void CEnemy03::Update()
{
	Vector3 Dir = Vector3(-1717, -36, -646) - this->Transform->GetPosition();
	D3DXVec3Normalize(&Dir, &Dir);
	this->Transform->Translation(Dir * 75 * DeltaTime);
	m_fDegree += 500 * DeltaTime;
	m_fOffset = sinf(D3DXToRadian(m_fDegree));
	this->Transform->SetPosition(Vector3(this->Transform->GetPosition().x, this->Transform->GetPosition().y + m_fOffset, +this->Transform->GetPosition().z));
	this->Transform->SetRotation(Vector3(0, D3DXToDegree(atan2f(Dir.x, Dir.z)), 0));


}

void CEnemy03::LateUpdate()
{
	if (abs(D3DXVec3Length(&(Vector3(-1717, -36, -646) - this->Transform->GetPosition()))) < 10)
	{
		i++;
		if (i > 10)
		{
			OBJECT.FindObjectWithName("Castle")->GetComponent<CCastle>()->m_fCurHp -= 100;
			GetComponent<CEnemyBase>()->m_iCurHp = 0.f;
			SCENE.m_iScore -= 1000;

		}
	}
}

void CEnemy03::OnDestroy()
{
	SCENE.m_iScore += 1000;
}

void CEnemy03::OnRender()
{
}

void CEnemy03::OnEnable()
{
}

void CEnemy03::OnDisable()
{
}

void CEnemy03::OnCollisionEnter(CObject * _pObject)
{
}

void CEnemy03::OnCollisionStay(CObject * _pObject)
{
}

void CEnemy03::OnCollisionExit(CObject * _pObject)
{
}
