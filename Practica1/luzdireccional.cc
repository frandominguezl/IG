#include "luzdireccional.h"

// Constructor por parámetros
LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
	this->alpha = direccion[0];
	this->beta = direccion[1];

	this->id = idLuzOpenGL;
	this->colorAmbiente = colorAmbiente;
	this->colorEspecular = colorEspecular;
	this->colorDifuso = colorDifuso;

    calcularPosiciones();
    this->posicion[3] = 0;
}

// Variar ángulo alpha
void LuzDireccional::variarAnguloAlpha(float incremento){
	this->alpha += incremento;
    calcularPosiciones();
}

// Variar ángulo beta
void LuzDireccional::variarAnguloBeta(float incremento){
	this->beta += incremento;
    calcularPosiciones();
}

// Variar la posición de los ángulos
void LuzDireccional::calcularPosiciones(){
	this->posicion[0] = sin(alpha*(M_PI/180));
	this->posicion[1] = sin(beta*(M_PI/180));
    this->posicion[2] = cos(alpha*(M_PI/180))*cos(beta*(M_PI/180));
}