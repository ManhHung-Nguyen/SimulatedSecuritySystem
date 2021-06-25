#include "BTree.h"
#include "Builder.h"

int comparer;
BSTree* last_node;

BSTree* BSTree::find_node(LPCHAR key) {

    if (key == 0) {
        return 0;
    }

    BSTree* p = this;
    last_node = 0;

    while (p) {
        comparer = Builder::Compare(key, p->key);
        if (comparer == 0) {
            return p;
        }

        last_node = p;
        p = (BSTree*)(comparer < 0 ?
            last_node->left :
            last_node->right);
    }

    return 0;
}

void BSTree::Insert(LPCHAR key, void* value) {

    if (this->key == 0) {
        this->key = key;
        this->value = value;
        return;
    }

    BSTree* p = find_node(key);
    if (p == 0) {
        p = new BSTree(key, value);
        if (comparer < 0) {
            last_node->left = p;
        }
        else {
            last_node->right = p;
        }
    }
}
