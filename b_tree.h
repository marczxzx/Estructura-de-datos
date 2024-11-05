#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <iomanip>

const int MAX_KEYS = 4;  // Número máximo de llaves por nodo

struct BTreeNode {
    float keys[MAX_KEYS];  // Array de llaves
    BTreeNode* children[MAX_KEYS + 1]; // Punteros a nodos hijos
    int num_keys;          // Número actual de llaves

    BTreeNode();
};

BTreeNode* createNode();
void insert(BTreeNode** root, float key);
void splitChild(BTreeNode* parent, int index);
void insertNonFull(BTreeNode* node, float key);
void insertKey(BTreeNode* node, float key);
void printTree(BTreeNode* node, int level = 0);
bool search(BTreeNode* node, float key);


#endif // B_TREE_H

