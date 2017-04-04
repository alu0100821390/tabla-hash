#include <climits>
#include <vector>
#include <ctime>

#include "../src/matricula_t.hpp"
#include "../src/celda_t.hpp"
#include "../src/hash_table_t.hpp"

using namespace std;


struct data_base {
    int size_;
    vector<matricula_t> vMatriculas_;
} banco_pruebas;


int main (void)
{
    cout << endl;

    srand(time(NULL));

    // Datos a introducir //
    /////////////////////////////////////////////////
    // int nCeldas = 25;
    // int nBloques = 2;
    // Dispersion fdispersion = pseudo_aleatoria;
    // Exploracion fexploracion = lineal;
    // double factor = 0.6;
    // int nPruebas = 40;
    /////////////////////////////////////////////////

    // Se pide los datos por teclado //

    int nCeldas, nBloques, nPruebas;
    double factor;
    Dispersion fdispersion;
    Exploracion fexploracion;

    cout << "Numero de celdas: ";
    cin >> nCeldas;
    cout << "Numero de bloques: ";
    cin >> nBloques;
    int disp_aux = 0;
    while ((disp_aux<1) || (disp_aux>3)){
        cout << "Tipo de dispersion (1.Modulo, 2.Suma, 3.Pseudoaleatoria): ";
        cin >> disp_aux;
    }
    switch (disp_aux){
        case 1:
            fdispersion = modulo;
            break;
        case 2:
            fdispersion = suma;
            break;
        case 3:
            fdispersion = pseudo_aleatoria;
            break;
    }
    int expl_aux = 0;
    while ((expl_aux<1) || (expl_aux>4)){
        cout << "Tipo de exploracion (1.Lineal, 2.Cuadratica, 3.Doble, 4.Re-dispersion): ";
        cin >> expl_aux;
    }
    switch (expl_aux){
        case 1:
            fexploracion = lineal;
            break;
        case 2:
            fexploracion = cuadratica;
            break;
        case 3:
            fexploracion = doble;
            break;
        case 4:
            fexploracion = redispersion;
            break;
    }
    cout << "Factor de carga: ";
    cin >> factor;
    cout << "Numero de pruebas: ";
    cin >> nPruebas;


    int N = factor * nCeldas * nBloques;

    if (nPruebas>N){
        nPruebas = N;
        cerr << "El numero de pruebas ha sido reducido por ser demasiado alto." << endl;
    }

    banco_pruebas.size_ = 4 * N;
    banco_pruebas.vMatriculas_.clear();
    banco_pruebas.vMatriculas_.resize(banco_pruebas.size_);

    char matricula[8];
    for (int i=0; i<banco_pruebas.size_; i++){
        if ((rand() % 1) == 1){
            for (int j=0; j<4; j++){
                matricula[j] = rand() % 10 + 48;
            }
            for (int j=4; j<7; j++){
                matricula[j] = rand() % 26 + 65;
            }
        }
        else{
            for (int j=0; j<2; j++){
                matricula[j] = rand() % 26 + 65;
            }
            for (int j=2; j<6; j++){
                matricula[j] = rand() % 10 + 48;
            }
            for (int j=6; j<8; j++){
                matricula[j] = rand() % 26 + 65;
            }
        }
        matricula_t aux(matricula);
        banco_pruebas.vMatriculas_[i] = aux;
    }


    hash_table_t<matricula_t> hash(nCeldas, nBloques, fdispersion, fexploracion);

    for (int i=0; i<N; i++){
        hash.insertar(banco_pruebas.vMatriculas_[i]);
    }

    int minimo = INT_MAX;
    int medio = 0;
    int maximo = -1;
    int contador;

    for (int i=0; i<nPruebas; i++){
        hash.buscar(banco_pruebas.vMatriculas_[i]);
        contador = banco_pruebas.vMatriculas_[i].get_nBusqueda();
        medio += contador;
        if (contador < minimo){
            minimo = contador;
        }
        if (contador > maximo){
            maximo = contador;
        }
    }
    medio = medio / nPruebas;

    cout << "\nNUMERO DE COMPARACIONES\n" << endl;
    cout << "--- Busquedas ---" << endl;
    cout << "Minimo: " << minimo << endl;
    cout << "Medio: " << medio << endl;
    cout << "Maximo: " << maximo << endl;


    minimo = INT_MAX;
    medio = 0;
    maximo = -1;

    for (int i=banco_pruebas.size_-1; i>=banco_pruebas.size_-nPruebas; i--){
        hash.buscar(banco_pruebas.vMatriculas_[i]);
        contador = banco_pruebas.vMatriculas_[i].get_nBusqueda();
        medio += contador;
        if (contador < minimo){
            minimo = contador;
        }
        if (contador > maximo){
            maximo = contador;
        }
    }
    medio = medio / nPruebas;

    cout << "--- Inserciones ---" << endl;
    cout << "Minimo: " << minimo << endl;
    cout << "Medio: " << medio << endl;
    cout << "Maximo: " << maximo << endl;


    cout << endl;
    return 0;
}
