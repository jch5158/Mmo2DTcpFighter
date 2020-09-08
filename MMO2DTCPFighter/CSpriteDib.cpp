
#include "stdafx.h"
#include "CBaseObject.h"
#include "CPlayerObject.h"
#include "CSpriteDib.h"

// �迭 �ִ밳���� �÷�Ű �� ARGB  -> ��Ʋ ��������� ARGB
CSpriteDib SpriteDib = CSpriteDib(e_SPRITE::eSPRITE_MAX, 0x00ffffff);


CSpriteDib::CSpriteDib(int m_iMaxSprite,DWORD dwColorKey) 
{
	// �迭 �ִ� ����
	this->m_iMaxSprite = m_iMaxSprite;

	// ����� �÷� `
	this->m_dwColorKey = dwColorKey;

	// �ִ� �о�� ���� ��ŭ �̸� �Ҵ� �޴´�.
	this->m_stpSprite = new st_SPRITE[m_iMaxSprite];

	// 0 ���� memset~
	memset(m_stpSprite, 0, sizeof(st_SPRITE) * m_iMaxSprite);

	// Ÿ�� �ѹ� ����
	//memset(this->mTileMap, 0, dfMAP_HEIGHT * dfMAP_WIDTH);

	// Ÿ�� �Ӽ� ����
	//memset(this->mTileAttribute, 0, dfMAP_HEIGHT * dfMAP_WIDTH);
}

CSpriteDib::~CSpriteDib() 
{

	for(int iCnt = 0; iCnt < this->m_iMaxSprite; iCnt++)
	{	
		// �迭 ������ŭ ������
		ReleaseStrite(iCnt);
	}


	delete[] this->m_stpSprite;
}

// ��������Ʈ ������ �������� �Լ��Դϴ�.
BOOL CSpriteDib::LoadDibSprite(int iSpriteIndex, const char* szFileName, int iCenterPointX, int iCenterPointY) 
{
	// bmp ���� ������ FILE �����Դϴ�.
	FILE* fp;
	
	// ��ġ �����Դϴ�.
	int iPitch;

	// �̹��� �����Դϴ�.
	int iImageSize;

	BITMAPFILEHEADER stFileHeader;

	// ��Ʈ�� ���� ����Դϴ�.
	BITMAPINFOHEADER stInfoHeader;

	fopen_s(&fp, szFileName, "rb");
	if (fp == nullptr) {
		return false;
	}

	// �ش� ��������Ʈ�� �̹� �����Ͱ� �ִٸ� �̸� ������. Ȥ�� ��������
	ReleaseStrite(iSpriteIndex);

	
	fread(&stFileHeader, sizeof(stFileHeader), 1,fp);

	if (0x4d42 == stFileHeader.bfType) 
	{
		fread(&stInfoHeader, sizeof(stInfoHeader), 1, fp);

		if (32 == stInfoHeader.biBitCount)
		{
			// ���� �̹����� ���� ��ġ��
			iPitch = ((stInfoHeader.biWidth * 4) + 3) & ~3;

			// ��Ʈ�� ���� ����� ���� �� �ش� ������ m_stpSprite �迭 ����ü ����
			this->m_stpSprite[iSpriteIndex].iWidth = stInfoHeader.biWidth;
			this->m_stpSprite[iSpriteIndex].iHeight = stInfoHeader.biHeight;
			this->m_stpSprite[iSpriteIndex].iPitch = iPitch;
			this->m_stpSprite[iSpriteIndex].iCenterPointX = iCenterPointX;
			this->m_stpSprite[iSpriteIndex].iCenterPointY = iCenterPointY;

			// �̹��� ����� ���Ѵ�.
			iImageSize = iPitch * stInfoHeader.biHeight;


			// �̹��� ũ�⸸ŭ �����Ҵ�
			this->m_stpSprite[iSpriteIndex].bytImage = new BYTE[iImageSize];

			// �̹��� ũ�� ��ŭ �����Ҵ�
			BYTE* bytTempBuffer = new BYTE[iImageSize];

			// �̹��� ��������Ʈ �迭�� byImage�� ����Ű�� ������
			BYTE* bytSpriteTemp = this->m_stpSprite[iSpriteIndex].bytImage;

			// �̹����� ������ ���� �������̴�.
			BYTE* bytTurnTemp;

			fread(bytTempBuffer, iImageSize, 1, fp);

			// ���� ������.
			// biHeight -1�� �� ������ ������ ù���� ������ ���� �о�� �ϱ� �����̴�.
			bytTurnTemp = bytTempBuffer + iPitch * (stInfoHeader.biHeight - 1);

			for (int iCnt = 0; iCnt < stInfoHeader.biHeight; iCnt++)
			{
				// ��ġ ���̸�ŭ bytStripteTemp�� ������ �����͸� �����Ѵ�.
				memcpy(bytSpriteTemp, bytTurnTemp, iPitch);

				// �����ٿ� ����
				bytSpriteTemp += iPitch;

				// �Ʒ����� ���ٿ� ����
				bytTurnTemp -= iPitch;
			}

			fclose(fp);

			delete[] bytTempBuffer;
			return true;
		}
	}
	
	return false;
}

