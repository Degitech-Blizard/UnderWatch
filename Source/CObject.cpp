#include "DXUT.h"
#include "CObject.h"


CObject::CObject()
{
}


CObject::~CObject()
{
	for (auto iter : m_Components)
	{
		SAFE_DELETE(iter);
	}
	m_Components.clear();
}

void CObject::Init()
{
}

void CObject::Render()
{
}

void CObject::Update()
{
}

void CObject::Release()
{
	for (auto iter : m_Components)
	{
		iter->OnDestroy();
	}
}




