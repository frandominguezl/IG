#ifndef EJEROTATORIO_H_INCLUDED
#define EJEROTATORIO_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "aspa.h"

class EjeRotatorio : public Malla3D
{
    private:
        Aspa* aspa1 = nullptr;
        Aspa* aspa2 = nullptr;
        Aspa* aspa3 = nullptr;
        Esfera* esfera = nullptr;
    public:
        EjeRotatorio();
        void draw();
};

#endif