#include "DXUT.h"
#include "CText.h"


CText::CText()
{
	OBJECT.RegisterRenderer2D(this);

}


CText::~CText()
{
	OBJECT.UnRegisterRenderer2D(this);

}


void CText::Awake()
{
}

void CText::Start()
{
}

void CText::Update()
{
}

void CText::LateUpdate()
{
}

void CText::Render()
{
}

void CText::OnRender()
{
}

void CText::OnDestroy()
{
}

void CText::OnEnable()
{
}

void CText::OnDisable()
{
}


void CText::OnCollisionEnter(CObject * _pObject)
{
}

void CText::OnCollisionStay(CObject * _pObject)
{
}

void CText::OnCollisionExit(CObject * _pObject)
{
}
