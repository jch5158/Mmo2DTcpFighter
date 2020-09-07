#include "stdafx.h"
#include "CFrameSkip.h"

CFrameSkip::CFrameSkip()
{
	this->m_dwMaxFPS = 20;

	this->m_dwOneFrameTime = 0;
}

CFrameSkip::~CFrameSkip()
{

}

// ���� ������ �ؽ�Ʈ ���
bool CFrameSkip::UpdateCheck(HWND hWnd) {

	static DWORD frameCheck = 50;
	
	static DWORD timeCheck = timeGetTime();

	static DWORD frameNow = 0;

	frameNow += 1;

	if (timeGetTime() - timeCheck >= 1000) {

		frameCheck = frameNow;

		timeCheck = timeGetTime();

		frameNow = 0;
	}

	WCHAR text[20];

	wsprintf(text, L"Logic : %d", frameCheck);

	SetWindowTextW(hWnd, text);

	return true;
}

bool CFrameSkip::FrameSkip()
{
	static DWORD oldTime = timeGetTime();

	DWORD nowTime = timeGetTime();
	
	// ���� �ð� - ���õ� �ð�.
	this->m_dwOneFrameTime += (nowTime - oldTime);

	//dwMaxFPS == 20 �̴�.	
	if (this->m_dwOneFrameTime < this->m_dwMaxFPS)
	{	
		// �̹��� Sleep �ؾߵ� �ð� == ( �� ������ - �� �� �������� ���ݱ��� �ɸ� �ð� )
		Sleep(this->m_dwMaxFPS - this->m_dwOneFrameTime);

		// Sleep ���� ���� �ð��� �ٽ� �������ش�. 
		// TimeGetTime()�� �ٽ� ȣ���Ͽ� ���� �ð��� ��Ȯ���� �ʱ� ������ 
		// nowTime + Sleep ���� �� �ð���ŭ �������ش�. 
		oldTime = nowTime+(this->m_dwMaxFPS-this->m_dwOneFrameTime);
	
		// ���� �ð� üũ ������ �������ش�.
		this->m_dwOneFrameTime = 0;

		return true;
	}
	else 
	{
		/*this->m_dwOneFrameTime -= this->m_dwMaxFPS;

		if (this->m_dwOneFrameTime >=this->m_dwMaxFPS)
		{*/
		//	this->m_dwOneFrameTime -= this->m_dwMaxFPS;
			//oldTime = nowTime;
		//	return false;
		//}	

		// �̹� �����ӿ��� 20�� ����ߴٰ� �ؼ� �ٷ� ������ ��ŵ���� �ʴ´�.
		// ���� �ð� üũ �������� - Sleep �ð���ŭ ���� ���� ���� �ð� üũ ��������
		// 20 �̻��� ������ ��� ������ ��ŵ�Ѵ�.
		this->m_dwOneFrameTime -= this->m_dwMaxFPS;

		oldTime = nowTime;

		if (this->m_dwOneFrameTime >= this->m_dwMaxFPS)
		{
			this->m_dwOneFrameTime -= this->m_dwMaxFPS;
			
			return false;
		}	
	}

	return true;
}

/*
bool CFrameSkip::FrameSkip(HWND hWnd)
{
	// Logic FPS Ȯ���ϱ� ���� ������
	static DWORD logicOldTime = timeGetTime();
	static DWORD logicFrame = 0;
	logicFrame++;

	static DWORD oldTime = timeGetTime();      // Render ó�� ���� �ð� ����
	DWORD       curTime = timeGetTime();      // Render ���� �ð� ����

	_OneFrameTime += curTime - oldTime;         // 1 frame �ɸ��� �ð�

	// 1�ʸ��� LogicFrame ���
	if (curTime - logicOldTime > 1000)
	{
		WCHAR szFrame[TEXT_SIZE];
		wsprintf(szFrame, L"LogicFPS = %d", logicFrame);
		SetWindowText(hWnd, szFrame);
		logicOldTime = timeGetTime();
		logicFrame = 0;
	}

	// 1 Frame �ӵ��� ��ǥ �ӵ� ���� ������ ���� ������ ��츦 ����� ������ ó���Ѵ�.
	if (_OneFrameTime < _MaxFrameTime)
	{
		// 1 Frame �ð��� ��ǥġ ���� ������ ��ǥġ�� �ɶ����� ���� �ش�.
		Sleep(_MaxFrameTime - _OneFrameTime);
		// ! ���� : oldTime ���� timeGetTime�� ����ϸ� �ȵ� !
		// Sleep �Լ� �۵� �ð��� �ֱ⶧���� oldTime�� timeGetTime���� �����Ѵٸ� ��Ȯ�� ���� �� �� ����.
		// ������� �Ʊ� ���� ���� �ð����� ���� ����ŭ �����ش�.
		oldTime = curTime + (_MaxFrameTime - _OneFrameTime);
		_OneFrameTime = 0;
	}
	else
	{
		// OneFrameTime�� _MaxFrameTime�� �ʰ��ߴٸ� �ʰ��� �� ��ŭ ���ܵд�.
		_OneFrameTime -= _MaxFrameTime;

		oldTime = timeGetTime();

		// _OneFrameTime�� �ʰ��� ���� �����Ǿ� _MaxFrameTime�� �޼��ߴٸ� Render �ѹ��� Skip�Ͽ� LoginFPS�� �����ش�.
		if (_OneFrameTime >= _MaxFrameTime)
		{
			_OneFrameTime -= _MaxFrameTime;
			return false;
		}
	}

	return true;
}
*/