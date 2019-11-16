#include "malla.h"
#include "cilindro.h"
#include "ply_reader.h"
#include "objrevolucion.h"

// Constructor por parámetros
Cilindro::Cilindro(){};

Cilindro::Cilindro(const int num_instancias_perfil, const float altura, const float radio)
{
	std::vector<Tupla3f> perfil;
	perfil.push_back(Tupla3f(radio, altura, 0));
	perfil.push_back(Tupla3f(radio, 0, 0));

	// Llamamos a crearMalla
	crearMalla(perfil, num_instancias_perfil);
}