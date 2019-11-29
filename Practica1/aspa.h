#ifndef ASPA_H_INCLUDED
#define ASPA_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "cono.h"

class Aspa : public ObjRevolucion
{
    private:
        Cilindro* cilin = nullptr;
        Cono* cono = nullptr;
        
        Material * mat = nullptr;
    public:
        Aspa();
        void drawAspa(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas);
        void setMaterial(const Material &m);
};

#endif