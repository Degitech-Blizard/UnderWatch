#include "DXUT.h"
#include "CHealMachine.h"
#include "CPlayer.h"

CHealMachine::CHealMachine()
{
}


CHealMachine::~CHealMachine()
{
}

void CHealMachine::Awake()
{
	this->m_fDuraction = 0.f;
	this->m_fHealPerSec = 0.f;

	this->m_fTime = 0.f;
	this->AddComponent<CMeshRenderer>()->SetModel(MODEL["Model"]);
	this->AddComponent<CAnimation3D>()->AddAnimator("IDLE", "3D_PLAYER_HEALMACHINE", 1.f/60.f, true);
	this->GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");



}

void CHealMachine::Start()
{

	m_pPlayer = OBJECT.FindObjectWithTag(Tag::Player);

	m_pFloor = OBJECT.AddObject();
	m_pFloor->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0,10,0));
	m_pFloor->AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_PLAYER_HEALFLOOR"]);
	m_pFloor->Transform->SetScale(Vector3(m_fRange,1,m_fRange));
}

void CHealMachine::Update()
{
	m_fTime += DeltaTime;

	if (m_fTime > m_fDuraction)
	{
		m_pObject->Destroy();
		m_pFloor->Destroy();
	}
	else
	{
		float distance = abs(D3DXVec3Length(&(this->Transform->GetPosition() - m_pPlayer->Transform->GetPosition())));
		if (distance < m_fRange * 50)
		{
			auto Player = m_pPlayer->GetComponent<CPlayer>();
			Player->m_fCurHp += m_fHealPerSec * DeltaTime ;
			if (Player->m_fMaxHp < Player->m_fCurHp) 
				Player->m_fCurHp = Player->m_fMaxHp;
		}
	}
}

void CHealMachine::LateUpdate()
{
}

void CHealMachine::OnDestroy()
{
}

void CHealMachine::OnRender()
{
}

void CHealMachine::OnEnable()
{
}

void CHealMachine::OnDisable()
{
}

void CHealMachine::OnCollisionEnter(CObject * _pObject)
{
}

void CHealMachine::OnCollisionStay(CObject * _pObject)
{
}

void CHealMachine::OnCollisionExit(CObject * _pObject)
{
}
