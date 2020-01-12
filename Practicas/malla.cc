#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(int modoDibujado)
{
   // Tabla de vértices
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());

   // Tabla de normales
   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT, 0, nv.data());

   // Tabla de colores
   glEnableClientState(GL_COLOR_ARRAY);
   
   switch(modoDibujado)
   {
      case 1: glColorPointer(3, GL_FLOAT, 0, cPuntos.data()); break;
      case 2: glColorPointer(3, GL_FLOAT, 0, cLineas.data()); break;
      case 3: glColorPointer(3, GL_FLOAT, 0, c.data()); break;
   }

   // Tabla de texturas
   if(!ct.empty() && tex != nullptr){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }

   // Tabla de triángulos
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Malla3D::cambiarColor(float R, float G, float B)
{
   // Vaciamos los vectores de colores
   c.clear();
   cPuntos.clear();
   cLineas.clear();

   // Color para el vector de colores
   Tupla3f color(R, G, B);

   // Colores adicionales para puntos y líneas
   Tupla3f colorPuntos(0, 0.5, 1.0);
   Tupla3f colorLineas(0.5, 0.5, 0);

   for(int i = 0; i < v.size(); i++){
      c.push_back(color);
      cPuntos.push_back(colorPuntos);
      cLineas.push_back(colorLineas);
   }

   c.push_back(color); 
   cLineas.push_back(colorLineas);
   cPuntos.push_back(colorPuntos); 
}

void Malla3D::draw_Chess()
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   
   fpar.resize(f.size()/2);
   fimpar.resize(f.size()/2);

   for(int i=0, j=0; i<f.size(); i+=2, j++){
      fpar[j] = f[i];
      fimpar[j] = f[i+1];
   }

   cimpar.resize(c.size());
   cpar.resize(c.size());

   for(int i=0; i < cpar.size(); i++){
      cpar[i][0] = (1.0);
      cpar[i][1] = (0.0);
      cpar[i][2] = (0.0);

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

void Malla3D::draw_ModoDiferido(int modoDibujado)
{
  if (vbo_v == 0 && vbo_f == 0){
   vbo_v = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(float)*v.size(), v.data());
   vbo_f = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*f.size(), f.data());
  }

   // Array de vértices
   glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f);

   if (vbo_n == 0){
      vbo_n = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(float)*nv.size(), nv.data());
   }

   // Array de normales
   glBindBuffer(GL_ARRAY_BUFFER, vbo_n);
   glNormalPointer(GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_NORMAL_ARRAY);

   // Array de colores
   glEnableClientState(GL_COLOR_ARRAY);

   switch(modoDibujado)
   {
      case 1:
         if(vbo_cp == 0)
            vbo_cp = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(int)*cPuntos.size(), cPuntos.data());
         
         glBindBuffer(GL_ARRAY_BUFFER, vbo_cp);
      break;

      case 2:
         if(vbo_cl == 0)
            vbo_cl = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(int)*cLineas.size(), cLineas.data());
         
         glBindBuffer(GL_ARRAY_BUFFER, vbo_cl);
      break;
      
      case 3:
         if(vbo_c == 0)
            vbo_c = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(int)*c.size(), c.data());
         
         glBindBuffer(GL_ARRAY_BUFFER, vbo_c);
      break;
   }

   // Tabla de texturas
   if(!ct.empty() && tex != nullptr){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }

   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modoDibujado, bool puntos, bool lineas, bool solido)
{ 
   if(mat != nullptr)
      mat->aplicar();

   if(tex != nullptr)
      tex->activar();
   
   if(nv.empty())
      calcular_normales();
   
   if(puntos){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      switch(modoDibujado)
      {
         case 1: draw_ModoInmediato(1); break;
         case 2: draw_ModoDiferido(1); break;
         case 3: draw_Chess(); break;
      }
   }

   if(lineas){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      switch(modoDibujado)
      {
         case 1: draw_ModoInmediato(2); break;
         case 2: draw_ModoDiferido(2); break;
         case 3: draw_Chess(); break;
      }
   }

   if(solido){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      switch(modoDibujado)
      {
         case 1: draw_ModoInmediato(3); break;
         case 2: draw_ModoDiferido(3); break;
         case 3: draw_Chess(); break;
      }
   }
}

// Función para calcular las normales
void Malla3D::calcular_normales()
{
  // Gestionamos las normales de las caras
  for(int i = 0; i < this->f.size(); i++){
    Tupla3f p = v[f[i](0)];
    Tupla3f q = v[f[i](1)];
    Tupla3f r = v[f[i](2)];

    // Las dos aristas resultantes
    Tupla3f a = q-p;
    Tupla3f b = r-p;

    // Vector perpendicular a la cara
    Tupla3f mc = a.cross(b);

    // Normalizamos el vector y lo introducimos
    this->nc.push_back(mc.normalized());
  }

  // Gestionamos las normales de los vértices
  nv = std::vector<Tupla3f>(v.size(), {0, 0, 0});

  for(int i = 0; i < this->f.size(); i++){
    nv[f[i](0)] = (nv[f[i](0)] + nc[i]).normalized();
    nv[f[i](1)] = (nv[f[i](1)] + nc[i]).normalized();
    nv[f[i](2)] = (nv[f[i](2)] + nc[i]).normalized();
  }
}

// Función para establecer el material
void Malla3D::setMaterial(Material m)
{
  mat = new Material(m);
}

// Función para establecer la textura
void Malla3D::setTextura(Textura t)
{
   tex = new Textura(t);
}