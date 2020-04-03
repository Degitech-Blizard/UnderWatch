#include "DXUT.h"
#include "CFrustum.h"


CFrustum::CFrustum()
{
}


CFrustum::~CFrustum()
{
}

BOOL CFrustum::Make(Matrix* _matProj, Matrix * _matView)
{
	Matrix matInverseProjView = *_matView * *_matProj;
	D3DXMatrixInverse(&matInverseProjView, NULL, &matInverseProjView);

	m_vtx[0] = Vector3(-1.f, 1.f, 0.f);
	m_vtx[1] = Vector3(1.f, 1.f, 0.f);
	m_vtx[2] = Vector3(1.f, -1.f, 0.f);
	m_vtx[3] = Vector3(-1.f, 1.f, 0.f);
	m_vtx[4] = Vector3(-1.f, 1.f, 1.f);
	m_vtx[5] = Vector3(1.f, 1.f, 1.f);
	m_vtx[6] = Vector3(1.f, -1.f, 1.f);
	m_vtx[7] = Vector3(-1.f, -1.f, 1.f);

	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&m_vtx[i], &m_vtx[i], &matInverseProjView);
	}

	D3DXPlaneFromPoints(&m_plane[0], &m_vtx[0], &m_vtx[3], &m_vtx[2]);
	D3DXPlaneFromPoints(&m_plane[1], &m_vtx[4], &m_vtx[5], &m_vtx[6]);
	D3DXPlaneFromPoints(&m_plane[2], &m_vtx[0], &m_vtx[4], &m_vtx[7]);
	D3DXPlaneFromPoints(&m_plane[3], &m_vtx[1], &m_vtx[2], &m_vtx[6]);
	D3DXPlaneFromPoints(&m_plane[4], &m_vtx[0], &m_vtx[1], &m_vtx[5]);
	D3DXPlaneFromPoints(&m_plane[5], &m_vtx[3], &m_vtx[7], &m_vtx[6]);

	return NULL;
}


BOOL CFrustum::IsIn(D3DXVECTOR3 * pv)
{
	float fDist;
	// int i;

	// 현재는 left, right, far plane만 적용한다.
	// for( i = 0 ; i < 6 ; i++ )
	{
		fDist = D3DXPlaneDotCoord(&m_plane[3], pv);
		if (fDist > 0) return FALSE; // plane의 normal벡터가 far로 향하고 있으므로 양수이면 프러스텀의 바깥쪽
		fDist = D3DXPlaneDotCoord(&m_plane[4], pv);
		if (fDist > 0) return FALSE; // plane의 normal벡터가 left로 향하고 있으므로 양수이면 프러스텀의 왼쪽
		fDist = D3DXPlaneDotCoord(&m_plane[5], pv);
		if (fDist > 0) return FALSE; // plane의 normal벡터가 right로 향하고 있으므로 양수이면 프러스텀의 오른쪽
	}
}

BOOL CFrustum::IsInSphere(D3DXVECTOR3 * pv, float radius)
{
	float fDist;

	for (int i = 0; i < 6; i++)
	{
		fDist = D3DXPlaneDotCoord(&m_plane[i], pv);

		if (fDist < radius)
			return false;
	}
	return true;

}
