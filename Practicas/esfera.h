#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion
{
	int num_instancias_perfil;
	float radio;
	std::vector<Tupla3f> perfil;

public:
	Esfera();
	Esfera(const int num_vert_perfil, const int num_instancias_perfil, const float radio);
	void setEjeRevolucion(char eje);
};

#endif