#include "csv_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void CSVReader::cargarCanciones(const std::string& filename, ListaReproduccion& listaReproduccion) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo CSV." << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, titulo, artista, anioStr, duracion, popularidadStr;
        getline(ss, id, ',');
        getline(ss, titulo, ',');
        getline(ss, artista, ',');
        getline(ss, anioStr, ',');
        getline(ss, duracion, ',');
        getline(ss, popularidadStr, ',');

        int anio = stoi(anioStr);
        int popularidad = stoi(popularidadStr);

        Cancion nuevaCancion(titulo, artista, anio, popularidad);
        listaReproduccion.agregarCancion(nuevaCancion);
    }

    archivo.close();
}

bool CSVReader::buscarCancionPorTitulo(const std::string& filename, const std::string& titulo, std::string& artista, int& anio, int& popularidad) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo CSV." << endl;
        return false;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, tituloArchivo, artistaArchivo, anioArchivo, duracion, popularidadArchivo;
        getline(ss, id, ',');
        getline(ss, tituloArchivo, ',');
        getline(ss, artistaArchivo, ',');
        getline(ss, anioArchivo, ',');
        getline(ss, duracion, ',');
        getline(ss, popularidadArchivo, ',');

        if (tituloArchivo == titulo) {
            artista = artistaArchivo;
            anio = stoi(anioArchivo);
            popularidad = stoi(popularidadArchivo);
            return true;
        }
    }

    return false;
}
