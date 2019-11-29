#ifndef PLATAFORMA_H_INCLUDED
#define PLATAFORMA_H_INCLUDED

#include "cubo.h"
#include "malla.h"

class Plataforma : public Malla3D
{
    private:
        Cubo* c = nullptr;
    public:
        Plataforma();
};

#endif