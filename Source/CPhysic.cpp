#include "DXUT.h"
#include "CPhysic.h"

using namespace Math;
CPhysic::CPhysic()
{
}


CPhysic::~CPhysic()
{
}

bool CPhysic::GetPixelCollision(CTexture * _pTexture, CRRect _Box, D3DXCOLOR _Color)
{
	D3DLOCKED_RECT LockRect;

	_pTexture->m_pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

	DWORD* pColor = (DWORD*)LockRect.pBits; // 잠금후 픽셀 값 받아오기

	for (int i = _Box.Top; i < _Box.Bottom; i++)
	{
		for (int j = _Box.Left; j < _Box.Right; i++)
		{
			D3DXCOLOR col = pColor[_pTexture->m_Info.Width * i + j];

			if (col == _Color)
			{
				_pTexture->m_pTexture->UnlockRect(0); //  잠금 해제
				return true;
			}
		}
	}
	_pTexture->m_pTexture->UnlockRect(0); //  잠금 해제
	return false;
}

bool CPhysic::GetPixelCollision(CTexture * _pTexture, CRVector2 _Pos, D3DXCOLOR _Color)
{
	D3DLOCKED_RECT LockRect;

	_pTexture->m_pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

	DWORD* pColor = (DWORD*)LockRect.pBits; // 잠금후 픽셀 값 받아오기

	D3DXCOLOR col = pColor[_pTexture->m_Info.Width * (INT)_Pos.y + (INT)_Pos.x];

	bool Collision = false;
	if (col == _Color)
		Collision = true;

	_pTexture->m_pTexture->UnlockRect(0); //  잠금 해제
	return Collision;
}

bool CPhysic::CheckCollision(const Circle & _Circle01, const Circle & _Circle02)
{
	float r = _Circle01.Radius + _Circle02.Radius;

	if (r < sqrtf((_Circle01.Center.x - _Circle02.Center.x) * (_Circle01.Center.x - _Circle02.Center.x) + (_Circle01.Center.y - _Circle02.Center.y) * (_Circle01.Center.y - _Circle02.Center.y)))
	{
		return true;
	}

	return false;
}

bool CPhysic::CheckCollision(const Circle & _Circle01, const Vector2 & _vPos)
{
	float			check_x = _Circle01.Center.x - _vPos.x;	
	float			check_y = _Circle01.Center.y - _vPos.y;
	int			distance = sqrt((check_x * check_x) + (check_y * check_y));	

	if (distance <= _Circle01.Radius)
	{
		return true;
	}

	return false;
}

bool CPhysic::CheckCollision(const Rect & _reRect, const Vector2 & _vPos)
{
	return (_reRect.Left < _vPos.x &&
		_reRect.Top < _vPos.y &&
		_reRect.Right > _vPos.x &&
		_reRect.Bottom > _vPos.y);
}

bool CPhysic::CheckCollision(const Vector2 & _vPos, const Rect & _reRect)
{
	return CheckCollision(_reRect, _vPos);
}

bool CPhysic::CheckCollision(const Rect & _reRect01, const Rect & _reRect02)
{
	return (_reRect01.Left < _reRect02.Right &&
		_reRect01.Top <  _reRect02.Bottom &&
		_reRect01.Right > _reRect02.Left &&
		_reRect01.Bottom > _reRect02.Bottom);
}

bool CPhysic::CheckCollision(const Rect & _reRect01, float _fRot01, const Rect & _reRect02, float _fRot02)
{
	Vector2 dist = GetDistanceVector(_reRect01, _reRect02);
	Vector2 vec[4] = { GetHeightVector(_reRect01,_fRot01), GetHeightVector(_reRect02,_fRot02), GetWidthVector(_reRect01,_fRot01), GetWidthVector(_reRect02,_fRot02) };

	Vector2 unit;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		unit = GetUnitVector(vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += absDotVector(vec[j], unit);
		}
		if (absDotVector(dist, unit) > sum) {
			return false;
		}
	}
	return true;
}

