#include "molino.h"

// Constructor por defecto
Molino::Molino()
{
    cabezal = new Cabezal();
    plat = new Cubo();
    soporte = new Cilindro(50, 50, 10);
    
};

// Método draw
void Molino::drawMolino(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas)
{

    glPushMatrix();
        // Dibujo el soporte
        soporte->cambiarColor(1.0, 0, 0);
        soporte->draw(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();

    glPushMatrix();
        // Dibujo la plataforma
        glScalef(1, 0.1, 1);
        plat->cambiarColor(0.2, 1, 0);
        plat->draw(modoDibujado, puntos, lineas, solido);
    glPopMatrix();

    glPushMatrix();
        // Aplico las transformaciones y dibujo el cabezal
        glTranslatef(0, 50, 0);
        glScalef(0.20, 0.20, 0.20);
        glRotatef(this->rotacionCabezalZ, 0, 0, 1);
        glRotatef(this->rotacionCabezalY, 0, 1, 0);
        cabezal->drawCabezal(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();
}

// Establecer ángulo de rotación del eje Y del cabezal
void Molino::setAnguloCabezalY(float angulo)
{
    this->rotacionCabezalY = angulo;
}

// Establecer ángulo de rotación del eje Y del cabezal
void Molino::setAnguloCabezalZ(float angulo)
{
    this->rotacionCabezalZ = angulo;
}

// Establecer ángulo de rotación para el eje rotatorio
void Molino::setRotacionEje(float angulo){
    cabezal->setAngulo(angulo);
}

// Función para establecer el material
void Molino::setMaterial(const Material &m)
{
  soporte->setMaterial(m);
  plat->setMaterial(m);
  cabezal->setMaterial(m);
}