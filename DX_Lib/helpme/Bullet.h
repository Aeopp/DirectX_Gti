#pragma once
#include "MoveObj.h"
class CBullet :
	public CMoveObj
{
private :
	friend class CObj;
	friend class CScene;
	public:
		CBullet();
		virtual ~CBullet() noexcept {};
		CBullet(const CBullet& Obj);
private:
	float m_fDist;
	float m_fLimitDist;
public:
	void SetBulletDistance(float fDist) {
		m_fLimitDist = fDist; 
	}
	virtual bool Init();
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual void Hit(CObj* const pDest, float fDeltaTime);
	virtual CBullet* Clone()override;

	void SetDir(int Dir) & override {
		CMoveObj::SetDir(Dir);
		if (Dir == 1) {
			SetTexture(L"BulletRight", L"Skill_2.bmp");
			SetColorKey(255, 0, 255);
		}
	}
};

