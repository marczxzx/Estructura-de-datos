#ifndef CANCION_H
#define CANCION_H

#include <string>
using namespace std;

class Cancion {
public:
    string titulo;
    string artista;
    int anio;
    int popularidad;

    Cancion(string titulo, string artista, int anio, int popularidad)
        : titulo(titulo), artista(artista), anio(anio), popularidad(popularidad) {}
    
    void mostrarCancion() {
        cout << "| Título: " << titulo 
             << " | Artista: " << artista 
             << " | Año: " << anio 
             << " | Popularidad: " << popularidad << " |" << endl;
    }
};

#endif
