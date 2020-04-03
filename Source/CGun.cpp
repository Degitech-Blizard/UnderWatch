#include "DXUT.h"
#include "CGun.h"

#include "CPlayer.h"
CGun::CGun()
{
}


CGun::~CGun()
{
}


void CGun::Awake()
{
	Last = Vector3(0, 0, 0);
	//this->m_pObject->m_pParent = m_pPlayer;
	this->Transform->SetScale(Vector3(0.1, 0.1, 0.1));
	this->Transform->SetRotation(Vector3(0, 90, 0));
	AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_PLAYER_GUN"]);
	AddComponent<CAnimation3D>()->AddAnimator("GUN", "3D_PLAYER_GUN", 1.f / 60.f, true);
	GetComponent<CAnimation3D>()->SetHandleAnimator("GUN");
}

void CGun::Start()
{
	m_pPlayer = OBJECT.FindObjectWithName("Player");
}

void CGun::Update()
{

	if (m_pPlayer->GetComponent<CPlayer>()->m_IsFire == false)
	{
		this->GetComponent<CAnimation3D>()->GetHandleAnimator()->SetCurFrame(0);
		this->GetComponent<CAnimation3D>()->GetHandleAnimator()->SetEnable(FALSE);
	}
	else 		this->GetComponent<CAnimation3D>()->GetHandleAnimator()->SetEnable(true);
	Vector3 vDir = CAMERA.GetPos() - this->Transform->GetPosition();
	D3DXVec3Normalize(&vDir, &vDir);


	Vector3 offset = Vector3(-15, -15, 12);

	Matrix matRotX, matRotY, matRot;
	D3DXMatrixRotationZ(&matRotX, D3DXToRadian(CAMERA.GetRotation().x));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(CAMERA.GetRotation().y  +90));

	matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&offset, &offset, &matRot);
	Vector3 vRotation = this->Transform->GetRotation();
	Lerp(&vRotation, vRotation, Vector3(CAMERA.GetRotation().x, CAMERA.GetRotation().y, 0), DeltaTime *80);


	this->Transform->SetRotation(Vector3(CAMERA.GetRotation().x, CAMERA.GetRotation().y, 0));
	Vector3 vPosition = this->Transform->GetPosition() - offset - Vector3(0, 64, 0);
	//Lerp(&vPosition, vPosition, m_pPlayer->Transform->GetPosition(), DeltaTime * 80);


	//this->Transform->SetPosition( m_pPlayer->Transform->GetPosition() + offset  +Vector3(0, 64, 0));
	Last = offset;
}

void CGun::LateUpdate()
{
}

void CGun::OnDestroy()
{
}

void CGun::OnRender()
{
}

void CGun::OnEnable()
{
}

void CGun::OnDisable()
{
}

void CGun::OnCollisionEnter(CObject * _pObject)
{
}

void CGun::OnCollisionStay(CObject * _pObject)
{
}

void CGun::OnCollisionExit(CObject * _pObject)
{
}


