#include "DXUT.h"
#include "CItem.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Awake()
{
	this->m_pBottom = OBJECT.AddObject("ItemBottom",Tag::Item);
	this->m_pBottom->AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_ITEM_BOTTOM"]);
	
	this->m_Kind = ItemKind::IK_HEAL;
	this->AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_ITEM_HEAL"]);
	this->AddComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(64.f, 20000.f, 64.f)));

	this->m_fDegree = 0.f;
	this->m_fOffset = 0.f;
}

void CItem::Start()
{
}

void CItem::Update()
{
	Vector3 Pos = this->Transform->GetPosition();
	Pos.y -= m_fOffset;
	m_pBottom->Transform->SetPosition(Vector3(Pos.x, Pos.y- 100, Pos.z));
	
	m_fDegree += 120 * DeltaTime;
	m_fOffset= sinf(D3DXToRadian(m_fDegree)) * 10;
	Pos.y += m_fOffset;
	this->Transform->SetPosition(Pos);
	this->GetComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(), Vector3(64.f, 20000.f, 64.f)));
}

void CItem::LateUpdate()
{
}

void CItem::OnDestroy()
{
}

void CItem::OnRender()
{
}

void CItem::OnEnable()
{
}

void CItem::OnDisable()
{
}

void CItem::OnCollisionEnter(CObject * _pObject)
{
	if (_pObject->GetObjectTag() == Tag::Player)
	{
		m_pObject->Destroy();
		if (this->m_Kind == ItemKind::IK_ATKUP)
		{
			
		}
		else if (this->m_Kind == ItemKind::IK_HPUP)
		{

		}
		else if (this->m_Kind == ItemKind::IK_HEAL)
		{

		}
	}
}

void CItem::OnCollisionStay(CObject * _pObject)
{
}

void CItem::OnCollisionExit(CObject * _pObject)
{
}