// ��������Ʈ ������ �����ϴ� �Լ��Դϴ�.
void CSpriteDib::ReleaseStrite(int iSpriteIndex)
{
	if (this->m_iMaxSprite <= iSpriteIndex)
		return;

	if (nullptr != m_stpSprite[iSpriteIndex].bytImage)
	{
		delete[] m_stpSprite[iSpriteIndex].bytImage;
		memset(&this->m_stpSprite[iSpriteIndex], 0, sizeof(st_SPRITE));
	}
}

// ��������Ʈ ������ ����ۿ� �׸��� �Լ��Դϴ�.
void CSpriteDib::DrawSprite(int iSpriteIndex, short iDrawX, short iDrawY, BYTE* bytDest, int iDestWidth, int iDestHeight, int iDestPitch, int iDrawLen, void* playerPtr)
{
	// ���ڰ��� �迭�� �ִ� ���̺��� Ŭ ��� return
	if (iSpriteIndex >= m_iMaxSprite)
		return;

	// �̹����� ���� �������� return
	if (nullptr == this->m_stpSprite[iSpriteIndex].bytImage)
		return;

	// �迭�� ����� �̹��� ������ �����ɴϴ�.
	st_SPRITE* stpSprite = &m_stpSprite[iSpriteIndex];

	// �̹����� ���α��� ������ ���
	int iSpriteWidth = stpSprite->iWidth;

	// �̹����� ���α��� ������ ���
	int iSpriteHeight = stpSprite->iHeight;

	// ���� ���ۼ�Ʈ�� �׸���
	iSpriteWidth = iSpriteWidth * iDrawLen / 100;


	// ������� �������̴�.
	// �ȼ������� �����ϱ� ������ DWORD ��, unsigned long���� �޴´�.
	DWORD* dwpDest = (DWORD*)bytDest;
	

	// �̹��� ������
	// �ȼ������� �����ϱ� ������ DWORD ��, unsigned long���� �޴´�.
	DWORD* dwpSprite = (DWORD*)(stpSprite->bytImage);

	
	// �׸��� X��ǥ���� X���� �����Ǹ�ŭ ����.
	iDrawX = iDrawX - stpSprite->iCenterPointX;
	
	// �׸��� Y��ǥ���� Y���� �����Ǹ�ŭ ����.
	iDrawY = iDrawY - stpSprite->iCenterPointY;
	

	// ��Ŭ��ŷ
	if(0 > iDrawY)
	{
		// Y ���� - �� �Ǳ� ������ -�� ��ȣ�� �����Ͽ� ���־�� �Ѵ�.
		iSpriteHeight = iSpriteHeight - (-iDrawY);

		// Y��ġ�� ��ġ�� ���̸� ���� �� �̹��� �����Ϳ� ���Ͽ� 
		// �׷��� �� �̹����� ������ ��ġ�� �����Ѵ�.
		dwpSprite = (DWORD*)(stpSprite->bytImage + stpSprite->iPitch * (-iDrawY));

		// �׸��� iDrawY ���� 0���� ��ƨ~
		iDrawY = 0;	
	}


	// ���� Ŭ��ŷ
	if (0 > iDrawX)
	{
		// ���α��̿��� x�������� ���� ���Ѵ�.
		iSpriteWidth = iSpriteWidth - (-iDrawX);

		
		// �̹��� ���� �����Ϳ��� X������ ��ŭ �����͸� �Ű��ش�.
		dwpSprite = dwpSprite + (-iDrawX);

		iDrawX = 0;
	}


	// �Ʒ�Ŭ��ŷ
	// �̹����� ũ�Ⱑ �޸� ������ ���� ���̸� �Ѿ�� �� if��
	if (iDestHeight <= iDrawY + iSpriteHeight)
	{
		// �� ���� ���α��̸� �Ѿ ��ŭ �̹����� �׸� ���α��̿��� ����.
		iSpriteHeight -= ((iDrawY + stpSprite->iHeight) - iDestHeight);
	}


	// ������ Ŭ����
	if (iDestWidth <= iDrawX + iSpriteWidth)
	{
		// �� ���� ���� ���̸� �Ѿ ��ŭ �̹����� �׸� ���α��̿��� ����.
		iSpriteWidth -= ((iDrawX + iSpriteWidth) - iDestWidth);
	}

	// �̹����� ���α��� �Ǵ� ���α��̰� 0 ���ϸ��� �׸��� ���� ������ �׳� return�ϸ� �ȴ�.
	if (iSpriteWidth <= 0 || iSpriteHeight <= 0)
		return;


	// �̹����� �׸� �������� ���Ѵ�. 
	dwpDest = (DWORD*)((BYTE*)(dwpDest + iDrawX) + (iDrawY * iDestPitch));

	// ����� ������, ����Ʈ ������ ������ �����ϱ� �����̴�.
	BYTE* byteDestOrigin = (BYTE*)dwpDest;

	//�̹��� ���� ������, ����Ʈ ������ ������ �����ϱ� �����̴�.
	BYTE* byteSpriteOrigin = (BYTE*)dwpSprite;


	// �̹����� ���� ���̸�ŭ �ݺ�
	for (int iCntY = 0; iSpriteHeight > iCntY; iCntY++)
	{
		// �̹����� ���� ���̸�ŭ �ݺ�
		for (int iCntX = 0; iSpriteWidth > iCntX; iCntX++)
		{
			// �̹����� �÷�Ű�� �����ϰ� �׸���.
			if (this->m_dwColorKey != (*dwpSprite & 0x00ffffff))
			{
				// BGRA
				if (playerObj == (CPlayerObject*)playerPtr)
				{
					BYTE argb[4];

					memcpy_s(argb, 4, &(*dwpSprite), 4);

					argb[0] *= 2;
					
					*dwpDest = *((DWORD*)argb);
				}
				else
				{
					*dwpDest = *dwpSprite;

				}
			}

			dwpDest++;
			dwpSprite++;
		}
		
		// �� ������ ���� ��
		byteDestOrigin = byteDestOrigin + iDestPitch;
	
		// �̹��� �������� ���� ��
		byteSpriteOrigin = byteSpriteOrigin + stpSprite->iPitch;

		dwpDest = (DWORD*)byteDestOrigin;
		dwpSprite = (DWORD*)byteSpriteOrigin;
	}
}

