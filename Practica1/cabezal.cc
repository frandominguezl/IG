#include "cabezal.h"

// Constructor por defecto
Cabezal::Cabezal()
{
    eje = new EjeRotatorio();
    c = new Cubo();
};

// Método draw
void Cabezal::draw()
{
    glPushMatrix();
        // Transformaciones y dibujado del cubo
        glScalef(2, 1, 1);
        c->draw();

        // Transformaciones y dibujado del eje rotatorio
        glTranslatef(1, 5, 0);
        glRotatef(this->anguloRotacion, 1, 0, 0);
        eje->draw();
    glPopMatrix();
    
    draw(this->modoDibujado, this->puntos, this->lineas, this->solido);
}

// Establecer ángulo de rotación del eje
void Cabezal::setAngulo(float anguloRotacion)
{
    this->anguloRotacion = anguloRotacion;
}