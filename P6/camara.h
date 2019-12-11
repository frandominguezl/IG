#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
    const float PI = 3.14159265;
    
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;

        // 0 = ortogonal, 1 = perspectiva
        int tipo; 
        float fovY, aspect, near, far;
    
    public:
        Camara();
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float fovY, float aspect, float near, float far);
        void girar(float angulo, char eje, int vec);
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);
        void rotarZExaminar(float angle);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        void mover(float x, float y, float z);
        void zoom(float factor);
        void setObserver();
        void setProyeccion();
};

#endif