bool CPhysic::CheckCollision( const Box& _Box01, Vector3 _vRot01, const Box& _Box02, Vector3 _vRot02)
{
	Box Box01 = _Box01;
	Box Box02 = _Box02;
	Box01.Rotation = _vRot01;
	Box02.Rotation = _vRot02;
	Vector3 D = _Box01.Center - _Box02.Center;

	Vector3 C[3];
	Vector3 absC[3];
	Vector3 AD;
	Vector3 Radius;
	float R0, R1, R;
	float R01;

	
	C[0].x = D3DXVec3Dot(&Box01.GetAxisX(), &Box02.GetAxisX());
	C[0].y = D3DXVec3Dot(&Box01.GetAxisX(), &Box02.GetAxisY());
	C[0].z = D3DXVec3Dot(&Box01.GetAxisX(), &Box02.GetAxisZ());
	AD.x = D3DXVec3Dot(&Box01.GetAxisX(), &D);
	absC[0].x = fabsf(C[0].x);
	absC[0].y = fabsf(C[0].y);
	absC[0].z = fabsf(C[0].z);

	R = fabs(AD.x);
	R1 = Box01.Radius.x * absC[0].x + Box01.Radius.y * absC[0].y + Box01.Radius.z * absC[0].z;
	R01 = Box01.Radius.x + R1;
	if (R > R01)return 0;

	//A1
	C[1].x = D3DXVec3Dot(&Box01.GetAxisY(), &Box02.GetAxisX());
	C[1].y = D3DXVec3Dot(&Box01.GetAxisY(), &Box02.GetAxisY());
	C[1].z = D3DXVec3Dot(&Box01.GetAxisY(), &Box02.GetAxisZ());
	AD.y = D3DXVec3Dot(&Box01.GetAxisY(), &D);
	absC[1].x = fabsf(C[1].x);
	absC[1].y = fabsf(C[1].y);
	absC[1].z = fabsf(C[1].z);
	R = fabsf(AD.y);
	R1 = Box01.Radius.x * absC[1].x + Box01.Radius.y * absC[1].y + Box01.Radius.z * absC[1].z;
	R01 = Box01.Radius.y + R1;
	if (R > R01)return 0;

	//A2
	C[2].x = D3DXVec3Dot(&Box01.GetAxisZ(), &Box02.GetAxisX());
	C[2].y = D3DXVec3Dot(&Box01.GetAxisZ(), &Box02.GetAxisY());
	C[2].z = D3DXVec3Dot(&Box01.GetAxisZ(), &Box02.GetAxisZ());
	AD.z = D3DXVec3Dot(&Box01.GetAxisZ(), &D);
	absC[2].x = fabsf(C[2].x);
	absC[2].y = fabsf(C[2].y);
	absC[2].z = fabsf(C[2].z);
	R = fabsf(AD.z);
	R1 = Box01.Radius.x * absC[2].x + Box01.Radius.y * absC[2].y + Box01.Radius.z * absC[2].z;
	R01 = Box01.Radius.z + R1;
	if (R > R01)return 0;

	//B0
	R = fabsf(D3DXVec3Dot(&Box01.GetAxisX(), &D));
	R0 = Box01.Radius.x * absC[0].x + Box01.Radius.y * absC[1].x + Box01.Radius.z * absC[2].x;
	R01 = R0 + Box01.Radius.x;
	if (R > R01)return 0;

	//B1
	R = fabsf(D3DXVec3Dot(&Box01.GetAxisY(), &D));
	R0 = Box01.Radius.x * absC[0].z + Box01.Radius.y * absC[1].y + Box01.Radius.z * absC[2].y;
	R01 = R0 + Box01.Radius.y;
	if (R > R01)return 0;

	//B2
	R = fabsf(D3DXVec3Dot(&Box01.GetAxisZ(), &D));
	R0 = Box01.Radius.x * absC[0].z + Box01.Radius.y * absC[1].z + Box01.Radius.z * absC[2].z;
	R01 = R0 + Box01.Radius.z;
	if (R > R01)return 0;

	//A0xB0
	R = fabsf(AD.z * C[1].x - AD.y * C[2].x);
	R0 = Box01.Radius.y * absC[2].x + Box01.Radius.z * absC[1].x;
	R1 = Box01.Radius.y * absC[0].z + Box01.Radius.z * absC[0].y;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A0xB1
	R = fabsf(AD.z * C[1].y - AD.y * C[2].y);
	R0 = Box01.Radius.y * absC[2].y + Box01.Radius.z * absC[1].y;
	R1 = Box01.Radius.x * absC[0].z + Box01.Radius.z * absC[0].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A0xB2
	R = fabs(AD.z * C[1].z - AD.y * C[2].z);
	R0 = Box01.Radius.y * absC[2].z + Box01.Radius.z * absC[1].y;
	R1 = Box01.Radius.x * absC[0].y + Box01.Radius.y * absC[0].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A1xB0
	R = fabs(AD.x * C[2].x - AD.x * C[0].x);
	R0 = Box01.Radius.x * absC[2].x + Box01.Radius.z * absC[0].x;
	R1 = Box01.Radius.y * absC[1].z + Box01.Radius.z * absC[1].y;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A1xB1
	R = fabs(AD.x * C[2].y - AD.z * C[0].y);
	R0 = Box01.Radius.x * absC[2].y + Box01.Radius.z * absC[0].y;
	R1 = Box01.Radius.x * absC[1].z + Box01.Radius.z * absC[1].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A1xB2
	R = fabsf(AD.x * C[2].z - AD.z * C[0].z);
	R0 = Box01.Radius.x * absC[2].z + Box01.Radius.z * absC[0].z;
	R1 = Box01.Radius.x * absC[1].y + Box01.Radius.y * absC[1].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A2xB0
	R =  fabsf(AD.y * C[0].x - AD.x * C[1].x);
	R0 = Box01.Radius.x * absC[1].x + Box01.Radius.y * absC[0].x;
	R1 = Box01.Radius.y * absC[2].z + Box01.Radius.z * absC[2].y;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A2xB1
	R = fabsf(AD.y * C[0].y - AD.x * C[1].y);
	R0 = Box01.Radius.x * absC[1].y + Box01.Radius.y * absC[0].y;
	R1 = Box01.Radius.x * absC[2].z + Box01.Radius.z * absC[2].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A2xB2
	R = fabsf(AD.y * C[0].z - AD.x * C[1].z);
	R0 = Box01.Radius.x * absC[1].z + Box01.Radius.y * absC[0].z;
	R1 = Box01.Radius.x * absC[2].y + Box01.Radius.y * absC[2].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	return 1;

}

