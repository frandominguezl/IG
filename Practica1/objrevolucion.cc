#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include <cmath>

static const float PI = 3.14159265;

// Constructor por parámetros
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true)
{
    std::vector<Tupla3f> vertices;
    // Leemos los vértices del archivo
    ply::read_vertices(archivo, vertices);
    crearMalla(vertices, num_instancias, (tapa_sup && tapa_inf));
}

// Constructor por parámetros
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup=true, bool tapa_inf=true)
{
    crearMalla(perfil, num_instancias, (tapa_sup && tapa_inf));
}

// Crear Malla
ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const bool conTapas)
{
    Tupla3f v_aux; // Vértice auxiliar
    int a, b;
    
    // Nos aseguramos de que la tabla de vértices está vacía
    this->v.clear();

    // Generamos la tabla de vértices
    for(int i=0; i < num_instancias_perf; i++){
        for(int j=0; j < perfil_original.size(); j++){
            aux(0) = perfil_original[j](0)*sin((2*PI*i)/num_instancias_perf);
            aux(2) = perfil_original[j](2)*cos((2*PI*i)/num_instancias_perf);
            this->v.push_back(aux);
        }
    }

    // Nos aseguramos de que la tabla de triángulos está vacía
    this->f.clear();

    // Generamos la tabla de triángulos
    for(int i=0; i < num_instancias_perf; i++){
        for(int j=0; j < perfil_original.size()-1; j++){
            a = perfil_original.size()*i + j;
            b = perfil_original.size()*((i+1)%num_instancias_perf) + j;

            // Creamos los triángulos
            Tupla3i t1(a, b, b+1);
            Tupla3i t2(a, b+1, a+1);
            this->f.push_back(t1);
            this->f.push_back(t2);
        }
    }

}