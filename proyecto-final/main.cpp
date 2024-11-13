#include <iostream>
#include <string>
#include "csv_reader.h"
#include "lista_reproduccion.h"

using namespace std;

int main() {
    ListaReproduccion listaReproduccion;
    CSVReader::cargarCanciones("spotify_data.csv", listaReproduccion);

    int opcion;
    string titulo;

    do {
        cout << "\n--- Gestor de Lista de Reproducción ---\n";
        cout << "1. Mostrar lista de reproducción\n";
        cout << "2. Agregar canción\n";
        cout << "3. Eliminar canción\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                listaReproduccion.mostrarLista();
                break;
            case 2: {
                cout << "Ingrese el título de la canción a agregar: ";
                cin.ignore();
                getline(cin, titulo);

                string artista;
                int anio, popularidad;

                if (CSVReader::buscarCancionPorTitulo("spotify_data.csv", titulo, artista, anio, popularidad)) {
                    Cancion nuevaCancion(titulo, artista, anio, popularidad);
                    listaReproduccion.agregarCancion(nuevaCancion);
                } else {
                    cout << "La canción '" << titulo << "' no se encuentra en el archivo CSV." << endl;
                }
                break;
            }
            case 3:
                cout << "Funcionalidad de eliminar canción aún no implementada." << endl;
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
