#ifndef MOLINO_H_INCLUDED
#define MOLINO_H_INCLUDED

#include "aux.h"
#include "cabezal.h"
#include "material.h"

class Molino : public ObjRevolucion
{
    private:
        Cabezal* cabezal = nullptr;
        Cubo* plat = nullptr;
        Cilindro* soporte = nullptr;

        Material * mat = nullptr;

        float rotacionCabezalY = 0.0;
        float rotacionCabezalZ = 0.0;
    public:
        Molino();
        void drawMolino(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas);
        void setAnguloCabezalY(float angulo);
        void setAnguloCabezalZ(float angulo);
        void setMaterial(const Material &m);
        void setRotacionEje(float angulo);
};

#endif