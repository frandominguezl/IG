#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, c.data());
  glShadeModel(GL_FLAT);
  glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tam_bytes, GLvoid* puntero_ram)
{
   GLuint id_vbo;
   glGenBuffers(1, &id_vbo);
   glBindBuffer(tipo_vbo, id_vbo);
   glBufferData(tipo_vbo, tam_bytes, puntero_ram, GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo, 0);

   return id_vbo;
}

void Malla3D::draw_ModoDiferido()
{
   glBindBuffer(GL_ARRAY_BUFFER, CrearVBO(GL_ARRAY_BUFFER, v.size(), v.data()));
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, CrearVBO(GL_ARRAY_BUFFER, v.size(), v.data()));
   glShadeModel(GL_FLAT);
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool modoDiferido, GLenum visual)
{
  switch(visual){
    case GL_FILL:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;

    case GL_POINT:
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      break;

    case GL_LINE:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
  }
   
   if(modoDiferido) {
      draw_ModoDiferido();
   }

   else {
      draw_ModoInmediato();
   }
}

