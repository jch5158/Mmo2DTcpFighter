#pragma once
class CFrameSkip
{
public:

	CFrameSkip();

	~CFrameSkip();
	
	//20
	DWORD m_dwMaxFPS;


	// ������Ʈ ������ �� ���� �������� �������
	DWORD m_dwOneFrameTime;	


	
	bool FrameSkip();



	bool UpdateCheck(HWND hWnd);

};

