#ifndef PLATAFORMA_H_INCLUDED
#define PLATAFORMA_H_INCLUDED

#include "aux.h"
#include "cubo.h"

class Plataforma : public Malla3D
{
    private:
        Cubo* c = nullptr;
    public:
        Plataforma();
};

#endif