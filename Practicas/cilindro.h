#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
	int num_instancias_perfil;
	float altura;
	float radio;
	std::vector<Tupla3f> perfil;

public:
	Cilindro();
	Cilindro(const int num_instancias_perfil, const float altura, const float radio);
	void setEjeRevolucion(char eje);
};

#endif