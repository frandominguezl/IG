#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cono : public ObjRevolucion
{
public:
	Cono();
	Cono(const int num_instancias_perfil, const float altura, const float radio);
};

#endif