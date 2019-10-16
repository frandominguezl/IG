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

void Malla3D::cambiarColor(float R, float G, float B)
{
   // Vaciamos el vector de colores
   c.clear();

   for(int i = 0; i < v.size(); i++){
      Tupla3f color(R, G, B);
      c.push_back(color);
   }
}

void Malla3D::draw_Chess()
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   
   for(int i=0; i<f.size(); i+=2){
      fimpar.push_back(f[i]);
      fpar.push_back(f[i+1]);
   }

   glShadeModel(GL_FLAT);

   cimpar.resize(c.size());
   cpar.resize(c.size());

   for(int i=0; i<cpar.size(); ++i){
      cpar[i][0] = (200.0);
      cpar[i][1] = (0.0);
      cpar[i][2] = (0.0);
   }

   for(int i=0; i<cimpar.size();++i){
      cimpar[i](0) = (0.0);
      cimpar[i](1) = (0.0);
      cimpar[i](2) = (0.0);
   }

   glColorPointer(3, GL_FLOAT, 0, cpar.data());
   glDrawElements(GL_TRIANGLES, 3*fpar.size(), GL_UNSIGNED_INT, fpar.data());
   glColorPointer(3, GL_FLOAT, 0, cimpar.data());
   glDrawElements(GL_TRIANGLES, 3*fimpar.size(), GL_UNSIGNED_INT, fimpar.data());
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
  if (vbo_v == 0 && vbo_f == 0){
    vbo_v = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(float)*v.size(), v.data());
    vbo_f = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*f.size(), f.data()); 
  }

   glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, vbo_f);
   glShadeModel(GL_FLAT);
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool modoDiferido, GLenum visual, bool chess)
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

  if(chess){
    draw_Chess();
  }
   
   if(modoDiferido) {
      draw_ModoDiferido();
   }

   else {
      draw_ModoInmediato();
   }
}

