#include "luzposicional.h"

// Constructor por parámetros
LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
	this->id = idLuzOpenGL;

	this->colorAmbiente = colorAmbiente;
	this->colorEspecular = colorEspecular;
	this->colorDifuso = colorDifuso;
    
	this->posicion[0] = posicion[0];
	this->posicion[1] = posicion[1];
	this->posicion[2] = posicion[2];
	this->posicion[3] = 1;
}