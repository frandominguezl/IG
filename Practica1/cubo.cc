/*
 * Clase Cubo - Informática Gráfica
 * Francisco Domínguez Lorente
 * Práctica 1
*/

#include "cubo.h"

/**
*
*@param
*@returns
*/

_cubo::_cubo(float Size)
{
  Vertices.resize(8);

  Vertices[0]=_vertex3f(-Size/2,-Size/2,0);
  Vertices[1]=_vertex3f(Size/2,-Size/2,0);
  Vertices[2]=_vertex3f(Size/2,Size/2,0);
  Vertices[3]=_vertex3f(-Size/2,Size/2,0);

  Vertices[4]=_vertex3f(-Size/2,-Size/2,-Size);
  Vertices[5]=_vertex3f(Size/2,-Size/2,-Size);
  Vertices[6]=_vertex3f(Size/2,Size/2,-Size);
  Vertices[7]=_vertex3f(-Size/2,Size/2,-Size);

  Triangles.resize(12);

  Triangles[0]=_vertex3ui(0,1,3);
  Triangles[1]=_vertex3ui(1,2,3);
  Triangles[2]=_vertex3ui(4,5,7);
  Triangles[3]=_vertex3ui(5,6,7);
  Triangles[4]=_vertex3ui(0,4,3);
  Triangles[5]=_vertex3ui(3,4,7);
  Triangles[6]=_vertex3ui(1,2,5);
  Triangles[7]=_vertex3ui(2,5,6);
  Triangles[8]=_vertex3ui(2,3,7);
  Triangles[9]=_vertex3ui(2,6,7);
  Triangles[10]=_vertex3ui(0,1,4);
  Triangles[11]=_vertex3ui(1,4,5);

}