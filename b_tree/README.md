# Implementación de Árbol B en C++

Este proyecto implementa una estructura de Árbol B en C++, que permite gestionar datos de manera eficiente a través de operaciones de inserción y búsqueda. El Árbol B es un tipo de árbol de búsqueda balanceado, ideal para estructuras de datos que requieren un rendimiento óptimo en operaciones de acceso y modificación de datos.

## Descripción

Esta implementación está diseñada para almacenar claves de punto flotante y limitar la cantidad de decimales a 5, lo cual es útil en aplicaciones que manejan datos con precisión decimal, como los valores de una tabla de datos cargada desde un archivo CSV.
Ademas tenemos el siguiente requisito o codigo base para usar:
```cpp
#define MAX_KEYS 4

struct BTreeNode {
  int num_keys;
  int keys[MAX_KEYS];
  struct BTreeNode *children[MAX_KEYS + 1];
};
```

### Funciones Principales
Las siguientes funciones son bases y seran utilizadas en nuestro codigo.

- **createNode**: Crea un nuevo nodo para el árbol B.
```cpp
struct BTreeNode *createNode() {
  struct BTreeNode *newNode =
      (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  if (newNode == NULL) {
    printf("La asignación de memoria falló.\n");
    exit(1);
  }
  newNode->num_keys = 0;
  for (int i = 0; i < MAX_KEYS + 1; i++) {
    newNode->children[i] = NULL;
  }
  return newNode;
}
```
- **insert**: Inserta una nueva clave en el árbol.
```cpp
void insert(struct BTreeNode **root, int key) {
  if (*root == NULL) {
    *root = createNode();
    (*root)->keys[0] = key;
    (*root)->num_keys = 1;
  } else {
    if ((*root)->num_keys == MAX_KEYS) {
      struct BTreeNode *newRoot = createNode();
      newRoot->children[0] = *root;
      splitChild(newRoot, 0);
      *root = newRoot;
    }
    insertNonFull(*root, key);
  }
}
```
- **splitChild**: Divide un nodo cuando se supera el número máximo de claves permitido.}
```cpp
void splitChild(struct BTreeNode *parent, int index) {
  struct BTreeNode *child = parent->children[index];
  struct BTreeNode *newChild = createNode();
  newChild->num_keys = MAX_KEYS / 2;
  for (int i = 0; i < MAX_KEYS / 2; i++) {
    newChild->keys[i] = child->keys[i + MAX_KEYS / 2 + 1];
  }
  if (child->children[0] != NULL) {
    for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
      newChild->children[i] = child->children[i + MAX_KEYS / 2 + 1];
    }
  }
  child->num_keys = MAX_KEYS / 2;
  for (int i = parent->num_keys; i >= index + 1; i--) {
    parent->children[i + 1] = parent->children[i];
  }
  parent->children[index + 1] = newChild;
  for (int i = parent->num_keys - 1; i >= index; i--) {
    parent->keys[i + 1] = parent->keys[i];
  }
  parent->keys[index] = child->keys[MAX_KEYS / 2];
  parent->num_keys++;
}
```
- **insertNonFull**: Inserta una clave en un nodo que no ha alcanzado el máximo de claves.
```cpp
void insertNonFull(struct BTreeNode *node, int key) {
  int i = node->num_keys - 1;
  if (node->children[0] == NULL) {
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
```
- **insertKey**: Función principal que gestiona la inserción de claves en el árbol.
```cpp
void insertKey(struct BTreeNode *node, int key) {
  int i = node->num_keys - 1;
  while (i >= 0 && node->keys[i] > key) {
    node->keys[i + 1] = node->keys[i];
    i--;
  }
  node->keys[i + 1] = key;
  node->num_keys++;
}
```
- **search**_ Funcion que se encarga de la busqueda de un valor específico dentro del arbol.
```cpp
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
```
-**buildTreeFromCSV**: Funcion que se encarga de leer los valores del archivo "random.csv" y los inserta dentro de nuestro arbol.
```cpp
void buildTreeFromCSV(BTreeNode*& root, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        float value;

        // Ignora la primera columna (número secuencial)
        getline(ss, temp, ','); // Lee y descarta la primera columna

        // Lee el valor flotante de la segunda columna
        if (ss >> value) {
            insert(&root, value);
        }
    }

    file.close();
}
```

## Archivos

- `b_tree.h`: Contiene la declaración de la estructura de datos y las funciones del Árbol B.
- `b_tree.cpp`: Implementa las funciones declaradas en `b_tree.h`.
- `main.cpp`: Aqui se hace llamado a todas las funciones del Arbol B.

## Grafico comparacion Insertion
Este grafico muestra la comparacion cuando el valor de la variable MAX_KEYS es alterado con los siguientes valores (3-4-5).
![Comparación de Inserción]("C:\Users\ASUS\ed\Estructura-de-datos\b_tree\grafico_insertion.png")

## Grafico comparacion Search
Este grafico muestra la comparacion del tiempo que se demora en buscar un valor del archivo .csv en nuestro arbol, cuando la variable MAX_KEYS es alterado con los siguientes valores (3-4-5).

![Comparación de Búsqueda]("C:\Users\ASUS\ed\Estructura-de-datos\b_tree\grafico_search.png")
