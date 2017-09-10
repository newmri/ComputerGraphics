#pragma once

#include <iostream>
using namespace std;

typedef int DATA_TYPE;

template<typename DATATYPE>
struct Pos
{
	DATATYPE x, y, z;
	double distFromStartPos;
	Pos()
	{
		x = 0, y = 0, z = 0;
		distFromStartPos = 0.0f;
	}
};

template<typename DATATYPE>
struct Node
{
	Node()
	{
		m_prev = nullptr;
		m_next = nullptr;
	}

	Pos<DATA_TYPE> m_pos;
	Node* m_prev;
	Node* m_next;
};

template<typename DATATYPE>
class CDeque
{

public:
	void AddFront(const Pos<DATA_TYPE> pos)
	{
		Node<DATA_TYPE>* node = new Node<DATA_TYPE>;
		node->m_pos = pos;
		node->m_pos.distFromStartPos = sqrt((pos.x) * (pos.x) + (pos.y) * (pos.y) + (pos.z) * (pos.z));

		node->m_next = m_head;
		m_size == 0 ? m_tail = node : m_head->m_prev = node;

		m_head = node;
		m_size++;

	}

	void AddRear(const Pos<DATA_TYPE> pos)
	{
		Node<DATA_TYPE>* node = new Node<DATA_TYPE>;
		node->m_pos = pos;
		node->m_pos.distFromStartPos = sqrt((pos.x) * (pos.x) + (pos.y) * (pos.y) + (pos.z) * (pos.z));

		node->m_prev = m_tail;
		m_size == 0 ? m_head = node : m_tail->m_next = node;

		m_tail = node;
		m_size++;

	}

	Pos<DATA_TYPE> RemoveFront()
	{
		Node<DATA_TYPE>* node = m_head;
		Pos<DATA_TYPE> pos;
		pos.distFromStartPos = -1;

		if (m_size == 0) return pos;
		pos = m_head->m_pos;

		m_head = m_head->m_next;
		delete node;

		m_head == nullptr ? m_tail = nullptr : m_head->m_prev = nullptr;
		m_size--;

		return pos;

	}

	Pos<DATA_TYPE> RemoveRear()
	{
		Node<DATA_TYPE>* node = m_tail;
		Pos<DATA_TYPE> pos;
		pos.distFromStartPos = -1;

		if (m_size == 0) return pos;
		pos = m_tail->m_pos;

		m_tail = m_tail->m_prev;
		delete node;

		m_tail == nullptr ? m_head = nullptr : m_tail->m_next = nullptr;
		m_size--;

		return pos;
	}

	void RemoveAll()
	{
		while(m_size != 0) RemoveRear();
	}

	Pos<DATA_TYPE> PeekFront() const
	{
		Pos<DATA_TYPE> pos;
		pos.distFromStartPos = -1;

		return (m_size == 0 ? pos : m_head->m_pos);
	}

	Pos<DATA_TYPE> PeekRear() const
	{
		Pos<DATA_TYPE> pos;
		pos.distFromStartPos = -1;

		return (m_size == 0 ? pos : m_tail->m_pos);
	}

	Pos<DATA_TYPE> PeekNearest()
	{
		Pos<DATA_TYPE> pos;
		pos.distFromStartPos = -1;

		if (m_tail == nullptr) {
			cout << "Empty" << endl;
			return pos;
		}

		Node<DATA_TYPE>* node = m_tail;
		pos = node->m_pos;

		if (m_size == 1) {
			this->Display(pos);
			return pos;
		}

		while (node) {
			if (node->m_prev == nullptr) {
				this->Display(pos);
				return pos;
			}

			node = node->m_prev;
			if (node->m_pos.distFromStartPos < pos.distFromStartPos) pos = node->m_pos;
			else if (node->m_pos.distFromStartPos == pos.distFromStartPos) {
				if ((node->m_pos.x + node->m_pos.y + node->m_pos.z) < (pos.x + pos.y + pos.z)) pos = node->m_pos;
			}
		}

		this->Display(pos);
		return pos;
	}

	Pos<DATA_TYPE> PeekFurtherMost()
	{
		Pos<DATA_TYPE> pos;
		pos.distFromStartPos = -1;

		if (m_tail == nullptr) {
			cout << "Empty" << endl;
			return pos;
		}

		Node<DATA_TYPE>* node = m_tail;
		pos = node->m_pos;

		if (m_size == 1) {
			this->Display(pos);
			return pos;
		}

		while (node) {
			if (node->m_prev == nullptr) {
				this->Display(pos);
				return pos;
			}

			node = node->m_prev;
			if (node->m_pos.distFromStartPos > pos.distFromStartPos) pos = node->m_pos;
			else if (node->m_pos.distFromStartPos == pos.distFromStartPos) {
				if ((node->m_pos.x + node->m_pos.y + node->m_pos.z) > (pos.x + pos.y + pos.z)) pos = node->m_pos;
			}
		}

		this->Display(pos);
		return pos;
	}

	void Display(Pos<DATA_TYPE> pos) const
	{
		cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << endl;
		cout << "dist: " << pos.distFromStartPos << endl;
	}

	void DisplayAll() const
	{
		if (m_tail == nullptr) {
			cout << "Empty" << endl;
			return;
		}
		Node<DATA_TYPE>* node = m_tail;
		
		while (node) {
			cout << "x: " << node->m_pos.x << " y: " << node->m_pos.y << " z: " << node->m_pos.z << endl;
			node = node->m_prev;

		}
	}

	int Size() const
	{
		return m_size;
	}
	bool IsEmpty() const
	{
		return (m_head == nullptr ? true : false);
	}

public:
	CDeque()
	{
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}

private:
	Node<DATA_TYPE>* m_head;
	Node<DATA_TYPE>* m_tail;
	int m_size;
};