#include "stdafx.h"
#include "CSpriteDib.h"
#include "CScreenDib.h"
#include "CBaseObject.h"
#include "CPlayerObject.h"




void CBaseObject::SetSprite(DWORD dwSpriteStart, DWORD dwSpriteEnd, DWORD dwFrameDelay)
{
	this->m_dwSpriteStart = dwSpriteStart;
	this->m_dwSpriteEnd = dwSpriteEnd;
	this->m_dwFrameDelay = dwFrameDelay;

	this->m_dwSpriteNow = dwSpriteStart;
	this->m_dwDelayCount = 0;

	// �ش� ��������Ʈ ������ �������� üũ�ϱ� ���� �ܰ�
	// ������ �������� NextFrame() �Լ����� true�� ����ȴ�.
	this->m_bEndFrame = false;
}


int CBaseObject::NextFrame()
{	

	// ������ ���ǿ� ������ ���� ��������Ʈ �������� �����Ѵ�.
	if (this->m_dwDelayCount >= m_dwFrameDelay)
	{
		this->m_dwDelayCount = 0;

		this->m_dwSpriteNow += 1;

		// ������ ��������Ʈ ���۱��� ������ ���
		if (this->m_dwSpriteNow >= this->m_dwSpriteEnd)
		{
			this->m_dwSpriteNow = this->m_dwSpriteStart;
			this->m_bEndFrame = true;
		}
	}


	this->m_dwDelayCount += 1;

	return -1;
}


CBaseObject::CBaseObject() {

}

CBaseObject::~CBaseObject() {}


unsigned int CBaseObject::GetX() 
{
	return this->m_iXpos;
}

unsigned int CBaseObject::GetY() 
{
	return this->m_iYpos;
}


// ĳ������ ��ġ�� �������ִ� �Լ��Դϴ�.
void CBaseObject::SetPosition(int iXpos, int iYpos)
{
	this->m_iXpos = iXpos;

	this->m_iYpos = iYpos;
}

// KeyProcess() ���� �Է°��� �޽��ϴ�.
// � �׼��� ���� ĳ���� ��ü ��������� �������ش�. 
void CBaseObject::ActionInput(DWORD dwAction)
{
	this->m_ActionInput = dwAction;

	return;
}