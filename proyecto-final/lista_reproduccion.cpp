#include "lista_reproduccion.h"
#include <iostream>

using namespace std;

void ListaReproduccion::agregarCancion(const Cancion& cancion) {
    canciones.push_back(cancion);
    cout << "Canción agregada: " << cancion.titulo << endl;
}

void ListaReproduccion::mostrarLista() {
    if (canciones.empty()) {
        cout << "La lista de reproducción está vacía." << endl;
        return;
    }

    cout << "\n--- Lista de Reproducción ---\n";
    for (const Cancion& cancion : canciones) {
        cancion.mostrarCancion();
    }
}
