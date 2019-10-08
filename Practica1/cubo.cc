#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   // Primer cuadrado
   Tupla3f v1(-lado*50, -lado*50, -50*lado), v2(lado*50, -lado*50, -50*lado), v3(lado*50, lado*50, -50*lado), v4(-lado*50, lado*50, -50*lado);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);

   // Segundo cuadrado
   Tupla3f v5(-lado*50, -lado*50, 50*lado), v6(lado*50, -lado*50, 50*lado), v7(lado*50, lado*50, 50*lado), v8(-lado*50, lado*50, 50*lado);
   v.push_back(v5);
   v.push_back(v6);
   v.push_back(v7);
   v.push_back(v8);

   // inicializar la tabla de caras o triángulos:
   // Cara frontal
   Tupla3i t1(0, 2, 1), t2(0, 3, 2);
   // Cara final
   Tupla3i t3(5, 7, 4), t4(7, 5, 6);
   // Cara derecha
   Tupla3i t5(1, 2, 6), t6(1, 6, 5);
   // Cara izquierda
   Tupla3i t7(0, 4, 3), t8(4, 7, 3);
   // Cara de arriba
   Tupla3i t9(2, 3, 6), t10(3, 7, 6);
   // Cara de abajo
   Tupla3i t11(0, 1, 4), t12(5, 4, 1);

   f.push_back(t3);
   f.push_back(t4);
   f.push_back(t1);
   f.push_back(t2);
   f.push_back(t5);
   f.push_back(t6);
   f.push_back(t7);
   f.push_back(t8);
   f.push_back(t9);
   f.push_back(t10);
   f.push_back(t11);
   f.push_back(t12);

   // inicializar la tabla de colores
   Tupla3f c1(255, 0.0, 0.0), c2(255, 0.0, 0.0), c3(255, 0.0, 0.0), c4(255, 0.0, 0.0),
           c5(255, 0.0, 0.0), c6(255, 0.0, 0.0), c7(255, 0.0, 0.0), c8(255, 0.0, 0.0);
   c.push_back(c1);
   c.push_back(c2);
   c.push_back(c3);
   c.push_back(c4);
   c.push_back(c5);
   c.push_back(c6);
   c.push_back(c7);
   c.push_back(c8);

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}