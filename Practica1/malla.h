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

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja en modo ajedrez
   void draw_Chess();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   // modoDiferido == true -> se llama a draw_ModoDiferido()
   // modoDiferido == false -> se llama a draw_ModoInmediato()
   // modo visualizacion
   void draw(bool modoDiferido, GLenum visual, bool chess) ;

   protected:

   // Visualización en Modo Diferido (VBO)
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tam_bytes, GLvoid* puntero_ram);

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f, fimpar, fpar ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c, cimpar, cpar ;  // terna para los colores

   GLuint vbo_f = 0, vbo_v = 0;

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
