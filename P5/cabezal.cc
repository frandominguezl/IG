#include "cabezal.h"

// Constructor por defecto
Cabezal::Cabezal()
{
    eje = new EjeRotatorio();
    c = new Cubo();
};

// Método draw
void Cabezal::drawCabezal(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas)
{   
    glPushMatrix();
        // Transformaciones y dibujado del cubo
        glScalef(2, 1, 1);
        c->cambiarColor(0.6, 0.8, 0.9);
        c->draw(modoDibujado, puntos, lineas, solido);
    glPopMatrix();

    glPushMatrix();
        // Transformaciones y dibujado del eje rotatorio
        glTranslatef(-150, 0, 0);
        glRotatef(this->anguloRotacion, 1, 0, 0);
        eje->drawEje(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();
}

// Establecer ángulo de rotación del eje
void Cabezal::setAngulo(float anguloRotacion)
{
    this->anguloRotacion = anguloRotacion;
}

// Función para establecer el material
void Cabezal::setMaterial(const Material &m)
{
  eje->setMaterial(m);
  c->setMaterial(m);
}