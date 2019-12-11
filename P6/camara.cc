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
void Camara::girar(float angulo, char eje, int vec)
{
    Tupla3f v_aux, salida;

    if(vec == 0){
        v_aux = {at[0] - eye[0], at[1] - eye[1], at[2] - eye[2]};
        v_aux = v_aux.normalized();
    }

    else{
        v_aux = this->up;
    }

    // Nos gustan más los radianes
    angulo *= (PI/180);

    switch(eje){
        case 'x':
            salida[0] = v_aux[0]*1;
            salida[1] = v_aux[1]*cos(angulo) + v_aux[2]*(-sin(angulo));
            salida[2] = v_aux[1]*sin(angulo) + v_aux[2]*cos(angulo);
        break;

        case 'y':
            salida[0] = v_aux[0]*cos(angulo) + v_aux[2]*sin(angulo);
            salida[1] = v_aux[1]*1;
            salida[2] = v_aux[1]*(-sin(angulo)) + v_aux[2]*cos(angulo);
        break;
    }

    if(vec == 0){
        at[0] = salida[0] + eye[0];
        at[1] = salida[1] + eye[1];
        at[2] = salida[2] + eye[2];
    }

    else{
        this->up = salida;
    }
}

// Rotar en X
void Camara::rotarXExaminar(float angle){};

// Rotar en Y
void Camara::rotarYExaminar(float angle){};

// Rotar en Z
void Camara::rotarZExaminar(float angle){};

// Rotar en X en primera persona
void Camara::rotarXFirstPerson(float angle)
{
    girar(angle, 'x', 0);
    girar(angle, 'x', 1);
}

// Rotar en Y en primera persona
void Camara::rotarYFirstPerson(float angle)
{
    girar(angle, 'y', 0);
    girar(angle, 'y', 1);
}

// Trasladar la cámara
void Camara::mover(float x, float y, float z)
{
    if(x != 0)
        this->eye[0] = x;

    if(y != 0)
        this->eye[1] = y;

    if(z != 0)
        this->eye[2] = z;
}

// Zoom en la escena
void Camara::zoom(float factor)
{
    // Vector dirección
    Tupla3f vd = {at[0] - eye[0], at[1] - eye[1], at[2] - eye[2]};
    vd = vd.normalized();
    vd = vd*factor;

    // Sumamos hacia donde miramos
    eye[0] += vd[0];
    eye[1] += vd[1];
    eye[2] += vd[2];

    // Actualizamos at
    at[0] += vd[0];
    at[1] += vd[1];
    at[2] += vd[2];    
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