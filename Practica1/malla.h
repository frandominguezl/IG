// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   // int modoDibujado = (1 = puntos, 2 = lineas, 3 = solido)
   void draw_ModoInmediato(int modoDibujado);

   // dibuja en modo ajedrez
   void draw_Chess();

   // dibuja el objeto en modo diferido (usando VBOs)
   // int modoDibujado = (1 = puntos, 2 = lineas, 3 = solido)
   void draw_ModoDiferido(int modoDibujado);

   // Cambiar el color
   void cambiarColor(float R, float G, float B);

   // Funcion que redibuja el objeto
   // int modoDibujado = (1 = modoInmediato, 2 = modoDiferido, 3 = modoAjedrez)
   // bool puntos = Activa/Desactiva la visualización en puntos
   // bool lineas = Activa/Desactiva la visualización en lineas
   // bool solido = Activa/Desactiva la visualización en solido
   virtual void draw(int modoDibujado, bool puntos, bool lineas, bool solido);

   // Establecer material
   void setMaterial(Material m);

   protected:

   // Visualización en Modo Diferido (VBO)
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tam_bytes, GLvoid* puntero_ram);

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f, fimpar, fpar ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c, cimpar, cpar ;  // terna para los colores
   std::vector<Tupla3f> cPuntos, cLineas; // Coloeres para diferentes modos de visualización
   std::vector<Tupla3f> nv; // Vector de normales de los vértices
   std::vector<Tupla3f> nc; // Vector de normales de las caras

   // Material
   Material * mat = nullptr;

   // Variables para visualización en Modo Diferido
   GLuint vbo_f = 0, vbo_v = 0, vbo_c = 0, vbo_n = 0, vbo_cp = 0, vbo_cl = 0;

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
