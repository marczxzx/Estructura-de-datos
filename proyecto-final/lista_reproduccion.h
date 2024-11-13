#ifndef LISTA_REPRODUCCION_H
#define LISTA_REPRODUCCION_H

#include <vector>
#include "cancion.h"

class ListaReproduccion {
private:
    vector<Cancion> canciones;

public:
    void agregarCancion(const Cancion& cancion);
    void mostrarLista();
};

#endif
