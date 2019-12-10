#include "material.h"

// Constructor por defecto
Material::Material(){}

// Constructor por parámetros
Material::Material(Tupla4f difuso, Tupla4f especular, Tupla4f ambiente, float brillo)
{
	this->difuso = difuso;
	this->especular = especular;
	this->ambiente = ambiente;
	this->brillo = brillo;
}

// Método aplicar
void Material::aplicar()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->especular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambiente);
	glMaterialf(GL_FRONT, GL_SHININESS, this->brillo);
}