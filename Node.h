#pragma once

// Universal dynamic list node

template <class T>
struct Node
{
	Node* prev = nullptr;
	T* value;
	Node* next = nullptr;

	Node(T* value)
	{
		this->value = value;
	}
};
