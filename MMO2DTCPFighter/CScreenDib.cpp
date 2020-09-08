
#include "stdafx.h"
#include "CScreenDib.h"

// �� ������ ���� ���� ���� �׸��� 32 �÷���Ʈ
CScreenDib ScreenDib = CScreenDib(6400, 6400, 32);


// ����۸� �������ش�.
CScreenDib::CScreenDib(int iWidth, int iHeight, int iColorBit) :m_iWidth(iWidth), m_iHeight(iHeight), m_iColorBit(iColorBit)
{
	// 32��Ʈ ����� ��ġ�� ����մϴ�.
	this->m_iPitch = ((this->m_iWidth * (m_iColorBit / 8)) + 3) & ~3;

	// ����ü�� ũ�⸸ŭ �������ش�.
	this->m_stDibInfoh.biSize = sizeof(BITMAPINFOHEADER);

	// ���� ����
	this->m_stDibInfoh.biWidth = iWidth;
	
	// ���� ���� 
	this->m_stDibInfoh.biHeight = -iHeight;
		
	this->m_stDibInfoh.biPlanes = 1;
	
	// ���Ʈ �÷����� Ȯ��
	this->m_stDibInfoh.biBitCount = iColorBit;

	// �������� bmp������ ������ �������� 
	this->m_stDibInfoh.biCompression = BI_RGB;

	// ���� * ���̸�ŭ �����Ҵ����ش�.
	CreateDibBuffer(m_iWidth, m_iHeight, m_iColorBit);
}

CScreenDib::~CScreenDib() {

	// ���� ����� �����մϴ�.
	ReleaseDibBuffer();

}

void CScreenDib::CreateDibBuffer(int iWidth, int iHeight, int iColorBit) {


	// ���� �����ŭ �����Ҵ��� �մϴ�.
	this->m_bypBuffer = new BYTE[this->m_iPitch * this->m_iHeight];

}

void CScreenDib::ReleaseDibBuffer(void) {

	// ���ۻ����� �����Ҵ� ����
	delete[] m_bypBuffer;
}

// �ø� ȣ��� ����ۿ� �׸� ���� ����Ѵ�.
void CScreenDib::Filp(HWND hWnd, int iX, int iY) {

	// ������ �ڵ�� dc
	HDC hdc = GetDC(hWnd);

	// dib����ϴ� �Լ��Դϴ�.
	StretchDIBits
	(
		hdc,                                     // ������ DC
		iX,                                      // x ��ǥ
		iY,                                      // y ��ǥ
		this->m_iPitch,                          // ������ �ʺ�
		this->m_iHeight,						 // ������ ����
		0,                                       // ��¼ҽ� x ��ǥ
		0,                                       // ��¼ҽ� y ��ǥ
		this->m_iPitch,                          // ��¼ҽ� �ʺ�
		this->m_iHeight,					     // ��¼ҽ� ����
		this->m_bypBuffer,                       // �̹����� ��ġ�� ������
		(BITMAPINFO*)(&this->m_stDibInfoh),      // BITMAPINFO = (BITMAPINFOHEADER + RGBQUAD) -> typeĳ���� �ؾ��Ѵ�. 
		DIB_RGB_COLORS,                          // DIB_RGB_COLORS , RGB ����Ʈ�� ���� ���� ����.
		SRCCOPY                                  // ��¸��
	);
	
	static DWORD frameCheck = 50;

	static DWORD timeCheck = timeGetTime();

	static DWORD frameNow = 0;

	frameNow += 1;

	if (timeGetTime()- timeCheck >= 1000) {

		frameCheck = frameNow;

		timeCheck = timeGetTime();
	
		frameNow = 0;
	}

	WCHAR text[10];

	wsprintf(text, L"%d", frameCheck);

	TextOut(hdc, 0, 0, text, 2);

	ReleaseDC(hWnd, hdc);
}

// �� ������ �����͸� return �Ѵ�.
BYTE* CScreenDib::GetDibBuffer()
{
	return this->m_bypBuffer;
}

// �� ������ ���� ���̸� return�Ѵ�.
int CScreenDib::GetWidth(void) 
{
	return this->m_iWidth;
}

// �� ������ ���� ���̸� return �Ѵ�.
int CScreenDib::GetHeight(void) 
{
	return this->m_iHeight;
}

// �� ������ pitch�� return�Ѵ�.
int CScreenDib::GetPitch(void) 
{
	return this->m_iPitch;
}
