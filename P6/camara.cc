#include "camara.h"

// Constructor por defecto
Camara::Camara(){};

// Constructor por parámetros
Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float fovY, float aspect, float near, float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up;
    this->tipo = tipo;
    this->fovY = fovY;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}

void Camara::rotarXExaminar(float angle){};
void Camara::rotarYExaminar(float angle){};
void Camara::rotarZExaminar(float angle){};
void Camara::rotarXFirstPerson(float angle){};
void Camara::rotarYFirstPerson(float angle){};
void Camara::rotarZFirstPerson(float angle){};
void Camara::mover(float x, float y, float z){};

// Zoom en la escena
void Camara::zoom(float factor)
{
    this->aspect *= factor;
    this->near *= factor;
    this->far *= factor;
}

// Observador de la escena
void Camara::setObserver()
{
    gluLookAt(eye[0], eye[1], eye[2],
               at[0], at[1], at[2],
               up[0], up[1], up[2]);
}

// Proyección de la escena
void Camara::setProyeccion()
{
    gluPerspective(fovY, aspect, near, far);
}