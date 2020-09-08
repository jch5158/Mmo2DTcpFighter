#include "stdafx.h"
#include "CScreenDib.h"
#include "CSpriteDib.h"
#include "CBaseObject.h"
#include "CPlayerObject.h"
#include "CDamageEffect.h"


CDamageEffect::CDamageEffect(void* victimPtr,int usX, int usY,DWORD actionCur)
{
	this->m_iXpos = usX;
	this->m_iYpos = usY;

	this->mVictimPtr = victimPtr;
	this->m_dwActionCur = actionCur;
	this->deleteCheck = false;
	this->m_RenderCheck = false;


	SetSprite(e_SPRITE::eEFFECT_SPARK_01, e_SPRITE::eEFFECT_SPARK_MAX, 3);

	switch (this->m_dwActionCur)
	{
	case KeyList::eACTION_ATTACK1:
	{
		printf_s("attack1\n");
	}

		this->m_EffectTiming = 50;

		break;

	case KeyList::eACTION_ATTACK2:
	
	{
		printf_s("attack2\n");
	}

		this->m_EffectTiming = 100;

		break;

	case KeyList::eACTION_ATTACK3:
	
	{
		printf_s("attack3\n");
	}

		this->m_EffectTiming = 300;

		break;

	default:
	{
		printf_s("default\n");
	}

		this->m_EffectTiming = 300;

		break;
	}

	this->m_TimeSet = timeGetTime();

}

CDamageEffect::~CDamageEffect() {}

void CDamageEffect::Update()
{
	
	if ( this->m_EffectTiming <= timeGetTime() - this->m_TimeSet) {
	
		this->m_RenderCheck = true;

		NextFrame();

		if (this->m_dwSpriteNow == eEFFECT_SPARK_04)
		{
			this->deleteCheck = true;
		}
	}

}

void CDamageEffect::Render()
{
	if (this->m_RenderCheck == false) 
	{
		return;
	}

	BYTE* pDestDib = ScreenDib.GetDibBuffer();

	// 백 버퍼의 가로길이
	int DestWidth = ScreenDib.GetWidth();

	// 백 버퍼의 세로길이
	int DestHeight = ScreenDib.GetHeight();

	// 백 버퍼의 피치
	int pitch = ScreenDib.GetPitch();

	int xPos = 0;
	int yPos = 0;

	if (playerObj == this->mVictimPtr)
	{
		if (this->m_iXpos >= dfRESOLUTION_WIDTH / 2 && this->m_iXpos <= dfRANGE_MOVE_RIGHT - (dfRESOLUTION_WIDTH / 2))
		{
			xPos = dfRESOLUTION_WIDTH / 2;
		}
		else if (this->m_iXpos <= dfRESOLUTION_WIDTH / 2)
		{
			xPos = this->m_iXpos;
		}
		else if (this->m_iXpos >= dfRANGE_MOVE_RIGHT - (dfRESOLUTION_WIDTH / 2))
		{
			xPos = this->m_iXpos - (dfRANGE_MOVE_RIGHT - dfRESOLUTION_WIDTH);
		}

		if (this->m_iYpos >= (dfRESOLUTION_HEIGHT / 2) + 50 && this->m_iYpos <= dfRANGE_MOVE_BOTTOM - ((dfRESOLUTION_HEIGHT / 2) - 50))
		{
			yPos = (dfRESOLUTION_HEIGHT / 2) + 50;
		}
		else if (this->m_iYpos <= (dfRESOLUTION_HEIGHT / 2) + 50)
		{
			yPos = this->m_iYpos;
		}
		else if (this->m_iYpos >= dfRANGE_MOVE_BOTTOM - ((dfRESOLUTION_HEIGHT / 2) - 50))
		{
			yPos = this->m_iYpos - (dfRANGE_MOVE_BOTTOM - dfRESOLUTION_HEIGHT);
		}


		// 현재 실행해야될 스프라이트 인덱스값이다.
		SpriteDib.DrawSprite(this->m_dwSpriteNow, xPos, yPos, pDestDib, DestWidth, DestHeight, pitch);
	}
	else
	{
		if (playerObj->m_iXpos >= this->m_iXpos)
		{
			xPos = (dfRESOLUTION_WIDTH / 2) - (playerObj->m_iXpos - this->m_iXpos);
			if (xPos < 0)
			{
				return;
			}
		}
		else
		{
			xPos = (dfRESOLUTION_WIDTH / 2) + (this->m_iXpos - playerObj->m_iXpos);
			if (xPos > dfRESOLUTION_WIDTH)
			{
				return;
			}
		}

		if (playerObj->m_iYpos >= this->m_iYpos)
		{
			yPos = (dfRESOLUTION_HEIGHT / 2) - (playerObj->m_iYpos - this->m_iYpos) + 50;
			if (yPos < 0)
			{
				return;
			}

		}
		else
		{
			yPos = (dfRESOLUTION_HEIGHT / 2) + (this->m_iYpos - playerObj->m_iYpos) + 50;
			if (yPos > dfRESOLUTION_HEIGHT)
			{
				return;
			}
		}


		// 현재 실행해야될 스프라이트 인덱스값이다.
		SpriteDib.DrawSprite(this->m_dwSpriteNow, xPos, yPos, pDestDib, DestWidth, DestHeight, pitch);
	}

}