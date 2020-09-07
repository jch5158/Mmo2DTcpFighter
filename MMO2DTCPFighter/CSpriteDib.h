#pragma once


//StripteDib �� �̹��� ������ �޾Ƽ� ����ۿ� �׸��� ���� Ŭ�����Դϴ�.
class CSpriteDib
{

public:

	// DIB ��������Ʈ ����ü
	struct st_SPRITE {
		
		// �̹��� ũ�� ������
		BYTE* bytImage;

		// ���α���
		int iWidth;

		// ���α���
		int iHeight;

		// ��ġ����
		int iPitch;

		// ���� X
		int iCenterPointX;
		
		// ���� Y
		int iCenterPointY;
	};

	CSpriteDib(int m_iMaxSprite,DWORD dwColorKey);

	virtual ~CSpriteDib();

	BOOL LoadDibSprite(int iSpriteIndex, const char* szFileName, int iCenterPointX, int iCenterPointY);

	void ReleaseStrite(int iSpriteIndex);

	void DrawSprite(int iSpriteIndex,  short iDrawX,  short iDrawY, BYTE* bytDest, int iDestWidth, int iDestHeight, int iDestPitch, int iDrawLen = 100, void* playerPtr = nullptr);

	void DrawImage(int iSpriteIndex,  short iDrawX,  short iDrawY, BYTE* bytDest, int iDestWidth, int iDestHeight, int iDestPitch, int iDrawLen = 100);


protected:

	// ��������Ʈ �迭 ����
	int m_iMaxSprite;

	// �̹��� ���� �迭
	st_SPRITE* m_stpSprite;

	// �÷�Ű�Դϴ�.
	DWORD m_dwColorKey;
};

extern CSpriteDib SpriteDib;
