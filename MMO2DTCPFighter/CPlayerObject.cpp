
#include "stdafx.h"
#include "CScreenDib.h"
#include "CSpriteDib.h"
#include "CBaseObject.h"
#include "CPlayerObject.h"

CPlayerObject* playerObj = new CPlayerObject;

void CPlayerObject::Update()
{
	// ���ǿ� �������� ���� ��������Ʈ ���������� ��ȯ�Ѵ�.
	NextFrame();

	// �׼� ����
	ActionProc();	
}

void CPlayerObject::ActionProc()
{	
	this->actionCheck = false;

	switch (this->m_dwActionCur)
	{
	case KeyList::eACTION_ATTACK1:
	case KeyList::eACTION_ATTACK2:
	case KeyList::eACTION_ATTACK3:
	
		// ���� �׼��� �����ٸ��� ���ĵ� ���°� �ȴ�.
		if (this->m_bEndFrame)
		{
			// ĳ���Ͱ� ���� ������ �������� ���
			if (this->m_dwDirCur == e_PlayerDir::eRight) 
			{
				SetSprite(e_SPRITE::ePLAYER_STAND_R01, e_SPRITE::ePLAYER_STAND_R_MAX, 5);
			}
			// ĳ���Ͱ� ���� ������ ������ ���
			else if (this->m_dwDirCur == e_PlayerDir::eLeft)
			{
				SetSprite(e_SPRITE::ePLAYER_STAND_L01, e_SPRITE::ePLAYER_STAND_L_MAX, 5);
			}
					

			// ���߰� ���� ����
			this->m_ActionInput = KeyList::eACTION_STAND;
			this->m_dwActionCur = KeyList::eACTION_STAND;
			this->actionCheck = true;	
		}	
	
		break;

	// ���� �׼��� �����ٸ� �����̴� �׼��� ���� �� �ִ�. 	
	default:

		InputActionProc();

		break;
	}
}

