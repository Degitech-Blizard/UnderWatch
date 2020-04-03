#pragma once
#include "CSingleton.h"
class CFrustum;
class CCameraManager :
	public CSingleton< CCameraManager>
{

public:
	CCameraManager();
	~CCameraManager();

public:
	CRay RayCastAtScreen(CRVector2 _vPos, float _fMaxDistance = -1.f);
	CRay RayCastAtObject(CRVector3 _vPos, CRVector3 _vDir, float _fMaxDistance = -1.f);

	Matrix matRotX, matRotY, matRot;

	Matrix GetMatRot()
	{
		return (matRotX * matRotY);
	}

	void Update();
	void Render();
	void SetTransform();
	void SetBillboardTransform();
	Matrix m_matView;
	Matrix m_matProj;
	bool m_bRebound = true;
	void SetSkyBox(CSkyBox * _pSkyBox) { SAFE_DELETE(m_pSkyBox);  m_pSkyBox = _pSkyBox; }
private:
	CSkyBox * m_pSkyBox = nullptr;

	Vector3 m_vPos;
	Vector3 m_vRotation;
	Vector3 m_vLookAt;
	Vector3 m_vUp;
	float m_fRebound = 0.f;
	float m_fOffset = 0.f;
	float m_fLastOffset;
	CFrustum * m_pFrustum = nullptr;
public:
	Vector3 m_vTargetRotation;
	Vector3 m_vTargetPos;
	Vector3 GetPos() { return m_vPos; }
	void SetPos(Vector3 _vPos) { m_vPos = _vPos;  }

	Vector3 GetLookAt() {
		D3DXVec3Normalize(&m_vLookAt, &m_vLookAt);

		Matrix matRotX, matRotY, matRot;
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(this->m_vRotation.x));
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(this->m_vRotation.y));

		Vector3 RotateLookAt = m_vLookAt;

		D3DXVec3TransformNormal(&RotateLookAt, &RotateLookAt, &(matRotX * matRotY)); 
		return RotateLookAt; }
	void SetLookAt(Vector3 _vLookAt) { m_vLookAt = _vLookAt; }

	Vector3 GetUp() { return m_vUp;}
	void SetUp(Vector3 _vUp) { m_vUp = _vUp; }

	Vector3 GetRotation() { return m_vRotation; }
	Vector3 GetTargetRotation() { return m_vTargetRotation; }
	//Vector3 GetTargetPos() { return m_vTargetPos; }
	void ForceRebound(float _fPower);
	void SetRotation(Vector3 _vRotation) { m_vTargetRotation = _vRotation; }
	CFrustum * GetFrustum() { return m_pFrustum; }

};

#define CAMERA (*CCameraManager::GetInstance())

