#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion
{
public:
	Esfera();
	Esfera(const int num_vert_perfil, const int num_instancias_perfil, const float radio);
};

#endif