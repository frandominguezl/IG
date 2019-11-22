#include "molino.h"

// Constructor por defecto
Molino::Molino()
{
    cabezal = new Cabezal();
    plat = new Plataforma();
    soporte = new Soporte();
};

// Método draw
void Molino::draw()
{
    glPushMatrix();
        // Dibujo el soporte
        soporte->draw();

        // Dibujo la plataforma
        plat->draw();

        // Aplico las transformaciones y dibujo el cabezal
        glTranslatef(0, 5, 0);
        glRotatef(this->rotacionCabezalX, 1, 0, 0);
        glRotatef(this->rotacionCabezalY, 0, 1, 0);
        cabezal->draw();
    glPopMatrix();
    
    draw(this->modoDibujado, this->puntos, this->lineas, this->solido);
}

// Establecer ángulo de rotación del eje Y del cabezal
void Molino::setAnguloCabezalY(float angulo)
{
    this->rotacionCabezalY = angulo;
}

// Establecer ángulo de rotación del eje Y del cabezal
void Molino::setAnguloCabezalX(float angulo)
{
    this->rotacionCabezalX = angulo;
}