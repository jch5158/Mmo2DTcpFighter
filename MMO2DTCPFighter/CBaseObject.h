#pragma once
class CBaseObject
{
public:


	CBaseObject();

	virtual ~CBaseObject();

	unsigned int GetX();

	unsigned int GetY();

	// KeyProcess() ���� �Է°��� �޽��ϴ�.
	// � �׼��� ���� ĳ���� ��ü ��������� �������ش�. 
	void ActionInput(DWORD dwAction);

	// ĳ������ ��ġ�� �������ִ� �Լ��Դϴ�.
	void SetPosition(int iXpos, int iYpos);

	void SetSprite(DWORD dwSpriteStart, DWORD dwSpriteMax, DWORD dwFrameDelay);

	int NextFrame();

	//int GetObjectID();

	//int GetObjectType();

	//int GetSprite();

	//int IsEndFrame();

	virtual void Render() = 0;

	virtual void Update() = 0;



public:

	// �ش� �������� true�� ��� �ٽ� ó�� ��������Ʈ�� ���ư��ϴ�.
	bool m_bEndFrame;


	// ����� �Է°� �����ϴ� �������.
	DWORD m_ActionInput;

	// ������� �Է°��� ó���ϴ� �޽���
	DWORD m_dwActionCur;

	unsigned int m_iXpos;

	unsigned int m_iYpos;

	// ������ ī��Ʈ�� ������� �Ǿ����� ������ �����̿��� üũ
	DWORD m_dwDelayCount;

	// �����Ӻ��� ������ ���� �־��ݴϴ�.
	DWORD m_dwFrameDelay;


	// ��������Ʈ ���� ��
	DWORD m_dwSpriteStart;

	// ���� ��������Ʈ �ε��� ��
	DWORD m_dwSpriteNow;

	// �� ��������Ʈ ��
	DWORD m_dwSpriteEnd;

	// ������Ʈ ID
	DWORD m_dwObjectID;

	// �������� �Ʊ����� 
	DWORD m_ObjectType;

	// ���� ������ ����Ʈ
	BYTE m_dwDirCur;

	// ���� ����
	BYTE m_dwDirOld;

	bool deleteCheck;

	// ĳ���� hp
	unsigned char m_chHP;

};



template<class T>
class YaxixCompare
{
public:
	bool operator()(const T leftObject, const T rightObject) const
	{
		return leftObject->m_iYpos < rightObject->m_iYpos;
	};
};