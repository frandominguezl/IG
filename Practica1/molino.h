#ifndef MOLINO_H_INCLUDED
#define MOLINO_H_INCLUDED

#include "aux.h"
#include "cabezal.h"
#include "soporte.h"
#include "plataforma.h"

class Molino : public Malla3D
{
    private:
        Cabezal* cabezal = nullptr;
        Plataforma* plat = nullptr;
        Soporte* soporte = nullptr;
        float rotacionCabezalY = 0.0;
        float rotacionCabezalX = 0.0;
    public:
        Molino();
        void draw();
        void setAnguloCabezalY(float angulo);
        void setAnguloCabezalX(float angulo);
};

#endif