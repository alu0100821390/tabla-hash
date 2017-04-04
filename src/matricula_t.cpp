#include "matricula_t.hpp"

matricula_t::matricula_t (void):
nBusqueda_(0)
{
    for (int i=0; i<7; i++){
        valor_[i] = 0;
    }
}

matricula_t::matricula_t (char *valor):
nBusqueda_(0)
{
    for (int i=0; i<7; i++){
        valor_[i] = valor[i];
    }
}

matricula_t::~matricula_t (void)
{

}

matricula_t::operator unsigned long (void)
{
    unsigned long aux = 0;
    for (int i=0; i<7; i++){
        aux += valor_[i] * (i + 1);
    }

    return aux;
}

bool matricula_t::operator == (const matricula_t &matricula) const
{
    bool iguales = true;
    for (int i=0; i<7; i++){
        if (valor_[i] != matricula.valor_[i]){
            iguales = false;
            i = 7;
        }
    }

    return iguales;
}

void matricula_t::set_nBusqueda (int nBusqueda)
{
    nBusqueda_ = nBusqueda;
}

int matricula_t::get_nBusqueda (void)
{
    return nBusqueda_;
}

ostream& matricula_t::write (ostream& os) const
{
    if (valor_[0] == '\0'){
        os << setw(9) << "N/A";
    }
    else{
        char aux[8];
        for (int i=0; i<8; i++){
            aux[i] = valor_[i];
        }
        os << setw(9) << aux;
    }
    return os;
}
