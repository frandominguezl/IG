#include "ejerotatorio.h"

// Constructor por defecto
EjeRotatorio::EjeRotatorio()
{
    aspa1 = new Aspa();
    aspa2 = new Aspa();
    aspa3 = new Aspa();
    esfera = new Esfera(50, 50, 1);
};

// Método draw
void EjeRotatorio::draw()
{
    glPushMatrix();
        // Transformaciones y dibujado de la esfera
        glScalef(0.5, 2, 0.5);
        esfera->draw();

        // Transformaciones y dibujado de la aspa 1
        glTranslatef(0, 1, 0);
        aspa1->draw();

        // Transformaciones y dibujado de la aspa 3
        glTranslatef(0, 1, 0);
        glRotatef(45.0, 1, 0, 0);
        aspa2->draw();

        // Transformaciones y dibujado de la aspa 3
        glTranslatef(0, 1, 0);
        glRotatef(-45.0, 1, 0, 0);
        aspa3->draw();
    glPopMatrix();
    
    draw(this->modoDibujado, this->puntos, this->lineas, this->solido);
}