#include "UI.h"
#include "CAnimation.h"
#include "Texture.h"
#include "Colinder.h"
#include "Input.h"
#include "Macro.h"
#include "Mouse.h"
#include <algorithm>
#include "CCore.h"
CUI::CUI():
	CObj()
{
	CollisionTag = L"UI";
}

CUI::CUI(const CUI& ui):
CObj(ui)
{
	CollisionTag = L"UI";

	m_eState=  BS_NONE;
}

CUI::~CUI()
{
}

void CUI::MouseOnEvent(CObj* const Target, float fDeltaTime){
	if (Target->GetTag() == L"Mouse") {
		m_eState = BS_MOUSEON;
		if(bChange==true ) 
		SetImageOffset(m_tSize.x, 0.f);
	}
}
void CUI::MouseReleaseEvent(CObj* const Target, float fDeltaTime) {
	if (Target->GetTag() == L"Mouse") {
		m_eState = BS_NONE;
		if (bChange == true)
		SetImageOffset(0.f, 0.f);
	}
}

void CUI::MouseClickEvent(CObj* const Target, float fDeltaTime)
{
	
}

void CUI::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CUI::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	return 0;
}

int CUI::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);

	if (m_eState != BS_NONE) {
		if (KEYPRESS("MouseLButton")) {
			m_eState = BS_CLICK; 
			if (bChange == true)
			SetImageOffset(m_tSize.x*2.f, 0.f);
		}
	}
	if (m_eState == BS_CLICK && KEYUP("MouseLButton")) {
		m_eState = BS_MOUSEON; SetImageOffset(m_tSize.x , 0.f);
		if (m_bEnableCallback) {
			m_BtnCallBack(fDeltaTime); 

			GET_SINGLE(CInput)->MouseAnimPlay("MouseNormal");
		}
	}

	return 0;
}
void CUI::ClampPos() {
	RESOLUTION WorldRs = GET_SINGLE(CCamera)->GetWorldRS();
	float X = GETRESOLUTION.iW - GetSize().x;
	float Y = GETRESOLUTION.iH - GetSize().y;
	if(X>=0)
	m_tPos.x = std::clamp<float>(m_tPos.x, 0, X);
	if(Y>=0)
	m_tPos.y = std::clamp<float>(m_tPos.y, 0, Y);
}
void CUI::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CUI::Hit(CObj* const Target, float fDeltaTime)
{
	CObj::Hit(Target, fDeltaTime);

	
}

void CUI::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CObj::FirstHitEvent(Target, fDeltaTime);
}

void CUI::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CObj::ReleaseHitEvent(Target, fDeltaTime);
	
}

void CUI::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture) {

		POSITION tImagePos;

		if (m_pAnimation) {
			PANIMATIONCLIP pClip =
				m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS) {
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->GetColorKeyEnable() == true) {
			TransparentBlt(hDC, m_tPos.x, m_tPos.y, m_tSize.x,
				m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
				m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else {
			BitBlt(hDC, m_tPos.x, m_tPos.y,
				m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
				SRCCOPY);
		}
	}

	if (bBorder == true) {
		auto Pos = GetPos();
		auto Size = GetSize();

		MoveToEx(hDC, Pos.x, Pos.y, NULL);
		LineTo(hDC, Pos.x + Size.x, Pos.y);
		LineTo(hDC, Pos.x + Size.x, Pos.y + Size.y);
		LineTo(hDC, Pos.x, Pos.y + Size.y);
		LineTo(hDC, Pos.x, Pos.y);
	}
	
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
}

