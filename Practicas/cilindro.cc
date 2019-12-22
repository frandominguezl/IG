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
	crearMalla(perfil, num_instancias_perfil, 0, true);
}

// Revolucionar entorno a un eje
void Cilindro::setEjeRevolucion(char eje)
{
	switch(eje){
		case 'x': crearMalla(this->perfil, this->num_instancias_perfil, 1, true);
		case 'y': crearMalla(this->perfil, this->num_instancias_perfil, 2, true);
		case 'z': crearMalla(this->perfil, this->num_instancias_perfil, 3, true);
	}
}