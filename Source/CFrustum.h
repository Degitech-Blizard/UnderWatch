#pragma once
class CFrustum
{
public:
	CFrustum();
	~CFrustum();

	Vector3 m_vtx[8]; /// 프러스텀을 구성할 정점 8개
	Vector3 m_vPos; /// 현재 카메라의 월드좌표
	D3DXPLANE m_plane[6]; /// 프러스텀을 구성하는 6개의 평면

public:


	/// 카메라(view) * 프로젝션(projection)행렬을 입력받아 6개의 평면을 만든다.
	BOOL Make(Matrix* _matProj, Matrix * _matView);



	/// 한점 v가 프러스텀안에 있으면 TRUE를 반환, 아니면 FALSE를 반환한다.
	BOOL IsIn(D3DXVECTOR3* pv);
	/** 중심(v)와 반지름(radius)를 갖는 경계구(bounding sphere)가 프러스텀안에 있으면
	* TRUE를 반환, 아니면 FALSE를 반환한다.*/
	BOOL IsInSphere(D3DXVECTOR3* pv, float radius);



	/// 현재 카메라의 월드좌표를 얻어준다.
	D3DXVECTOR3* GetPos() { return &m_vPos; }



};

