#include "b_tree.h"
#include <fstream>
#include <sstream>
#include <chrono> // Incluir la biblioteca para medir el tiempo
#include <iostream>
using namespace std;

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

int main() {
    BTreeNode* root = nullptr;

    string filename = "C:\\Users\\ASUS\\ed\\Estructura-de-datos\\random.csv";


    // Iniciar el cronómetro para la carga
    auto start = chrono::high_resolution_clock::now(); 

    buildTreeFromCSV(root, filename);

    // Detener el cronómetro
    auto end = chrono::high_resolution_clock::now(); 
    chrono::duration<double> elapsed = end - start; // Calcular el tiempo transcurrido

    // Mostrar el tiempo de ejecución de la carga
    cout << "Tiempo de carga: " << elapsed.count() << " segundos." << endl;

    // Valor a buscar (puedes cambiar esto por cualquier llave que desees buscar)
    float keyToSearch = 0.643257; // Cambia esta llave según sea necesario

    // Iniciar el cronómetro para la búsqueda
    auto searchStart = chrono::high_resolution_clock::now(); 

    // Realizar la búsqueda
    bool found = search(root, keyToSearch);

    // Detener el cronómetro
    auto searchEnd = chrono::high_resolution_clock::now(); 
    chrono::duration<double> searchElapsed = searchEnd - searchStart; // Calcular el tiempo de búsqueda

    // Mostrar el resultado de la búsqueda y el tiempo de ejecución
    cout << "La llave " << (found ? "se encontró" : "no se encontró") << " en el árbol." << endl;
    cout << "Tiempo de búsqueda: " << searchElapsed.count() * 1000 << " milisegundos." << endl;

    return 0;
}

