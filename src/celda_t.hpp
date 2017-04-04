#pragma once

#include <cstdio>
#include <vector>

using namespace std;

template <class Clave>
class celda_t
{
private:
    int nBloques_;
    vector<Clave> vClaves_;

public:
    celda_t (int nBloques):
    nBloques_(nBloques)
    {
        vClaves_.clear();
        vClaves_.resize(nBloques_);
    }

    ~celda_t (void)
    {

    }

    bool buscar (Clave clave)
    {
        bool encontrado = false;
        for (int i=0; i<nBloques_; i++){
            if (vClaves_[i] == clave){
                encontrado = true;
                i = nBloques_;
            }
        }

        return encontrado;
    }

    bool insertar (Clave clave)
    {
        bool insertado = false;
        unsigned long aux;
        for (int i=0; i<nBloques_; i++){
            aux = vClaves_[i];
            if (aux == 0){
                vClaves_[i] = clave;
                insertado = true;
                i = nBloques_;
            }
        }

        return insertado;
    }

    bool lleno ()
    {
        bool lleno = true;
        unsigned long aux;
        for (int i=0; i<nBloques_; i++){
            aux = vClaves_[i];
            if (aux == 0){
                lleno = false;
            }
        }
        return lleno;
    }

    ostream& write (ostream& os) const
    {
        for (int i=0; i<nBloques_; i++){
            vClaves_[i].write(os);
        }
        os << endl;

        return os;
    }
};
