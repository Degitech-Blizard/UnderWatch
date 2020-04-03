#include "DXUT.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CBulletEffect.h"
#include "CHealMachine.h"
#include "CPlayerAim.h"
#include "CRocketBullet.h"
#include "CEnemyBase.h"
CPlayer::CPlayer()
{

}


CPlayer::~CPlayer()
{
	 
}

void CPlayer::Hit(float _fDamage,bool _bKill)
{
	SOUND.Play("SND_ENEMY_HIT", FALSE);

	if (!this->m_bUltimateEnable)
	{
		this->m_fCurUltimate += _fDamage * 12.f;
		if (m_fCurUltimate > m_fMaxUltimate) m_fCurUltimate = m_fMaxUltimate;
	}
	if (_bKill)
	{
		SOUND.Play("SND_ENEMY_KILL", FALSE);

		OBJECT.FindObjectWithName("Aim")->GetComponent<CPlayerAim>()->Kill();

	}
	else	OBJECT.FindObjectWithName("Aim")->GetComponent<CPlayerAim>()->Hit();
	
}

void CPlayer::Awake()
{
	this->AddComponent<CBoxCollider3D>()->SetBox(Box(this->Transform->GetPosition(),Vector3(32,128,32)));
	this->AddComponent<CRigidBody3D>();
	m_vAxis[Axis::Foward] = Vector3(0, 0, 1);
	m_vAxis[Axis::Backward] = Vector3(0, 0, -1);
	m_vAxis[Axis::Right] = Vector3(1, 0, 0);
	m_vAxis[Axis::Left] = Vector3(-1, 0, 0);
	m_vAxis[Axis::Up] = Vector3(0, 1, 0);
	m_vAxis[Axis::Down] = Vector3(0, -1, 0);
	m_vCamDir = Vector3(0, 0, 0);
	this->Transform->Translation(800, 300, 800);

	CAMERA.SetLookAt(Vector3(0, 0, 1));
	m_fTime = 0.25f;


}
void CPlayer::Start()
{
	m_pPlayerSkill = OBJECT.FindObjectWithName("PlayerSkill")->GetComponent<CPlayerSkill>();
	m_pGun = OBJECT.FindObjectWithName("Gun")->GetComponent<CGun>();
}
void CPlayer::Update()
{
	m_fTime += DeltaTime;
	Vector2 NormalDelta = INPUT.m_vDeltaCursor;

	CAMERA.SetRotation(	Vector3(
			CAMERA.GetRotation().x + (NormalDelta.y * this->m_fSensitivity  * DeltaTime), 
			CAMERA.GetRotation().y + (NormalDelta.x * this->m_fSensitivity  * DeltaTime), 
			CAMERA.GetRotation().z));

	if (CAMERA.GetTargetRotation().x > 90)
	{
		CAMERA.SetRotation(Vector3(
			90,
			CAMERA.GetRotation().y,
			CAMERA.GetRotation().z));
	}
	if (CAMERA.GetTargetRotation().x < -90)
	{
		CAMERA.SetRotation(Vector3(
			-90,
			CAMERA.GetRotation().y,
			CAMERA.GetRotation().z));
	}


	this->Transform->Rotate(
		0, 
		NormalDelta.x * this->m_fSensitivity  * DeltaTime, 0);

	Vector3 vPlayerPos = this->Transform->GetPosition();

	Matrix CamRotY, CamRotX, CamRot;

	D3DXMatrixRotationY(&CamRotY, D3DXToRadian(CAMERA.GetRotation().y));
	D3DXMatrixRotationX(&CamRotX, D3DXToRadian(CAMERA.GetRotation().x));

	CamRot = CamRotY; //* CamRotX;

	D3DXVec3TransformNormal(&m_vAxis[Axis::Foward], &Vector3(0, 0, 1), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Backward], &Vector3(0, 0, -1), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Right], &Vector3(1, 0, 0), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Left], &Vector3(-1, 0, 0), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Up], &Vector3(0, 1, 0), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Down], &Vector3(0, -1, 0), &CamRot);


	if (INPUT.KeyDown(VK_SPACE) && this->GetComponent<CRigidBody3D>()->GetVelocity().y == 0.f && this->Transform->GetComponent<CRigidBody3D>()->GetIsKinematic() == true)
	{

			this->Transform->GetComponent<CRigidBody3D>()->SetIsKinematic(false);
			this->Transform->Translation(0, 1, 0);
			this->Transform->GetComponent<CRigidBody3D>()->SetVelocitiy(Vector3(0, 2000, 0));
	}
	Vector3 offset = Vector3(-15, -15, 12);

	Matrix matRotX, matRotY, matRot;
	D3DXMatrixRotationZ(&matRotX, D3DXToRadian(CAMERA.GetRotation().x));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(CAMERA.GetRotation().y + 90));

	matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&offset, &offset, &matRot);
	if (INPUT.KeyDown('Q'))
	{
		if (this->m_fCurUltimate >= this->m_fMaxUltimate)
		{
		SOUND.Play("SND_PLAYER_ULTIMATE_VOICE", FALSE);
		SOUND.Play("SND_PLAYER_Q", FALSE);
		this->m_fCurUltimate = 0.f;
			this->m_fUltimateDuraction = 12.f;
			this->m_bUltimateEnable = true;
		}
	}
	if (m_bUltimateEnable)
	{
		this->m_fUltimateDuraction -= DeltaTime;
		if (m_fUltimateDuraction <= 0.f)
		{
			this->m_fUltimateDuraction = 0.f;
			this->m_bUltimateEnable = false;
		}

	}
	if (m_fWalkTime > 0.5)
	{
		m_fWalkTime = 0.f;
		SOUND.Play("SND_PLAYER_STEP", FALSE);
	}
	bool isMove = false;
	if (INPUT.KeyPress(VK_UP))
	{
		m_fSensitivity += DeltaTime * 10;

	}
	if (INPUT.KeyPress(VK_DOWN))
	{
		m_fSensitivity -= DeltaTime * 10;
	}
	Vector3 LastPos = this->Transform->GetPosition();
	if (INPUT.KeyPress('A'))
	{
		isMove = true;
		m_fWalkTime += DeltaTime;
		this->Transform->Translation(this->m_vAxis[Axis::Left] * DeltaTime * m_fMoveSpeed);
		this->Transform->SetScale(Vector3(1, 1, -1));

	}
	
	  if (INPUT.KeyPress('D'))
	{
		isMove = true;
		m_fWalkTime += DeltaTime;
		this->Transform->Translation(this->m_vAxis[Axis::Right] * DeltaTime * m_fMoveSpeed);
		this->Transform->SetScale(Vector3(1, 1, -1));

	}

	 if (INPUT.KeyPress('W'))
	{
		isMove = true;
		m_fWalkTime += DeltaTime;
		this->Transform->Translation(m_vAxis[Axis::Foward] * m_fMoveSpeed * DeltaTime);
		this->Transform->SetScale(Vector3(1, 1, -1));

	}
	 if (INPUT.KeyPress('S'))
	{
		isMove = true;
		m_fWalkTime += DeltaTime;
		this->Transform->Translation(m_vAxis[Axis::Backward] * m_fMoveSpeed * DeltaTime);
		this->Transform->SetScale(Vector3(1, 1, 1));

	}
	 if (isMove == false)
	{
		m_fWalkTime = 0.f;
		m_fDegree = 0;
		m_fOffset = 0;
		CAMERA.SetPos(Vector3(this->Transform->GetPosition().x, this->Transform->GetPosition().y + 128, this->Transform->GetPosition().z) + Vector3(0, m_fOffset * 10, 0));
		m_pGun->Transform->SetPosition(this->Transform->GetPosition() + offset + Vector3(0, 128, 0));
	}
	 else
	 {
		 m_fDegree += 900 * DeltaTime;
		 m_fOffset = sinf(D3DXToRadian(m_fDegree));


		 CAMERA.SetPos(Vector3(this->Transform->GetPosition().x, this->Transform->GetPosition().y + 128, this->Transform->GetPosition().z) + Vector3(0, m_fOffset * 2, 0));
		 m_pGun->Transform->SetPosition(this->Transform->GetPosition() + offset + Vector3(0, 128, 0));

	 }

	if (INPUT.KeyUp('E') && m_pPlayerSkill->CanUseSkill02())
	{
		SOUND.Play("SND_PLAYER_E", FALSE);
		m_pPlayerSkill->UseSkill02(15.f);
		CObject * pHealMachine = OBJECT.AddObject();
		pHealMachine->AddComponent<CHealMachine>();
		pHealMachine->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0, 0, 0));
		pHealMachine->GetComponent<CHealMachine>()->SetDuraction(8.f);
		pHealMachine->GetComponent<CHealMachine>()->SetHealPerSec(30.f);
		pHealMachine->GetComponent<CHealMachine>()->SetRange(10.f);
	}
	if (INPUT.KeyDown(VK_RBUTTON) && m_pPlayerSkill->CanUseSkill03())
	{
		SOUND.Play("SND_PLAYER_RM", FALSE);
		m_pPlayerSkill->UseSkill03(6.f);
		auto Bullet = OBJECT.AddObject("Bullet", Tag::PlayerBullet);
		CRay ray = CAMERA.RayCastAtScreen(WinSize / 2.f);
		Bullet->Transform->SetPosition(this->Transform->GetPosition());


		CAMERA.SetRotation(Vector3(
			CAMERA.GetTargetRotation().x - 1.5f,
			CAMERA.GetTargetRotation().y,
			CAMERA.GetTargetRotation().z));
		Bullet->Transform->SetPosition(ray.m_vPos + ray.m_vDir);

		Bullet->AddComponent<CRocketBullet>()->m_vDir = ray.m_vDir;
		Bullet->Transform->SetScale(Vector3(0.125, 0.125, 0.125));

		//Matrix matX, matY, matRot;
		float MoonAngle_x = D3DXToDegree(acos(ray.m_vDir.y));
		float MoonAngle_y = D3DXToDegree(atan2f(ray.m_vDir.z, -ray.m_vDir.x));
		Bullet->Transform->SetRotation(Vector3(MoonAngle_x + 90, MoonAngle_y + 90, 0.f));
		//D3DXMatrixRotationX(&matX, D3DXToRadian(D3DXToDegree(MoonAngle_x) - 90));
		//D3DXMatrixRotationY(&matY, D3DXToRadian(D3DXToDegree(MoonAngle_y) - 90));
		//Se
		

		auto FireEffect = OBJECT.AddObject();
		FireEffect->AddComponent<CBulletEffect>();
		FireEffect->Transform->SetPosition(m_pGun->Transform->GetPosition() + ray.m_vDir * 80 + this->m_vAxis[Axis::Up] * 10);
		FireEffect->Transform->SetScale(Vector3(0.1f, 0.1f, 1.f));
	}
	else if (INPUT.KeyPress(VK_LBUTTON))
	{
		if (m_fTime > 0.1f)
		{
		
			m_fTime = 0.f;
			m_IsFire = true;
			SOUND.Play("SND_PLAYER_FIRE", FALSE);
			CAMERA.ForceRebound(6.f);

			auto Bullet = OBJECT.AddObject("Bullet", Tag::PlayerBullet);
			CRay ray = CAMERA.RayCastAtScreen(WinSize / 2.f);

			Bullet->Transform->SetPosition(this->Transform->GetPosition() - Vector3(0,100,0));



			Bullet->Transform->SetPosition(ray.m_vPos + (ray.m_vDir *4) - Vector3(0, 16, 0) + m_vAxis[Axis::Right] * 10);

			Bullet->AddComponent<CBullet>()->m_vDir = ray.m_vDir;
			Bullet->AddComponent<CBullet>()->m_fSpeed = 150000.f;

			Bullet->Transform->SetScale(Vector3(0.125, 0.125, 0.125));
			if (this->m_bUltimateEnable)
			{
				list<CObject*>listgameobject = OBJECT.GetCotainObject(this->Transform->GetPosition(), 999999, Tag::Enemy);
				
				float distance = 99999990.f;
				
				if (listgameobject.empty() == false)
				{
					bool isFirst = true;
					CObject * pObject;
					for (auto iter : listgameobject)
					{
						if (isFirst)
						{
							pObject = iter;
							isFirst = false;
						}
						else
						{
							if (D3DXVec3Length(&(this->Transform->GetPosition() - pObject->Transform->GetPosition()))
								> D3DXVec3Length(&(this->Transform->GetPosition() - iter->Transform->GetPosition())))
							{
								pObject = iter;
							}
							else
							{
								continue;
							}
						}

					}

					Bullet->Transform->SetPosition(pObject->Transform->GetPosition() - (ray.m_vDir * DeltaTime * 6000));
			//		Bullet->AddComponent<CBullet>()->m_vDir = pObject->Transform->GetPosition() - (ray.m_vPos + ray.m_vDir);
		//			D3DXVec3Normalize(&Bullet->AddComponent<CBullet>()->m_vDir, &Bullet->AddComponent<CBullet>()->m_vDir);
				}
			}
			
			float MoonAngle_x = D3DXToDegree(acos(ray.m_vDir.y));
			float MoonAngle_y = D3DXToDegree(atan2f(ray.m_vDir.z, -ray.m_vDir.x));
			Bullet->Transform->SetRotation(Vector3(MoonAngle_x , MoonAngle_y, 0.f));
			

			auto FireEffect = OBJECT.AddObject();
			FireEffect->AddComponent<CBulletEffect>();
			FireEffect->Transform->SetPosition(m_pGun->Transform->GetPosition()  + ray.m_vDir * 80 + this->m_vAxis[Axis::Up] * 10);
			FireEffect->Transform->SetScale(Vector3(0.1f, 0.1f, 1.f));
		}
	}
	else
	{
		if (m_IsFire == true)
		{
			//¹Ýµ¿
		}
		m_IsFire = false;
	}



}

void CPlayer::LateUpdate()
{
	if (this->m_fCurHp <= 0.f)
	{
		SCENE.ChangeScene("S_GAMEOVER");
	}
}

void CPlayer::OnDestroy()
{
}

void CPlayer::OnRender()
{
}

void CPlayer::OnEnable()
{
}

void CPlayer::OnDisable()
{
}


void CPlayer::OnCollisionEnter(CObject * _pObject)
{
	if (_pObject->GetObjectTag() == Tag::Collider)
	{
		m_bIsCollision = true;

		Vector3 Dir = this->Transform->GetPosition() - _pObject->Transform->GetPosition();
		D3DXVec3Normalize(&Dir, &Dir);
		Dir.y = 0.f;
		this->Transform->SetPosition(this->Transform->GetPosition() + Dir * 50);
	}
}

void CPlayer::OnCollisionStay(CObject * _pObject)
{

}

void CPlayer::OnCollisionExit(CObject * _pObject)
{
	if (_pObject->GetObjectTag() == Tag::Collider)
	{
		m_bIsCollision = false;
	}
}



