#include "Camera.h"
#include "Obj.h"
#include <algorithm>
DEFINTION_SINGLE(CCamera)
CCamera::CCamera() :
	m_pTarget(nullptr)
{
};;

CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget); 
}

void CCamera::SetTarget(CObj* pObj)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pObj;

	if (m_pTarget) {
		m_pTarget->AddRef();
	}
};

bool CCamera::Init(const POSITION& tPos, const RESOLUTION& tRS,
	const RESOLUTION& tWorldRS)
{
	m_tPos = tPos;
	m_tClientRS = tRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);
	return true;
};

void CCamera::Input(float fDeltaTime)
{
	if (!m_pTarget) {
	}
};

void CCamera::Update(/*Test*/HDC hDC,float fDeltaTime)
{
	if (m_pTarget) {
		POSITION tPos = m_pTarget->GetPos();
		POSITION tPivot = m_pTarget->GetPivot();
		_SIZE tSize = m_pTarget->GetSize();

		RESOLUTION _ClientRect = GetClientRect();

		m_tPos.x  = tPos.x - _ClientRect.iW /2 ;
		m_tPos.y = tPos.y - _ClientRect.iH /float(1.5f);

		m_tPos.x   = std::clamp<float>(m_tPos.x  ,0, (m_tWorldRS.iW - (_ClientRect.iW)));
		m_tPos.y  = std::clamp<float>(m_tPos.y , 0, m_tWorldRS.iH - (_ClientRect.iH));

		// 여기서 카메라 좌표를 제한한다.

		// API 카메라 좌표 계산

		//float fL = tPos.x - tPivot.x * tSize.x;
		//float fT = tPos.y - tPivot.y * tSize.y; 
		//float fR = fL + tSize.x;
		//float fB = fT + tSize.y;
		//// TODO :: Debug Field Delete plz 
		////Ellipse(hDC, fL, fT, fR, fB);
		////Rectangle(hDC, tPos.x, tPos.y, tPos.x+3, tPos.y+3);
		//////  
		//float fLeftArea = m_tClientRS.iW * m_tPivot.x;
		//float fRightArea = m_tClientRS.iW - fLeftArea;
		//float fTopArea = m_tClientRS.iH * m_tPivot.y;
		//float fBottomArea = m_tClientRS.iH - fTopArea;
		//// TODO :: Debug Field Delete plz 
		////Ellipse(hDC, fLeftArea, fTopArea, fRightArea, fBottomArea);
		// /// 

		//if (tPos.x <= fLeftArea) {
		//	m_tPos.x= 0.f;
		//}
		//else if (tPos.x >= m_tWorldRS.iW- fRightArea) {
		//	m_tPos.x = m_tWorldRS.iW - m_tClientRS.iW;
		//}
		//else {
		//	m_tPos.x = tPos.x - m_tClientRS.iW * m_tPivot.x;
		//}

		//if (tPos.y <= fTopArea) {
		//	m_tPos.y = 0.f; 
		//}
		//else if (tPos.y >= m_tWorldRS.iH - fBottomArea) {
		//	m_tPos.y = m_tWorldRS.iH - m_tClientRS.iH;
		//}
		//else {
		//	m_tPos.y = tPos.y - m_tClientRS.iH * m_tPivot.y;
		//}
	}
}


