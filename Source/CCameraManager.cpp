#include "DXUT.h"
#include "CCameraManager.h"
#include "CFrustum.h"


CCameraManager::CCameraManager()
{
	m_pFrustum = new CFrustum();
	m_vPos = Vector3(0, 0, -100);
	m_vTargetPos = Vector3(0, 0, -100);
	m_vLookAt= Vector3(0, 0, 0);
	m_vUp = Vector3(0, 1, 0);
	m_vRotation = Vector3(0, 180, 0);
	m_vTargetRotation = Vector3(0, 180, 0);
	m_fLastOffset = 0.f;
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLookAt, &m_vUp);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 10000000.f);
}


CCameraManager::~CCameraManager()
{
	SAFE_DELETE(m_pFrustum);
	SAFE_DELETE(m_pSkyBox);
}

CRay CCameraManager::RayCastAtScreen(CRVector2 _vPos,float _fMaxDistance)
{
	Vector2 vCursor = _vPos;

	Vector3 _vTransPos;


	D3DVIEWPORT9 ViewPort;
	g_Device->GetViewport(&ViewPort);
	Matrix matProj;
	g_Device->GetTransform(D3DTS_PROJECTION, &matProj);
	_vTransPos.x = (((2.0f * vCursor.x) / ViewPort.Width) - 1.0f)- matProj._31;
	_vTransPos.y = (((-2.0f * vCursor.y) / ViewPort.Height) + 1.0f)- matProj._32;


	_vTransPos.x /= matProj._11;
	_vTransPos.y /= matProj._22;
	_vTransPos.z = 1.f;

	CRay Ray;
	Ray.m_fMaxDistance = _fMaxDistance;
	Ray.m_vPos = Vector3(0.f,0.f,0.f);
	Ray.m_vDir = _vTransPos;

	//카메라 -> 월드
	Matrix matViewInverse;
	Matrix matView;
	g_Device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, NULL, &matView);


	D3DXVec3TransformCoord(&Ray.m_vPos, &Ray.m_vPos, &matViewInverse);

	D3DXVec3TransformNormal(&Ray.m_vDir, &Ray.m_vDir, &matViewInverse);

	D3DXVec3Normalize(&Ray.m_vDir, &Ray.m_vDir);

	return Ray;

}

CRay CCameraManager::RayCastAtObject(CRVector3 _vPos, CRVector3 _vDir, float _fMaxDistance)
{
	CRay Ray;
	Ray.m_fMaxDistance = _fMaxDistance;
	Ray.m_vPos = _vPos;
	Ray.m_vDir = _vDir;
	return Ray;
}


void CCameraManager::Update()
{
	D3DXVec3Normalize(&m_vLookAt, &m_vLookAt);

	if (m_bRebound == true)
	{
		m_fLastOffset = m_fOffset;
		Lerp(&this->m_fOffset, this->m_fOffset, m_fRebound, DeltaTime * 24);
		this->m_vTargetRotation.x -= m_fOffset - m_fLastOffset;
	}

	Lerp(&this->m_vRotation, this->m_vRotation,Vector3( this->m_vTargetRotation.x , this->m_vTargetRotation.y, this->m_vTargetRotation.z), DeltaTime * 18);
//	Lerp(&this->m_vPos, this->m_vPos, this->m_vTargetPos, DeltaTime * 36);

	D3DXMatrixRotationX(&matRotX, D3DXToRadian(this->m_vRotation.x));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(this->m_vRotation.y));

	Vector3 RotateLookAt = m_vLookAt;
	
	D3DXVec3TransformNormal(&RotateLookAt, &RotateLookAt, &(matRotX * matRotY));

	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &(m_vPos + RotateLookAt), &m_vUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 16000.F);

	m_pFrustum->Make(&m_matProj,&m_matView);
	if (m_pSkyBox)
		m_pSkyBox->FrameMove(DeltaTime);
}

void CCameraManager::Render()
{
	if(m_pSkyBox)
	m_pSkyBox->FrameRender();
}

void CCameraManager::SetTransform()
{
	g_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);
	g_Device->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCameraManager::SetBillboardTransform()
{
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	g_Device->GetTransform(D3DTS_VIEW,&matView);

	memset(&matView._41, 0, sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, 0, &matView);


	D3DXVECTOR3 BillPos = D3DXVECTOR3(0.f, 0.f, 0.f);

	float fScale[3];

	fScale[0] = 20.f;
	fScale[1] = 20.f;
	fScale[2] = 1.f;

	memcpy(&matView._41, &BillPos, sizeof(D3DXVECTOR3));

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matView(i, j) *= fScale[i];
	}

	g_Device->SetTransform(D3DTS_WORLD, &matView);
}

void CCameraManager::ForceRebound(float _fPower)
{
	m_fRebound += _fPower ;
	m_bRebound = true;
}
