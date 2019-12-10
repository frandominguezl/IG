#include "malla.h"
#include "esfera.h"
#include "ply_reader.h"
#include "objrevolucion.h"

// Constructor por parámetros
Esfera::Esfera(){};

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perfil, const float radio)
{
	std::vector<Tupla3f> perfil;
	
    for(int i=0; i < num_vert_perfil; i++){
        Tupla3f aux;
        aux(0) = cos((PI/2) + i*PI/num_vert_perfil) * radio;
        aux(1) = sin((PI/2) + i*PI/num_vert_perfil) * radio;
        aux(2) = 0.0;

        perfil.push_back(aux);
    }

	// Llamamos a crearMalla
	crearMalla(perfil, num_instancias_perfil);
}