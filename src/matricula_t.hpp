#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class matricula_t
{
private:
    char valor_ [8];
    int nBusqueda_;  // Auxiliar para el estudio. Se incrementa en cada búsqueda dle valor valor_

public:
    matricula_t (void);
    matricula_t (char *valor);
    ~matricula_t (void);

    operator unsigned long (void);
    bool operator == (const matricula_t &matricula) const;

    void set_nBusqueda (int nBusqueda);
    int get_nBusqueda (void);

    ostream& write (ostream& os) const;
};
