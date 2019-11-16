#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
public:
	Cilindro();
	Cilindro(const int num_instancias_perfil, const float altura, const float radio);
};

#endif