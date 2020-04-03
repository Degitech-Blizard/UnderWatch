#include "DXUT.h"
#include "Misc.h"
//------------------------------------------------------------------
//
//------------------------------------------------------------------
void Set_Vtx2D(CVERTEX2D &ct, float x, float y, float z, float rhw, DWORD clr)
{
	ct.x = x;	ct.y = y;	ct.z = z;		ct.rhw = rhw; ct.color = clr;
}
void Set_Vtx3D(CVERTEX3D &ct, float x, float y, float z, DWORD clr)
{
	ct.x = x;	ct.y = y;	ct.z = z;		ct.color = clr;
}
void Set_VtxLT(CVERTEXLT &ct, D3DXVECTOR3 p, D3DXVECTOR3 n)
{
	ct.pos = p; ct.normal = n;
}
void Set_Vtx2D_Tex(CVERTEX2D_TEX &ct, D3DXVECTOR4 p, DWORD clr, float tu, float tv)
{
	ct.pos = p;	ct.color = clr;	ct.tu = tu;	ct.tv = tv;
}
void Set_Vtx3D_Tex(CVERTEX3D_TEX &ct, D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv)
{
	ct.pos = p; ct.normal = n;	ct.tu = tu;	ct.tv = tv;
}
void Set_Idx(CINDEX &ci, WORD _0, WORD _1, WORD _2)
{
	ci._0 = _0; ci._1 = _1;	ci._2 = _2;
}
void Set_IdxLine(CINDEXLINE &ci, WORD _0, WORD _1)
{
	ci._0 = _0; ci._1 = _1;
}
//------------------------------------------------------------------
//정적 버텍스
//------------------------------------------------------------------
HRESULT Create_Vtx2D(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DTEXTURE9 &tex, int x, int y, int w, int h, WCHAR* str, DWORD dif, float tu0, float tv0, float tu1, float tv1)
{
	//텍스쳐 버텍스버퍼 생성.
	if (str && FAILED(D3DXCreateTextureFromFile(g_Device, str, &tex))) return E_FAIL;
	if (FAILED(g_Device->CreateVertexBuffer(sizeof(CVERTEX2D_TEX) * 4, 0, CVERTEX2D_TEX_FVF, D3DPOOL_DEFAULT, &vb, NULL))) return E_FAIL;
	//버텍스 버퍼 초기화.
	CVERTEX2D_TEX* pv;
	if (FAILED(vb->Lock(0, 0, (void**)&pv, 0))) return E_FAIL;
	Set_Vtx2D_Tex(pv[0], D3DXVECTOR4(float(x) - 0.5f, float(y) - 0.5f, 0, 1.0f), dif, tu0, tv0);
	Set_Vtx2D_Tex(pv[1], D3DXVECTOR4(float(x + w) - 0.5f, float(y) - 0.5f, 0, 1.0f), dif, tu1, tv0);
	Set_Vtx2D_Tex(pv[2], D3DXVECTOR4(float(x) - 0.5f, float(y + h) - 0.5f, 0, 1.0f), dif, tu0, tv1);
	Set_Vtx2D_Tex(pv[3], D3DXVECTOR4(float(x + w) - 0.5f, float(y + h) - 0.5f, 0, 1.0f), dif, tu1, tv1);
	vb->Unlock();
	return S_OK;
}
void Render_Vtx2D(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DTEXTURE9 &tex)
{
	if (!vb) return;
	g_Device->SetTexture(0, (tex) ? tex : NULL);
	g_Device->SetStreamSource(0, vb, 0, sizeof(CVERTEX2D_TEX));
	g_Device->SetFVF(CVERTEX2D_TEX_FVF);
	g_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//------------------------------------------------------------------
//정적 인덱스
//------------------------------------------------------------------
HRESULT Create_Vtx2DI(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DINDEXBUFFER9 &ib, LPDIRECT3DTEXTURE9 &tex, int x, int y, int w, int h, WCHAR* str, DWORD dif, float tu0, float tv0, float tu1, float tv1)
{
	//텍스쳐 버텍스버퍼 생성.
	if (str && FAILED(D3DXCreateTextureFromFile(g_Device, str, &tex))) return E_FAIL;
	if (FAILED(g_Device->CreateVertexBuffer(sizeof(CVERTEX2D_TEX) * 4, 0, CVERTEX2D_TEX_FVF, D3DPOOL_DEFAULT, &vb, NULL))) return E_FAIL;
	//버텍스 버퍼 초기화.
	CVERTEX2D_TEX* pv;
	if (FAILED(vb->Lock(0, 0, (void**)&pv, 0))) return E_FAIL;
	Set_Vtx2D_Tex(pv[0], D3DXVECTOR4(float(x) - 0.5f, float(y) - 0.5f, 0, 1.0f), dif, tu0, tv0);
	Set_Vtx2D_Tex(pv[1], D3DXVECTOR4(float(x + w) - 0.5f, float(y) - 0.5f, 0, 1.0f), dif, tu1, tv0);
	Set_Vtx2D_Tex(pv[2], D3DXVECTOR4(float(x) - 0.5f, float(y + h) - 0.5f, 0, 1.0f), dif, tu0, tv1);
	Set_Vtx2D_Tex(pv[3], D3DXVECTOR4(float(x + w) - 0.5f, float(y + h) - 0.5f, 0, 1.0f), dif, tu1, tv1);
	vb->Unlock();
	//인덱스 버퍼
	if (FAILED(g_Device->CreateIndexBuffer(sizeof(CINDEX) * 2, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, NULL))) return E_FAIL;
	//인덱스 버퍼 초기화
	CINDEX* iv;
	if (FAILED(ib->Lock(0, 0, (void**)&iv, 0))) return E_FAIL;
	Set_Idx(iv[0], 0, 1, 2);
	Set_Idx(iv[1], 1, 2, 3);
	ib->Unlock();
	return S_OK;
}
void Render_Vtx2DI(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DINDEXBUFFER9 &ib, LPDIRECT3DTEXTURE9 &tex)
{
	if (!vb || !ib) return;
	g_Device->SetTexture(0, (tex) ? tex : NULL);
	g_Device->SetStreamSource(0, vb, 0, sizeof(CVERTEX2D_TEX));
	g_Device->SetFVF(CVERTEX2D_TEX_FVF);
	g_Device->SetIndices(ib);
	g_Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
}
//------------------------------------------------------------------
// Release
//------------------------------------------------------------------
void Release_Vtx(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DTEXTURE9 &tex)
{
	SAFE_RELEASE(tex);	SAFE_RELEASE(vb);
}
void Release_VtxI(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DINDEXBUFFER9 &ib, LPDIRECT3DTEXTURE9 &tex)
{
	SAFE_RELEASE(tex);	SAFE_RELEASE(ib);	SAFE_RELEASE(vb);
}
//------------------------------------------------------------------
// Draw Text
//------------------------------------------------------------------
WCHAR* ctow(char* val, ...)
{
	static WCHAR wch[MAX_PATH];
	char  ch[MAX_PATH];
	va_list list;
	va_start(list, val);
	vsprintf(ch, val, list);
	va_end(list);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, wch, sizeof(char)*MAX_PATH);
	return wch;
}

void DrawPrintf(WCHAR* str, int x, int y, int w, int h, DWORD flags, DWORD color)
{
	RECT rc;	SetRect(&rc, x, y, x + w, y + h);
}