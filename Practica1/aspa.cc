#include "aspa.h"

// Constructor por defecto
Aspa::Aspa()
{
    cilin = new Cilindro(50, 100, 10);
};

// Método draw
void Aspa::drawAspa(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas)
{
    glPushMatrix();
        // Transformaciones y dibujado del cilindro
        glTranslatef(10, 50, 0);
        glScalef(2, 2, 2);
        cilin->cambiarColor(0.6, 0.8, 0.9);
        cilin->draw(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();
}

// Función para establecer el material
void Aspa::setMaterial(const Material &m)
{
  cilin->setMaterial(m);
}