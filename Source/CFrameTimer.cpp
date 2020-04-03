#include "DXUT.h"
#include "CFrameTimer.h"

CFrameTimer::CFrameTimer()
{
}

CFrameTimer::~CFrameTimer()
{
}

void CFrameTimer::Update()
{
	DWORD iCurTime = timeGetTime();      //���� �ð�
	float fTimeDelta = (iCurTime - m_iLastTime)*0.001f;        //timeDelta(1�������� �帥 �ð�) 1�ʴ����� �ٲ��ش�.

	m_fTimeElapsed += fTimeDelta;

	m_iFrameCount++;

	if (m_fTimeElapsed >= 1.0f)         //�帥�ð��� 1���̻��̸� ���� �ϰ������� ó��
	{


		m_iFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}
	else
	{
		m_fFPS = (float)m_iFrameCount / m_fTimeElapsed;
		m_fDeltaTime = 1.0f / m_fFPS;
	}


	m_iLastTime = iCurTime;
}