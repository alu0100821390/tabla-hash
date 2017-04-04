#pragma once

#include <cstdio>
#include <vector>

#include "celda_t.hpp"

using namespace std;

bool es_primo (int n)
{
    bool primo = true;

    if ((n % 2) == 0){
        primo = false;
    }
    else{
        int aux = 3;
        while ((primo) && (aux>2) && (aux<n)){
            if ((n % aux) == 0){
                primo = false;
            }
            aux += 2;
        }
    }
}

enum Dispersion { modulo, suma, pseudo_aleatoria };
enum Exploracion { lineal, cuadratica, doble, redispersion };

template <class Clave>
class hash_table_t
{
private:
    int nCeldas_;
    int nBloques_;
    vector<celda_t<Clave> > vCeldas_;
    Dispersion fdispersion_;
    Exploracion fexploracion_;

public:
    hash_table_t (int nCeldas, int nBloques, Dispersion fdispersion, Exploracion fexploracion):
    nCeldas_(nCeldas),
    nBloques_(nBloques),
    fdispersion_(fdispersion),
    fexploracion_(fexploracion)
    {
        vCeldas_.clear();
        vCeldas_.resize(nCeldas_, celda_t<Clave>(nBloques_));
    }

    ~hash_table_t (void)
    {

    }

    bool buscar (Clave &clave)
    {
        clave.set_nBusqueda(1);
        bool encontrado = false;

        int pos_disp = func_dispersion(clave);
        if (vCeldas_[pos_disp].buscar(clave)){
            encontrado = true;
        }
        else{
            int intento = 2;
            int despl;
            int dir_expl;
            while ((intento<=nCeldas_) && (!encontrado)){
                clave.set_nBusqueda(intento);
                despl = func_exploracion(clave, intento);
                dir_expl = (pos_disp + despl) % nCeldas_;
                if (vCeldas_[dir_expl].buscar(clave)){
                    encontrado = true;
                }
                else{
                    if (!vCeldas_[dir_expl].lleno()){
                        intento = nCeldas_+1;
                    }
                }
                intento ++;
            }
        }

        return encontrado;
    }

    bool insertar (Clave clave)
    {
        bool insertado = false;

        int pos_disp = func_dispersion(clave);
        if (vCeldas_[pos_disp].insertar(clave)){
            insertado = true;
        }
        else{
            int intento = 2;
            int pos_expl;
            int dir_expl;
            while ((intento<=nCeldas_) && (!insertado)){
                pos_expl = func_exploracion(clave, intento);
                dir_expl = (pos_disp + pos_expl) % nCeldas_;
                if (vCeldas_[dir_expl].insertar(clave)){
                    insertado = true;
                }
                intento ++;
            }
        }

        return insertado;
    }

    int disp_modulo (Clave clave)
    {
        int disp = clave;

        return clave % nCeldas_;
    }

    int disp_suma (Clave clave)
    {
        int suma = clave;
        suma = suma % nCeldas_;

        return suma;
    }

    int disp_pseudo_aleatoria (Clave clave)
    {
        int aux = clave;
        srand(aux);

        return rand() % nCeldas_;
    }

    int func_dispersion (Clave clave)
    {
        int pos;
        switch (fdispersion_){
            case modulo:
                pos = disp_modulo(clave);
                break;
            case suma:
                pos = disp_suma(clave);
                break;
            case pseudo_aleatoria:
                pos = disp_pseudo_aleatoria(clave);
                break;
        }

        return pos;
    }

    int expl_lineal (Clave clave, int intento)
    {
        return intento;
    }

    int expl_cuadratica (Clave clave, int intento)
    {
        return intento * intento;
    }

    int expl_doble (Clave clave, int intento)
    {
        int disp;

        int primo = -1;
        int aux = nCeldas_ - 1;
        while ((primo == -1) && (aux > 0)){
            if (es_primo(aux)){
                primo = aux;
            }
            aux --;
        }

        disp = ((primo - (clave % primo)) * intento) % nCeldas_;

        return disp;
    }

    int expl_redispersion (Clave clave, int intento)
    {
        int disp;

        vector<bool> visitado;
        visitado.clear();
        visitado.resize(nCeldas_, false);
        int aux = clave;
        srand(aux);

        for (int i=0; i<intento; i++){
            disp = rand();
            disp = disp % nCeldas_;
            while (visitado[disp]){
                disp = rand();
                disp = disp % nCeldas_;
            }
            visitado[disp] = true;
        }

        return disp;
    }

    int func_exploracion (Clave clave, int intento)
    {
        int despl;
        switch (fexploracion_){
            case lineal:
                despl = expl_lineal(clave, intento);
                break;
            case cuadratica:
                despl = expl_cuadratica(clave, intento);
                break;
            case doble:
                despl = expl_doble(clave, intento);
                break;
            case redispersion:
                despl = expl_redispersion(clave, intento);
                break;
        }

        return despl;
    }

    ostream& write (ostream& os) const{
        os << "TABLA";
        for (int i=0; i<nBloques_; i++){
            os << setw(9) << i;
        }
        os << endl;
        for (int i=0; i<nCeldas_; i++){
            os << i << " --> ";
            vCeldas_[i].write(os);
        }

        return os;
    }
};
