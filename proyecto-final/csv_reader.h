#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include "lista_reproduccion.h"

class CSVReader {
public:
    static void cargarCanciones(const std::string& filename, ListaReproduccion& listaReproduccion);
    static bool buscarCancionPorTitulo(const std::string& filename, const std::string& titulo, std::string& artista, int& anio, int& popularidad);
};

#endif