// ���� ��������Ʈ ������ ����ۿ� �׸��� �Լ��Դϴ�.
void CSpriteDib::DrawImage(int iSpriteIndex,  short iDrawX,  short iDrawY, BYTE* bytDest, int iDestWidth, int iDestHeight, int iDestPitch, int iDrawLen)
{
	// �ִ� ��������Ʈ �迭 ���� Ŭ �� ����. 
	if (iSpriteIndex >= m_iMaxSprite)
		return;

	// �ش� ��������Ʈ �ε����� nullptr �� ��� return
	if (nullptr == this->m_stpSprite[iSpriteIndex].bytImage)
		return;

	st_SPRITE* stpSprite = &m_stpSprite[iSpriteIndex];

	int iSpriteWidth = stpSprite->iWidth;
	int iSpriteHeight = stpSprite->iHeight;

	iSpriteWidth = iSpriteWidth * iDrawLen / 100;

	// �� ���� �������̴�.
	DWORD* dwpDest = (DWORD*)bytDest;	

	// ��� �׸� �������̴�.
	DWORD* dwpSprite = (DWORD*)(stpSprite->bytImage);

	// ���ڷ� ���� ��ǥ�� ���� ��ǥ�� ����Ѵ�.
	iDrawX = iDrawX - stpSprite->iCenterPointX;
	iDrawY = iDrawY - stpSprite->iCenterPointY;	

	// ��Ŭ��ŷ
	if (0 > iDrawY)
	{
		// Y ���� - �� �Ǳ� ������ -�� ��ȣ�� �����Ͽ� ���־�� �Ѵ�.
		iSpriteHeight = iSpriteHeight - (-iDrawY);

		// Y��ġ�� ��ġ�� ���̸� ���� �� �̹��� �����Ϳ� ���Ͽ� 
		// �׷��� �� �̹����� ������ ��ġ�� �����Ѵ�.
		dwpSprite = (DWORD*)(stpSprite->bytImage + stpSprite->iPitch * (-iDrawY));

		// �׸��� iDrawY ���� 0���� ��ƨ~
		iDrawY = 0;
	}


	// ���� Ŭ��ŷ
	if (0 > iDrawX)
	{
		// ���α��̿��� x�������� ���� ���Ѵ�.
		iSpriteWidth = iSpriteWidth - (-iDrawX);


		// �̹��� ���� �����Ϳ��� X������ ��ŭ �����͸� �Ű��ش�.
		dwpSprite = dwpSprite + (-iDrawX);

		iDrawX = 0;
	}


	// �Ʒ�Ŭ��ŷ
	// �̹����� ũ�Ⱑ �޸� ������ ���� ���̸� �Ѿ�� �� if��
	if (iDestHeight <= iDrawY + iSpriteHeight)
	{
		// �� ���� ���α��̸� �Ѿ ��ŭ �̹����� �׸� ���α��̿��� ����.
		iSpriteHeight -= ((iDrawY + stpSprite->iHeight) - iDestHeight);
	}


	// ������ Ŭ����
	if (iDestWidth <= iDrawX + iSpriteWidth)
	{
		// �� ���� ���� ���̸� �Ѿ ��ŭ �̹����� �׸� ���α��̿��� ����.
		iSpriteWidth -= ((iDrawX + iSpriteWidth) - iDestWidth);
	}

	if (iSpriteWidth <= 0 || iSpriteHeight <= 0)
		return;

	dwpDest = (DWORD*)((BYTE*)(dwpDest + iDrawX) + (iDrawY * iDestPitch));

	BYTE* byteDestOrigin = (BYTE*)dwpDest;
	BYTE* byteSpriteOrigin = (BYTE*)dwpSprite;

	for (int iCntY = 0; iSpriteHeight > iCntY; iCntY++)
	{
		for (int iCntX = 0; iSpriteWidth > iCntX; iCntX++)
		{
			/*if (this->m_dwColorKey != (*dwpSprite & 0x00ffffff)) 
			{*/	
				// �� ���ۿ� 4BYTE ��ŭ �� �����Ѵ�.
				*dwpDest = *dwpSprite;
			//}

			dwpDest++;
			dwpSprite++;
		}

		// ��ġ��ŭ �����͸� �Ű� ���� ���� �����Ѵ�.
		byteDestOrigin = byteDestOrigin + iDestPitch;
		byteSpriteOrigin = byteSpriteOrigin + stpSprite->iPitch;

		// ������ �������� DWORD �����Ϳ� ĳ�����Ͽ� �����Ѵ�.
		dwpDest = (DWORD*)byteDestOrigin;
		dwpSprite = (DWORD*)byteSpriteOrigin;
	}
}
