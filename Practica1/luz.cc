#include "luz.h"

// Constructor por defecto
Luz::Luz(){}

// Método activar
void Luz::activar()
{
	glEnable(this->id);
	glLightfv(this->id, GL_DIFFUSE, this->colorDifuso);
	glLightfv(this->id, GL_SPECULAR, this->colorEspecular);
	glLightfv(this->id, GL_AMBIENT, this->colorAmbiente);
	glLightfv(this->id, GL_POSITION, this->posicion);
}