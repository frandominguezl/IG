#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   Tupla3f v1(-lado, -lado, 0.0), v2(lado, -lado, 0.0), v3(lado, lado, 0.0), v4(-lado, lado, 0.0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);

   // inicializar la tabla de caras o triángulos:
   Tupla3i t1(0, 1, 2), t2(0, 2, 3);
   f.push_back(t1);
   f.push_back(t2);

   // inicializar la tabla de colores
   Tupla3f c1(255, 0.0, 0.0), c2(255, 0.0, 0.0), c3(255, 0.0, 0.0), c4(255, 0.0, 0.0);
   c.push_back(c1);
   c.push_back(c2);
   c.push_back(c3);
   c.push_back(c4);

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

