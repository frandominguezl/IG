#ifndef EJEROTATORIO_H_INCLUDED
#define EJEROTATORIO_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "aspa.h"

class EjeRotatorio : public ObjRevolucion
{
    private:
        Aspa* aspa1 = nullptr;
        Aspa* aspa2 = nullptr;
        Aspa* aspa3 = nullptr;
        Esfera* esfera = nullptr;

        Material * mat = nullptr;
    public:
        EjeRotatorio();
        void drawEje(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas);
        void setMaterial(const Material &m);
};

#endif