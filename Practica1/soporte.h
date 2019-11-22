#ifndef SOPORTE_H_INCLUDED
#define SOPORTE_H_INCLUDED

#include "aux.h"
#include "cilindro.h"

class Soporte : public Malla3D
{
    private:
        Cilindro* cilin;
    public:
        Soporte();
};

#endif