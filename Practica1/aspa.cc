#include "aspa.h"

// Constructor por defecto
Aspa::Aspa()
{
    cilin = new Cilindro(20, 1, 1);
    cono = new Cono(20, 1, 1);
};

// Método draw
void Aspa::draw()
{
    glPushMatrix();
        // Transformaciones y dibujado del cilindro
        glScalef(0.5, 2, 0.5);
        cilindro->draw();

        // Transformaciones y dibujado del cono
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(0, 2, 0);
        cono->draw();
    glPopMatrix();

    draw(this->modoDibujado, this->puntos, this->lineas, this->solido);
}