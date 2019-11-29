#include "aspa.h"

// Constructor por defecto
Aspa::Aspa()
{
    cilin = new Cilindro(50, 100, 10);
    cono = new Cono(20, 1, 1);
};

// Método draw
void Aspa::drawAspa(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas)
{
    glPushMatrix();
        // Transformaciones y dibujado del cilindro
        glTranslatef(10, 50, 0);
        glScalef(2, 2, 2);
        cilin->cambiarColor(1.0, 0, 0);
        cilin->draw(modoDibujado, puntos, lineas, solido, tapas);

        // Transformaciones y dibujado del cono
        /*glScalef(0.5, 0.5, 0.5);
        glTranslatef(0, 2, 0);
        cono->cambiarColor(1.0, 0, 0);
        cono->draw(modoDibujado, puntos, lineas, solido, tapas);*/
    glPopMatrix();
}

// Función para establecer el material
void Aspa::setMaterial(const Material &m)
{
  cilin->setMaterial(m);
  //cono->setMaterial(m);
}