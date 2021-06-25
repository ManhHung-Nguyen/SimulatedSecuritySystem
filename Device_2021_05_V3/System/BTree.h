#pragma once
#include "Types.h"

class BSTree {
	BSTree* left;
	BSTree* right;
	LPCHAR key;
	void* value;

	BSTree* find_node(LPCHAR key);
public:
	BSTree(LPCHAR key = 0, void* value = 0)
		: key(key), value(value) {
		left = right = 0;
	}
	void Insert(LPCHAR key, void* value);
	void* Find(LPCHAR key) {
		BSTree* p = find_node(key);
		return p ? p->value : 0;
	}
};