bool CPhysic::CheckCollision( Box _Box01, Vector3 _fRot01, const Sphere & _Sphere)
{
	_Box01.Rotation = _fRot01;
	//Vector3 local = Vector3(0, 0, 0);

	//local.x = D3DXVec3Dot(&_Sphere.Center, &Vector3(_Box01.GetAxisX()));
	//local.y = D3DXVec3Dot(&_Sphere.Center, &Vector3(_Box01.GetAxisY()));
	//local.z = D3DXVec3Dot(&_Sphere.Center, &Vector3(_Box01.GetAxisZ()));


	D3DXVECTOR3 SpCenter = _Sphere.Center - _Box01.Center;

	D3DXMATRIX matRotate, matResult, matInverse;
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixIdentity(&matResult);
	D3DXMatrixIdentity(&matInverse);

	// obb가 회전했을때 연산을 마친 행렬값을 가지고 있는 부분입니다.
	Matrix matRot[3];
	
	D3DXMatrixRotationX(&matRot[0], D3DXToRadian(_Box01.Rotation.x));
	D3DXMatrixRotationY(&matRot[1], D3DXToRadian(_Box01.Rotation.y));
	D3DXMatrixRotationZ(&matRot[2], D3DXToRadian(_Box01.Rotation.z));

	matRotate = matRot[0] * matRot[1] * matRot[2];
	matRotate._41 = _Box01.Center.x;
	matRotate._42 = _Box01.Center.y;
	matRotate._43 = _Box01.Center.z;

	D3DXMatrixMultiply(&matResult, &matResult, &matRotate);
	D3DXMatrixInverse(&matInverse, NULL, &matResult);
	D3DXMatrixTranspose(&matInverse, &matInverse); // DX는 Y축이 반대이므로 투영하기전에 Transpos를 해줘야한다.
	D3DXVec3TransformCoord(&SpCenter, &SpCenter, &matInverse);
	
	Vector3 vBoxPoint; // 박스 위의 점 중 구와 가장 가까운 점

	if (_Sphere.Center.x < _Box01.Center.x - _Box01.Radius.x / 2.0f)

		vBoxPoint.x = _Box01.Center.x - _Box01.Radius.x / 2.0f;

	else if (_Sphere.Center.x > _Box01.Center.x + _Box01.Radius.x / 2.0f)
		vBoxPoint.x  = _Box01.Center.x + _Box01.Radius.x / 2.0f;
	else
		vBoxPoint.x = _Sphere.Center.x;

	if (_Sphere.Center.y < _Box01.Center.y - _Box01.Radius.y / 2.0f)

		vBoxPoint.y = _Box01.Center.y - _Box01.Radius.y / 2.0f;

	else if (_Sphere.Center.y > _Box01.Center.y + _Box01.Radius.y / 2.0f)
		vBoxPoint.y = _Box01.Center.y + _Box01.Radius.y / 2.0f;
	else
		vBoxPoint.y = _Sphere.Center.y;

	if (_Sphere.Center.z < _Box01.Center.z - _Box01.Radius.z / 2.0f)

		vBoxPoint.z = _Box01.Center.z - _Box01.Radius.z / 2.0f;

	else if (_Sphere.Center.z > _Box01.Center.z + _Box01.Radius.z / 2.0f)
		vBoxPoint.z = _Box01.Center.z + _Box01.Radius.z / 2.0f;
	else
		vBoxPoint.z = _Sphere.Center.z;

	Vector3 dist = _Sphere.Center - vBoxPoint;

	float collisionDistance = D3DXVec3Length(&dist) - _Sphere.Radius;

	if (collisionDistance < 0.f) return false;
	else return true;
}