void CPlayerObject::InputActionProc()
{
	// ���� �׼��� ���� �׼ǿ� �־��ش�.
	DWORD dwActionOld = this->m_dwActionCur;
	
	// BaseObject�� ActionInput() �Լ��� �Է¹��� ���� �־��ش�.
	this->m_dwActionCur = this->m_ActionInput;

	if (dwActionOld != this->m_dwActionCur)
	{
		this->actionCheck = true;
	}

	switch (this->m_dwActionCur)
	{
	case KeyList::eACTION_MOVE_UU:

		if (this->m_iYpos > 57) {
			this->m_iYpos -= 2;
		}

		switch (this->m_dwDirCur)
		{
		case e_PlayerDir::eRight:			
			if (dwActionOld != KeyList::eACTION_STAND)
			{
				if (this->m_bEndFrame == true)
				{
					SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
				}
			}
			else 
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
			}
			break;
		case e_PlayerDir::eLeft:
			if (dwActionOld != KeyList::eACTION_STAND)
			{
				if (this->m_bEndFrame == true)
				{
					SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
				}
			}
			else
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
			}				
			break;
		}

		break;

	case KeyList::eACTION_MOVE_DD:

		if (this->m_iYpos < 467)
		{
			this->m_iYpos += 2;
		}

		switch (this->m_dwDirCur)
		{
		case e_PlayerDir::eRight:	
			if (dwActionOld != KeyList::eACTION_STAND)
			{
				if (this->m_bEndFrame)
				{
					SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
				}
			}
			else
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
			}
			break;
		case e_PlayerDir::eLeft:
			if (dwActionOld != KeyList::eACTION_STAND)
			{
				if (this->m_bEndFrame)
				{
					SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
				}
			}
			else
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
			}

			break;
		}

		break;

	case KeyList::eACTION_MOVE_RR:

		if (this->m_iXpos < 627)
		{
			this->m_iXpos += 3;
		}
		
		if (dwActionOld != KeyList::eACTION_STAND && this->m_dwDirCur == e_PlayerDir::eRight)
		{
			if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
			}
		}
		else 
		{
			SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
		}	

		this->m_dwDirOld = this->m_dwDirCur;
		this->m_dwDirCur = e_PlayerDir::eRight;

		break;

	case KeyList::eACTION_MOVE_LL:

		if (this->m_iXpos > 27)
		{
			this->m_iXpos -= 3;
		}

		if (dwActionOld != KeyList::eACTION_STAND && this->m_dwDirCur == e_PlayerDir::eLeft)
		{
			if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
			}
		}
		else
		{
			SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
		}

		this->m_dwDirOld = this->m_dwDirCur;
		this->m_dwDirCur = e_PlayerDir::eLeft;

		break;

	case KeyList::eACTION_MOVE_LU:

		if (this->m_iXpos > 27 && this->m_iYpos > 67)
		{
			this->m_iXpos -= 3;
			this->m_iYpos -= 2;
		}

		if (dwActionOld != KeyList::eACTION_STAND && this->m_dwDirCur == e_PlayerDir::eLeft)
		{
			if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
			}
		}
		else
		{
			SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
		}

		this->m_dwDirOld = this->m_dwDirCur;
		this->m_dwDirCur = e_PlayerDir::eLeft;

		break;

	case KeyList::eACTION_MOVE_LD:

		if (this->m_iXpos > 27 && this->m_iYpos < 467)
		{
			this->m_iXpos -= 3;
			this->m_iYpos += 2;
		}

		if (dwActionOld != KeyList::eACTION_STAND && this->m_dwDirCur == e_PlayerDir::eLeft)
		{
			if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
			}
		}
		else
		{
			SetSprite(e_SPRITE::ePLAYER_MOVE_L01, e_SPRITE::ePLAYER_MOVE_L_MAX, 4);
		}

		this->m_dwDirOld = this->m_dwDirCur;
		this->m_dwDirCur = e_PlayerDir::eLeft;

		break;

	case KeyList::eACTION_MOVE_RU:

		if (this->m_iXpos < 627 && this->m_iYpos > 67)
		{
			this->m_iYpos -= 2;
			this->m_iXpos += 3;
		}

		if (dwActionOld != KeyList::eACTION_STAND && this->m_dwDirCur == e_PlayerDir::eRight)
		{
			if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
			}
		}
		else
		{
			SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
		}

		this->m_dwDirOld = this->m_dwDirCur;
		this->m_dwDirCur = e_PlayerDir::eRight;

		break;

	case KeyList::eACTION_MOVE_RD:
		if (this->m_iXpos < 627 && this->m_iYpos < 467)
		{
			this->m_iYpos += 2;
			this->m_iXpos += 3;
		}


		if (dwActionOld != KeyList::eACTION_STAND && this->m_dwDirCur == e_PlayerDir::eRight)
		{
			if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
			}
		}
		else
		{
			SetSprite(e_SPRITE::ePLAYER_MOVE_R01, e_SPRITE::ePLAYER_MOVE_R_MAX, 4);
		}

		this->m_dwDirOld = this->m_dwDirCur;
		this->m_dwDirCur = e_PlayerDir::eRight;

		break;

	case KeyList::eACTION_ATTACK1:

		if(this->m_dwDirCur == e_PlayerDir::eRight)
		{
			SetSprite(e_SPRITE::ePLAYER_ATTACK1_R01, e_SPRITE::ePLAYER_ATTACK1_R_MAX, 3);
		}
		else if (this->m_dwDirCur == e_PlayerDir::eLeft)
		{
			SetSprite(e_SPRITE::ePLAYER_ATTACK1_L01, e_SPRITE::ePLAYER_ATTACK1_L_MAX, 3);
		}

			break;

	case KeyList::eACTION_ATTACK2:

		if (this->m_dwDirCur == e_PlayerDir::eRight)
		{
			SetSprite(e_SPRITE::ePLAYER_ATTACK2_R01, e_SPRITE::ePLAYER_ATTACK2_R_MAX, 4);
		}
		else if (this->m_dwDirCur == e_PlayerDir::eLeft)
		{
			SetSprite(e_SPRITE::ePLAYER_ATTACK2_L01, e_SPRITE::ePLAYER_ATTACK2_L_MAX, 4);
		}

			break;

	case KeyList::eACTION_ATTACK3:

		if (this->m_dwDirCur == e_PlayerDir::eRight)
		{
			SetSprite(e_SPRITE::ePLAYER_ATTACK3_R01, e_SPRITE::ePLAYER_ATTACK3_R_MAX, 4);
		}
		else if (this->m_dwDirCur == e_PlayerDir::eLeft)
		{
			SetSprite(e_SPRITE::ePLAYER_ATTACK3_L01, e_SPRITE::ePLAYER_ATTACK3_L_MAX, 4);
		}

			break;
	case KeyList::eACTION_STAND:
	
		switch (this->m_dwDirCur)
		{
		case e_PlayerDir::eRight:

			if (dwActionOld != KeyList::eACTION_STAND)
			{
				SetSprite(e_SPRITE::ePLAYER_STAND_R01, e_SPRITE::ePLAYER_STAND_R_MAX, 5);
			}
			else if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_STAND_R01, e_SPRITE::ePLAYER_STAND_R_MAX, 5);
			}

			break;
		case e_PlayerDir::eLeft:
			
			if (dwActionOld != KeyList::eACTION_STAND)
			{
				SetSprite(e_SPRITE::ePLAYER_STAND_L01, e_SPRITE::ePLAYER_STAND_L_MAX, 5);
			}
			else if (this->m_bEndFrame)
			{
				SetSprite(e_SPRITE::ePLAYER_STAND_L01, e_SPRITE::ePLAYER_STAND_L_MAX, 5);
			}

			break;
		}

		break;
	}
}

void CPlayerObject::Render()
{
	// �� ���۸� �޴´�.
	BYTE* pDestDib = ScreenDib.GetDibBuffer();

	// �� ������ ���α���
	int DestWidth = ScreenDib.GetWidth();

	// �� ������ ���α���
	int DestHeight = ScreenDib.GetHeight();

	// �� ������ ��ġ
	int pitch = ScreenDib.GetPitch();

	// �׸���
	SpriteDib.DrawSprite(eSHADOW, this->m_iXpos, this->m_iYpos, pDestDib, DestWidth, DestHeight, pitch, 100);

	// ���� �����ؾߵ� ��������Ʈ �ε������̴�.
	SpriteDib.DrawSprite(this->m_dwSpriteNow, this->m_iXpos, this->m_iYpos, pDestDib, DestWidth, DestHeight, pitch, 100, (void*)this);

	// ä�� ������
	SpriteDib.DrawSprite(eGUAGE_HP, this->m_iXpos-35, this->m_iYpos+9, pDestDib, DestWidth, DestHeight, pitch,this->m_chHP);
}

// ü���� �������ִ� �Լ��Դϴ�. 
void CPlayerObject::SetHp(BYTE Hp)
{
	this->m_chHP = Hp;
}

CPlayerObject::CPlayerObject()
{
	this->deleteCheck = false;

	this->m_ObjectType = e_ObjType::eType_Player;

	this->m_chHP = 100;

	// Ű���� �Է� �޽���
	this->m_ActionInput = KeyList::eACTION_STAND;

	// ���� �Է¹��� �޽���
	this->m_dwActionCur = KeyList::eACTION_STAND;
	
	// ���� ������ ����Ʈ
	this->m_dwDirCur = e_PlayerDir::eRight;
}

CPlayerObject::~CPlayerObject()
{
}


