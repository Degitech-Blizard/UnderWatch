#include "DXUT.h"
#include "CSkyBox.h"


CSkyBox::CSkyBox(CTexture * top, CTexture* bottom, CTexture* left, CTexture* right, CTexture* front, CTexture* back)
{
	mTex[0] = top->GetD3DXTexture();
	mTex[1] = bottom->GetD3DXTexture();
	mTex[2] = left->GetD3DXTexture();
	mTex[3] = right->GetD3DXTexture();
	mTex[4] = front->GetD3DXTexture();
	mTex[5] = back->GetD3DXTexture();
	//상자 만들기
	// - texture UV까지 생각해보면 정점 24개가 필요하다.


	CVERTEX3D_TEX* pv;

	for (int i = 0; i < 6; i++)
	{
		if (FAILED(g_Device->CreateVertexBuffer(sizeof(CVERTEX3D_TEX) * 4, 0, CVERTEX3D_TEX_FVF, D3DPOOL_DEFAULT, &mVtx[i], NULL))) return;
	}
	//top
	if (FAILED(mVtx[0]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	mVtx[0]->Unlock();
	//bottom
	if (FAILED(mVtx[1]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[1]->Unlock();
	//left
	if (FAILED(mVtx[2]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[2]->Unlock();
	//right
	if (FAILED(mVtx[3]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[3]->Unlock();
	//front
	if (FAILED(mVtx[4]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[4]->Unlock();
	//back
	if (FAILED(mVtx[5]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[5]->Unlock();
	for (int i = 0; i < 6; i++)
	{
		//인덱스 버퍼
		if (FAILED(g_Device->CreateIndexBuffer(sizeof(CINDEX) * 12, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIdx[i], NULL))) return;
	}
	//인덱스 버퍼 초기화
	CINDEX* iv;
	for (int i = 0; i < 6; i++)
	{
		if (FAILED(mIdx[i]->Lock(0, 0, (void**)&iv, 0))) return;
		Set_Idx(iv[0], 0, 1, 2);
		Set_Idx(iv[1], 2, 1, 3);
		mIdx[i]->Unlock();
	}
	return;
}

CSkyBox::~CSkyBox()
{
	for (int i = 0; i < 6; i++)
	{
		SAFE_RELEASE(mVtx[i]);
		SAFE_RELEASE(mIdx[i]);
	}
}

int CSkyBox::FrameMove(float et)
{
	return 0;
}

void CSkyBox::FrameRender()
{
	if (!mVtx || !mIdx) return;

	g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//컬링은 양면
	g_Device->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z버퍼 끄기
	g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);			//조명 끄기

	//스카이 박스 이동.
	D3DXVECTOR3 vPos = CAMERA.GetPos();
	D3DXMATRIX matWrd;	D3DXMatrixIdentity(&matWrd);
	D3DXMatrixTranslation(&matWrd, vPos.x, vPos.y, vPos.z);
	g_Device->SetTransform(D3DTS_WORLD, &matWrd);

	//텍스쳐 UV Address를 설정.
	g_Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//스카이박스 드로우.
	for (int i = 0; i < 6; i++)
	{
		g_Device->SetTexture(0, (mTex[i]) ? mTex[i] : NULL);
		g_Device->SetStreamSource(0, mVtx[i], 0, sizeof(CVERTEX3D_TEX));
		g_Device->SetFVF(CVERTEX3D_TEX_FVF);
		g_Device->SetIndices(mIdx[i]);
		g_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}

	//행렬 초기화.
	D3DXMatrixIdentity(&matWrd);
	g_Device->SetTransform(D3DTS_WORLD, &matWrd);

	g_Device->SetRenderState(D3DRS_ZENABLE, TRUE);			//Z버퍼 켜기
	g_Device->SetRenderState(D3DRS_LIGHTING, TRUE);			//조명 켜기
	g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//컬링 반시계방향
}