bool CPhysic::CheckCollision(Sphere _Sphere01, Sphere _Sphere02)
{
	float fDistance;
	D3DXVECTOR3 vDiff;

	vDiff = _Sphere02.Center - _Sphere01.Center;
	fDistance = D3DXVec3Length(&vDiff);

	if (fDistance <= (_Sphere01.Radius + _Sphere02.Radius))
		return true;  // 충돌
	return false; // 비 충돌
}

bool CPhysic::CheckCollision(CRay _Ray, Sphere _Sphere, Vector3& _vIntersect)
{
	//Matrix matPos, matPosInv;

	//D3DXMatrixTranslation(&matPos, _Sphere.Center.x, _Sphere.Center.y, _Sphere.Center.z);
	//D3DXMatrixInverse(&matPosInv, NULL, &matPos);

	//D3DXVec3TransformCoord(&_Ray.m_vPos, &_Ray.m_vPos, &matPosInv);
	//D3DXVec3TransformNormal(&_Ray.m_vDir, &_Ray.m_vDir, &matPosInv);

	//float b = D3DXVec3Dot(&_Ray.m_vPos, &_Ray.m_vDir);
	//float a = D3DXVec3Dot(&_Ray.m_vDir, &_Ray.m_vDir);
	//float c = (_Ray.m_vPos.x * _Ray.m_vPos.x + _Ray.m_vPos.y * _Ray.m_vPos.y + _Ray.m_vPos.z * _Ray.m_vPos.z) - (_Sphere.Radius * _Sphere.Radius);


	//if (b*b - a * c >= 0) return true;
	
	return false;
	float distance;
	Vector3 intersection;

	Vector3 l = _Sphere.Center - _Ray.m_vPos;
	double s = D3DXVec3Dot(&l, &_Ray.m_vDir);
	double l2 = D3DXVec3Dot(&l, &l);
	double r2 = pow(_Sphere.Radius, 2);

	if (s < 0 && l2 > r2) {
		return false;                       // 광선이 구의 반대 방향을 향하거나 구를 지나친 경우
	}
	double m2 = l2 - pow(s, 2);
	if (m2 > r2) {
		return false;                      // 광선이 구를 비껴가는 경우
	}
	double q = sqrt(r2 - m2);
	// 두 개의 교차점 중 어느것을 구하는가?   
	if (l2 > r2) {
		distance = s - q;
	}
	else {
		distance = s + q;
	}
	intersection = _Ray.m_vPos + distance * _Ray.m_vDir;

	if(distance > _Ray.m_fMaxDistance && _Ray.m_fMaxDistance != -1.f)
	return true;

}

