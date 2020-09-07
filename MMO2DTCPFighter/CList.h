#pragma once

template <typename T>
class CList
{
private:
	struct Node
	{
		T data;
		Node* prev;
		Node* next;

		bool deleteCheck;

		// �������Դϴ�.
		Node(T data = NULL)
		{
			this->data = data;
			prev = nullptr;
			next = nullptr;
			deleteCheck = false;
		}
	};

	Node* head;
	Node* tail;
public:

	class Iterator
	{
	public:
		Node* node;

		friend class CList;

		Iterator(Node* node = nullptr)
		{
			this->node = node;
		}

		Iterator NextIter()
		{
			Iterator iter(this->node->next);
			return iter;
		}


		// ������ �����ε�

		const Iterator& operator++(int)
		{
			const Iterator iterator(this->node->next);
			return iterator;
		}

		Iterator& operator++()
		{
			this->node = this->node->next;
			return *this;
		}


		const Iterator& operator--(int)
		{
			const Iterator iterator(this->node->prev);

			return iterator;
		}

		Iterator& operator--()
		{
			this->node = this->node->prev;

			return *this;
		}

		Node* operator*() const
		{
			return this->node;
		}

		T operator->() const
		{
			return this->node->data;
		}

		bool operator==(const Iterator& iter) const
		{
			return this->node->data == iter.node->data;
		}

		bool operator!=(const Iterator& iter) const
		{
			return !(this->node->data == iter.node->data);
		}
	};


public:

	int listLength;

	CList()
	{
		head = new Node();
		tail = new Node();

		head->next = tail;
		tail->prev = head;	

		head->prev = nullptr;
		tail->next = nullptr;
	
		listLength = 0;
	}

	~CList()
	{
		Node* prev = nullptr;

		while (head != nullptr)
		{
			prev = head;
			head = head->next;
			delete prev;
		}
	}

	void PushBack(T data)
	{
		listLength += 1;

		Node* node = new Node(data);

		// ���� �ڿ� �߰�
		InputNode(tail, node);
	}

	void PushFront(T data)
	{
		listLength += 1;

		Node* node = new Node(data);

		InputNode(head->next, node);
	}

	void insert(Iterator iter, T data)
	{

		listLength += 1;

		Node* node = new Node(data);

		InputNode(iter.node, node);
	}

	Iterator begin()
	{

		return Iterator(head->next);
	}

	Iterator end()
	{
		return Iterator(tail);
	}

	Iterator erase(Iterator iter)
	{
		listLength -= 1;

		Iterator iterBuffer = iter;

		iterBuffer.node->prev->next = iterBuffer.node->next;

		iterBuffer.node->next->prev = iterBuffer.node->prev;

		Iterator iterator(iterBuffer.node->next);

		delete iterBuffer.node;

		return iterator;
	}

	bool Remove(T data)
	{
		Iterator iterE = this->end();

		for (Iterator iter = this->begin(); iter != iterE; ++iter)
		{

			if (iter.node->data == data)
			{

				this->erase(iter);

				return true;
			}
		}
		return false;
	}


	void DataSwap(Iterator iterF, Iterator iterE) {

		T bufferData = iterF.node->data;

		iterF.node->data = iterE.node->data;

		iterE.node->data = bufferData;
	}

private:

	// Ư�� ���ڿ� input
	void InputNode(Node* node, Node* newNode)
	{
		newNode->prev = node->prev;
		newNode->next = node;

		node->prev->next = newNode;
		node->prev = newNode;
	}

};