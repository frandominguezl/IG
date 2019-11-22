#ifndef ASPA_H_INCLUDED
#define ASPA_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "cono.h"

class Aspa : public Malla3D
{
    private:
        Cilindro* cilin = nullptr;
        Cono* cono = nullptr;
    public:
        Aspa();
        void draw();
};

#endif