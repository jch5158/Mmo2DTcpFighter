#pragma once

class CDamageEffect : public CBaseObject
{
public:

	CDamageEffect(void* victimPtr,int usX, int usY,DWORD actionCur);

	virtual ~CDamageEffect();

	DWORD m_EffectTiming;

	DWORD m_TimeSet;

	bool m_RenderCheck;

	void Update();

	void Render();

private:

	// ���� ĳ������ ������
	void* mVictimPtr;

};