bool CPhysic::CheckCollision(CRay _Ray, Box _Box, Vector3 _vRotation, Vector3& _vIntersect)
{
	_Box.Rotation = _vRotation;
	Box box = _Box;
	CRay ray = _Ray;
	float u, v, t;
	Vector3 vt[8];
	vt[0] = box.Center + Vector3(-box.Radius.x, box.Radius.y, box.Radius.z);
	vt[1] = box.Center + Vector3(box.Radius.x, box.Radius.y, box.Radius.z);
	vt[2] = box.Center + Vector3(box.Radius.x, box.Radius.y, -box.Radius.z);
	vt[3] = box.Center + Vector3(-box.Radius.x, box.Radius.y, -box.Radius.z);

	vt[4] = box.Center + Vector3(-box.Radius.x, -box.Radius.y, box.Radius.z);
	vt[5] = box.Center + Vector3(box.Radius.x, -box.Radius.y, box.Radius.z);
	vt[6] = box.Center + Vector3(box.Radius.x, -box.Radius.y, -box.Radius.z);
	vt[7] = box.Center + Vector3(-box.Radius.x, -box.Radius.y, -box.Radius.z);

	bool col[16];
	col[0] = D3DXIntersectTri(&vt[1], &vt[2], &vt[5], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[0] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;
	}

	col[5] = D3DXIntersectTri(&vt[6], &vt[5], &vt[2], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[5] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}

	col[6] = D3DXIntersectTri(&vt[3], &vt[2], &vt[7], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[6] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[7] = D3DXIntersectTri(&vt[2], &vt[7], &vt[6], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[7] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[1] = D3DXIntersectTri(&vt[1], &vt[4], &vt[5], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[1] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[8] = D3DXIntersectTri(&vt[0], &vt[1], &vt[4], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[8] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[9] = D3DXIntersectTri(&vt[4], &vt[7], &vt[6], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[9] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[10] = D3DXIntersectTri(&vt[4], &vt[7], &vt[6], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[10] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[11] = D3DXIntersectTri(&vt[4], &vt[5], &vt[6], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[11] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[12] = D3DXIntersectTri(&vt[3], &vt[4], &vt[7], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[12] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;
		
	}
	col[13] = D3DXIntersectTri(&vt[0], &vt[3], &vt[4], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[13] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[14] = D3DXIntersectTri(&vt[0], &vt[1], &vt[2], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[14] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;

	}
	col[15] = D3DXIntersectTri(&vt[0], &vt[3], &vt[2], &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t);
	if (col[15] == true)
	{
		_vIntersect = ray.m_vPos + ray.m_vDir * t;
		return true;
	}
	/*if (D3DXIntersectTri(&Vector3(box.Center.x + box.Radius.x, box.Radius, 10000), &Vector3(10000, 0, 10000), &Vector3(-10000, 0, -10000), &ray.m_vPos, &ray.m_vDir,
		&u, &v, &t) || D3DXIntersectTri(&Vector3(10000, 0, 10000), &Vector3(10000, 0, -10000), &Vector3(-10000, 0, -10000), &m_Ray._origin, &m_Ray._direction,
			&u, &v, &t))
	{

	}*/
	_vIntersect = Vector3(0, 0, 0);
	return false;
}

CRaycastHit CPhysic::RayCast(CRay _Ray)
{
	bool IsCollision;
	CRaycastHit Hit;
		Vector3 Point;
	for (auto iter : OBJECT.m_listCollider3D)
	{
		if (iter->GetColliderType() == Collider3D_Type::OBB)
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CBoxCollider3D>()->GetBox(), Point);
		}

		else
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CSphereCollider3D>()->GetSphere(), Point);

		}
		if (IsCollision == true)
		{
			if (Hit.m_fDistance > D3DXVec3Length(&(_Ray.m_vPos - Point)) && _Ray.m_fMaxDistance >= D3DXVec3Length(&(_Ray.m_vPos - Point)))
			{
				Hit.m_fDistance = D3DXVec3Length(&(_Ray.m_vPos - Point));
				Hit.m_pCollider = iter;
				Hit.m_pHitObject = iter->m_pObject;
				Hit.m_vHitPoint = Point;
			}
		}
	}
	return Hit;
}

CRaycastHit CPhysic::RayCast(CRay _Ray, ObjectTag _Tag)
{
	bool IsCollision;
	CRaycastHit Hit;
	Hit.m_pCollider = nullptr;
	Hit.m_pHitObject = nullptr;
	Hit.m_fDistance = 1000000000;
	Vector3 Point = Vector3(0,0,0);
	for (auto iter : OBJECT.m_listCollider3D)
	{
		if (iter->m_pObject->GetObjectTag() != _Tag)continue;
		if (iter->GetColliderType() == Collider3D_Type::OBB)
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CBoxCollider3D>()->GetBox(),Vector3(0,0,0), Point);
		}

		else
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CSphereCollider3D>()->GetSphere(), Point);

		}

		if (IsCollision == true)
		{
			if (Hit.m_fDistance > D3DXVec3Length(&(_Ray.m_vPos - Point)) && _Ray.m_fMaxDistance >= D3DXVec3Length(&(_Ray.m_vPos - Point)))
			{ 
				Hit.m_fDistance = D3DXVec3Length(&(_Ray.m_vPos - Point));
				Hit.m_pCollider = iter;
				Hit.m_pHitObject = iter->m_pObject;
				Hit.m_vHitPoint = iter->Transform->GetPosition();
			}
		}
	}
	return Hit;
}

