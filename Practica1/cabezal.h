#ifndef CABEZAL_H_INCLUDED
#define CABEZAL_H_INCLUDED

#include "aux.h"
#include "ejerotatorio.h"
#include "cubo.h"

class Cabezal : public Malla3D
{
    private:
        EjeRotatorio* eje = nullptr;
        Cubo* c = nullptr;
        float anguloRotacion = 0.0;
    public:
        Cabezal();
        void draw();
        void setAngulo(float anguloRotacion);
};

#endif