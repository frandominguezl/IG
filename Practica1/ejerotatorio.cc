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
void EjeRotatorio::drawEje(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas)
{
    glPushMatrix();
        // Transformaciones y dibujado de la esfera
        glScalef(75, 75, 75);
        esfera->cambiarColor(1.0, 0, 0);
        esfera->draw(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();

    glPushMatrix();
        // Transformaciones y dibujado de la aspa 1
        aspa1->cambiarColor(1.0, 0, 0);
        aspa1->drawAspa(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();

    glPushMatrix();
        // Transformaciones y dibujado de la aspa 3
        glRotatef(230.0, 1, 0, 0);
        aspa2->cambiarColor(1.0, 0, 0);
        aspa2->drawAspa(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();

    glPushMatrix();
        // Transformaciones y dibujado de la aspa 3
        glRotatef(-230.0, 1, 0, 0);
        aspa3->cambiarColor(1.0, 0, 0);
        aspa3->drawAspa(modoDibujado, puntos, lineas, solido, tapas);
    glPopMatrix();
}

// Función para establecer el material
void EjeRotatorio::setMaterial(const Material &m)
{
  aspa1->setMaterial(m);
  aspa2->setMaterial(m);
  aspa3->setMaterial(m);
  esfera->setMaterial(m);
}