list<CRaycastHit> CPhysic::RayCastAll(CRay _Ray)
{
	bool IsCollision;
	list<CRaycastHit> listHit;
	Vector3 Point;
	for (auto iter : OBJECT.m_listCollider3D)
	{
		if (iter->GetColliderType() == Collider3D_Type::OBB)
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CBoxCollider3D>()->GetBox(), Point);
		}

		else
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CSphereCollider3D>()->GetSphere(), Point);

		}
		if (IsCollision == true )
		{
			if (_Ray.m_fMaxDistance >= D3DXVec3Length(&(_Ray.m_vPos - Point)))
			{
				CRaycastHit Hit;
				Hit.m_fDistance = D3DXVec3Length(&(_Ray.m_vPos - Point));
				Hit.m_pCollider = iter;
				Hit.m_pHitObject = iter->m_pObject;
				Hit.m_vHitPoint = Point;
				listHit.push_back(Hit);
			}
		}
	}
	return listHit;
}

list<CRaycastHit> CPhysic::RayCastAll(CRay _Ray, ObjectTag _Tag)
{
	bool IsCollision;
	list<CRaycastHit> listHit;
	Vector3 Point;
	for (auto iter : OBJECT.m_listCollider3D)
	{
		if (iter->m_pObject->GetObjectTag() != _Tag)continue;
		
		if (iter->GetColliderType() == Collider3D_Type::OBB)
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CBoxCollider3D>()->GetBox(),iter->Transform->GetRotation(), Point);
		}

		else
		{
			IsCollision = this->CheckCollision(_Ray, iter->m_pObject->GetComponent<CSphereCollider3D>()->GetSphere(), Point);

		}
		if (IsCollision == true)
		{
			if (_Ray.m_fMaxDistance >= D3DXVec3Length(&(_Ray.m_vPos - Point)))
			{
				CRaycastHit Hit;
				Hit.m_fDistance = D3DXVec3Length(&(_Ray.m_vPos - Point));
				Hit.m_pCollider = iter;
				Hit.m_pHitObject = iter->m_pObject;
				Hit.m_vHitPoint = Point;
				listHit.push_back(Hit);
			}
		}
	}
	return listHit;
}
