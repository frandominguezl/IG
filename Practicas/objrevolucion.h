// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "textura.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
    public:
        const float PI = 3.14159265;
        int instancias_triangulos = 0;
        Tupla3f tapaInf, tapaSup;
        int M = 0, N = 0;

        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, int ejeRevolucion, bool tapa_sup=true, bool tapa_inf=true, bool conTextura=false) ;
        ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, bool conTextura=false) ;

        // dibuja el objeto en modo inmediato
        // int modoDibujado = (1 = puntos, 2 = lineas, 3 = solido)
        // bool tapas
        void draw_ModoInmediato(int modoDibujado, bool tapas);

        // dibuja en modo ajedrez
        void draw_Chess(bool tapas);

        // dibuja el objeto en modo diferido (usando VBOs)
        // int modoDibujado = (1 = puntos, 2 = lineas, 3 = solido)
        void draw_ModoDiferido(int modoDibujado, bool tapas);

        // Funcion que redibuja el objeto
        // int modoDibujado = (1 = modoInmediato, 2 = modoDiferido, 3 = modoAjedrez)
        // bool puntos = Activa/Desactiva la visualización en puntos
        // bool lineas = Activa/Desactiva la visualización en lineas
        // bool solido = Activa/Desactiva la visualización en solido
        void draw(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas) ;

    protected:
        std::vector<Tupla3f> voltearVertices(const std::vector<Tupla3f> & perfil_original);

        // int ejeRevolucion: 1->x, 2->y, 3->z
        void crearMalla(const std::vector<Tupla3f> & perfil_original, int num_instancias_perf, int ejeRevolucion=0, bool conTextura=false);
        
        // Función para el cálculo de las coordenadas de texturas
        void calcularCoordTextura(const std::vector<Tupla3f> & perfil);
        double distanciaVertices(Tupla3f anterior, Tupla3f siguiente);

        // Gestión de tapas
        void gestionarTapas(std::vector<Tupla3f>& perfil, int eje);

        // Generación de vértices
        void generarVertices(std::vector<Tupla3f>& perfil, int eje);

        // Revolucionar sobre un determinado eje
        std::vector<Tupla3f> revolucionarEnEje(std::vector<Tupla3f>& perfil, int ejeRevolucion);
} ;

#endif
