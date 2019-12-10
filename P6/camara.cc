#include "camara.h"

// Constructor por defecto
Camara::Camara(){};

// Constructor por parámetros
Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float fovY, float aspect, float near, float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up.normalized();
    this->tipo = tipo;
    this->fovY = fovY;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}

// Girar cámara con ratón
void Camara::girar(int x, int y, int z)
{
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    glRotatef(z, 0, 0, 1);
}

// Rotar en X
void Camara::rotarXExaminar(float angle){};

// Rotar en Y
void Camara::rotarYExaminar(float angle){};

// Rotar en Z
void Camara::rotarZExaminar(float angle){};

// Rotar en X en primera persona
void Camara::rotarXFirstPerson(float angle){};

// Rotar en Y en primera persona
void Camara::rotarYFirstPerson(float angle){};

// Trasladar la cámara
void Camara::mover(float x, float y, float z)
{
    this->eye = {x, y, z};
}

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
    if(tipo == 1)
        gluPerspective(fovY, aspect, near, far);
}