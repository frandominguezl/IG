#include "malla.h"
#include "cilindro.h"
#include "ply_reader.h"
#include "objrevolucion.h"
#include <cmath>

// Constructor por defecto
Cilindro::Cilindro(){};

// Constructor por parámetros
Cilindro::Cilindro(const int num_instancias_perfil, const float altura, const float radio)
{
	this->num_instancias_perfil = num_instancias_perfil;
	this->altura = altura;
	this->radio = radio;

	this->perfil.push_back(Tupla3f(radio, altura, 0));
	this->perfil.push_back(Tupla3f(radio, 0, 0));

	// Llamamos a crearMalla
	crearMalla(perfil, num_instancias_perfil, true);
}