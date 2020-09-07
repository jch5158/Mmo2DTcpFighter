#pragma once

// ����۸� ����� ����۸� Filp�Ͽ� ���� ȭ���� �����մϴ�.
class CScreenDib
{
public:

	// �� ������ ���� ���� ���� �׸��� 32 �÷���Ʈ
	CScreenDib(int iWidth, int iHeight, int iColorBit);

	virtual ~CScreenDib();

public:
	
	void Filp(HWND hWnd, int iX = 0, int iY = 0);

	BYTE* GetDibBuffer();
	
	int GetWidth(void);

	int GetHeight(void);

	int GetPitch(void);

protected:

	void CreateDibBuffer(int iWidth, int iHeight, int iColorBit);

	void ReleaseDibBuffer(void);


	BITMAPINFOHEADER m_stDibInfoh = { 0, };

	// �� ���۸� ���� byte������ �������Դϴ�.
	BYTE* m_bypBuffer;

	// �� ������ ���α��� �Դϴ�.
	int m_iWidth;

	// �� ������ ���α��� �Դϴ�.
	int m_iHeight;
	
	// 4����Ʈ ���ĵ� �� ���� ����Ʈ ��
	int m_iPitch;  	
	
	// �÷� ��Ʈ�Դϴ�.
	int m_iColorBit;

	// ���� ��ü �������Դϴ�. ( ��ġ X m_iHeight )
	int m_iBufferSize;

};


// �� ������ ���� ���� ���� �׸��� 32 �÷���Ʈ
extern CScreenDib ScreenDib;
