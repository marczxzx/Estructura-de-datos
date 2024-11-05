#include "b_tree.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
static int insert_count = 0; // Contador de inserciones

BTreeNode::BTreeNode() : num_keys(0) {
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        children[i] = nullptr;
    }
}

BTreeNode* createNode() {
    BTreeNode* newNode = new BTreeNode();
    if (!newNode) {
        std::cerr << "La asignación de memoria falló.\n";
        exit(1);
    }
    return newNode;
}

void insert(BTreeNode** root, float key) {
    if (*root == nullptr) {
        *root = createNode();
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        insert_count++; // Incrementar contador
        std::cout << "Insertado: " << key << " (Total: " << insert_count << ")" << std::endl; // Mensaje de inserción
    } else {
        if ((*root)->num_keys == MAX_KEYS) {
            BTreeNode* newRoot = createNode();
            newRoot->children[0] = *root;
            splitChild(newRoot, 0);
            *root = newRoot;
        }
        insertNonFull(*root, key);
        insert_count++; // Incrementar contador
        std::cout << "Insertado: " << key << " (Total: " << insert_count << ")" << std::endl; // Mensaje de inserción
    }
}

void splitChild(BTreeNode* parent, int index) {
    BTreeNode* child = parent->children[index];
    BTreeNode* newChild = createNode();

    // Se asigna la mitad de las llaves al nuevo hijo
    newChild->num_keys = MAX_KEYS / 2; // 2 llaves para un nodo de 4
    for (int i = 0; i < newChild->num_keys; i++) {
        newChild->keys[i] = child->keys[i + 2]; // Se mueven las últimas 2 llaves
    }

    if (child->children[0] != nullptr) {
        for (int i = 0; i <= newChild->num_keys; i++) {
            newChild->children[i] = child->children[i + 2]; // Se mueven los hijos
        }
    }

    child->num_keys = 2; // Se actualiza el número de llaves del nodo hijo
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i]; // Se desplazan los hijos en el padre
    }

    parent->children[index + 1] = newChild; // Se añade el nuevo hijo al padre
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i]; // Se desplazan las llaves en el padre
    }

    parent->keys[index] = child->keys[1]; // Se sube la llave del medio al padre
    parent->num_keys++;
}

void insertNonFull(BTreeNode* node, float key) {
    int i = node->num_keys - 1;
    if (node->children[0] == nullptr) {
        insertKey(node, key);
        return;
    }

    while (i >= 0 && node->keys[i] > key) {
        i--;
    }
    i++;

    if (node->children[i]->num_keys == MAX_KEYS) {
        splitChild(node, i);
        if (node->keys[i] < key) {
            i++;
        }
    }
    insertNonFull(node->children[i], key);
}

void insertKey(BTreeNode* node, float key) {
    int i = node->num_keys - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i]; // Desplaza las llaves para hacer espacio
        i--;
    }
    node->keys[i + 1] = key; // Inserta la nueva llave
    node->num_keys++;
}



//Funcion para buscar llave
bool search(BTreeNode* node, float key) {
    if (node == nullptr) {
        return false; // La llave no se encuentra
    }

    int i = 0;
    // Encuentra la posición de la llave
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }

    // Comprueba si se encontró la llave (considerando una tolerancia)
    if (i < node->num_keys && std::fabs(node->keys[i] - key) < 1e-6) { // Ajusta la tolerancia según sea necesario
        return true; // La llave se encuentra
    }

    // Si no es una hoja, busca en el hijo correspondiente
    if (node->children[0] == nullptr) {
        return false; // Es una hoja, no se encuentra la llave
    }

    return search(node->children[i], key); // Busca en el hijo correspondiente
}







