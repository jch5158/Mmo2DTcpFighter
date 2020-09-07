//#pragma once
//
//template <class DATA>
//class CFreeList
//{
//private:
//	struct stBlockNode
//	{		
//		stBlockNode()
//		{
//			this->stpNextBlock = nullptr;
//		}
//
//		// ����÷ο츦 üũ�� üũ���Դϴ�.
//		int underCheckSum;
//
//		// ������Ʈ�� �������Դϴ�.
//		DATA data;
//
//		// �����÷ο츦 üũ�� üũ���Դϴ�.
//		int overCheckSum;
//
//		// ~CFreeList() �Ҹ��ڿ��� �ش� ����Ʈ�� ��ȸ�ؼ� Relese 
//		stBlockNode* stpNextAlloc;
//
//		// ���� ��带 üũ�� ��������Դϴ�. 
//		stBlockNode* stpNextBlock;
//	};
//
//
//public:
//
//	CFreeList(int iBlockNum, bool bPlacementNew = false)
//	{
//		// ~CFreeList() �Ҹ��ڿ��� �ش� ����Ʈ�� ��ȸ�ؼ� Relese 
//		this->m_pAllocNodeTop = nullptr;
//
//		// Alloc()�� ���� ����Ʈ
//		this->m_pFreeNode = nullptr;
//	
//		this->m_bPlaceMentNew = bPlacementNew;
//
//		this->m_iBlockCount = iBlockNum;
//
//		for (int iCnt = 0; iCnt < iBlockNum; ++iCnt)
//		{
//			stBlockNode* blockPtr = (stBlockNode*)malloc(sizeof(stBlockNode));
//
//			blockPtr->stpNextBlock = this->m_pFreeNode;
//
//			blockPtr->stpNextAlloc = this->m_pAllocNodeTop;
//
//			this->m_pAllocNodeTop = blockPtr;
//
//			this->m_pFreeNode = blockPtr;
//		}
//	}
//
//	virtual ~CFreeList()
//	{
//		while (1)
//		{
//			if (this->m_pAllocNodeTop == nullptr)
//			{
//				break;
//			}
//			// ������ �����͸� ptrBuffer�� ��´�.
//			stBlockNode* ptrBuffer = this->m_pAllocNodeTop;
//
//			// ptrBuffer�� ���� ��� ���� top ���� �ٲ۴�.
//			this->m_pAllocNodeTop = ptrBuffer->stpNextAlloc;
//
//			// ����
//			free(ptrBuffer);
//		}
//	}
//
//	DATA* Alloc(void)
//	{
//
//	}
//
//	bool Free(DATA* tData)
//	{
//
//	}
//
//	// ���� Ȯ�� �� ���� ��ü ����
//	int GetAllocCount(void)
//	{
//		return this->m_iAllocCount;
//	}
//
//	// ���� ������� ���� ����
//	int	GetUseCount(void)
//	{
//		return this->m_iBlockCount;
//	}
//
//	// placement new�� ȣ������ ������ ����
//	bool m_bPlaceMentNew;
//
//	// �� Ȯ���� ��� ��
//	int m_iAllocCount
//
//	// ������� ��� ��
//	int m_iBlockCount;
//
//	// ~CFreeList() �Ҹ��ڿ��� �ش� ����Ʈ�� ��ȸ�ؼ� Relese 
//	stBlockNode* m_pAllocNodeTop;
//
//	// ���� ������� ��ȯ�� (�̻��) ������Ʈ ���� ����. ž ��忪���� �� �������
//	stBlockNode* m_pFreeNode;
//
//};
//
