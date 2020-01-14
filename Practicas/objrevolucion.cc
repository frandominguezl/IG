#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <cmath>

// Constructor por defecto
ObjRevolucion::ObjRevolucion(){};

// Constructor por parámetros
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, int ejeRevolucion, bool tapa_sup, bool tapa_inf, bool conTextura)
{
    this->M = archivo.size();
    this->N = num_instancias;

    std::vector<Tupla3f> vertices;
    // Leemos los vértices del archivo
    ply::read_vertices(archivo, vertices);
    
    crearMalla(vertices, num_instancias, ejeRevolucion, conTextura);
}

// Constructor por parámetros
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf, bool conTextura)
{
    this->M = perfil.size();
    this->N = num_instancias;
    crearMalla(perfil, num_instancias, conTextura);
}

std::vector<Tupla3f> ObjRevolucion::voltearVertices(const std::vector<Tupla3f> & perfil_original){
    std::vector<Tupla3f> volteado, aux = perfil_original;
    volteado.reserve(perfil_original.size());

    for(int i=0; i < perfil_original.size(); i++){
        volteado.push_back(aux.back());
        aux.pop_back();
    }

    return volteado;
}

void ObjRevolucion::gestionarTapas(std::vector<Tupla3f>& perfil, int eje)
{
    // ¿Tapa superior?
    if(eje == 2){
        if(perfil[0](0) == 0.0 && perfil[0](1) == 0.0){
            this->tapaSup = perfil[0];
            perfil.erase(perfil.begin());
        }

        else{
            this->tapaSup(0) = 0.0;
            this->tapaSup(1) = perfil[0](1);
            this->tapaSup(2) = 0.0;
        }
    }

    else if(eje == 1){
        if(perfil[0](1) == 0.0 && perfil[0](2) == 0.0){
            this->tapaSup = perfil[0];
            perfil.erase(perfil.begin());
        }

        else{
            this->tapaSup(0) = perfil[0](0);
            this->tapaSup(1) = 0.0;
            this->tapaSup(2) = 0.0;
        }
    }

    else if(eje == 3){
        if(perfil[0](0) == 0.0 && perfil[0](2) == 0.0){
            this->tapaSup = perfil[0];
            perfil.erase(perfil.begin());
        }

        else{
            this->tapaSup(0) = 0.0;
            this->tapaSup(1) = 0.0;
            this->tapaSup(2) = perfil[0](2);
        }
    }

    // ¿Tapa inferior?
    if(eje == 2){
        if(perfil[perfil.size()-1](0) == 0.0 && perfil[perfil.size()-1](1) == 0.0){
            this->tapaInf = perfil[perfil.size()-1];
            perfil.pop_back();
        }

        else{
            this->tapaInf(0) = 0.0;
            this->tapaInf(1) = perfil[perfil.size()-1](1);
            this->tapaInf(2) = 0.0;
        }
    }

    else if(eje == 1){
        if(perfil[perfil.size()-1](1) == 0.0 && perfil[perfil.size()-1](2) == 0.0){
            this->tapaInf = perfil[perfil.size()-1];
            perfil.pop_back();
        }

        else{
            this->tapaInf(0) = perfil[perfil.size()-1](0);
            this->tapaInf(1) = 0.0;
            this->tapaInf(2) = 0.0;
        }
    }

    else if(eje == 3){
        if(perfil[perfil.size()-1](0) == 0.0 && perfil[perfil.size()-1](2) == 0.0){
            this->tapaInf = perfil[perfil.size()-1];
            perfil.pop_back();
        }

        else{
            this->tapaInf(0) = 0.0;
            this->tapaInf(1) = 0.0;
            this->tapaInf(2) = perfil[perfil.size()-1](2);
        }
    }
}

void ObjRevolucion::generarVertices(std::vector<Tupla3f>& perfil, int eje)
{
    Tupla3f v_aux;

    // Eje Y
    if(eje == 2){
        for(int i=0; i < this->N; i++){
            for(int j=0; j < perfil.size(); j++){
                v_aux(0) = perfil[j](0)*cos((2*PI*i)/this->N);
                v_aux(1) = perfil[j](1);
                v_aux(2) = perfil[j](0)*sin((2*PI*i)/this->N);

                this->v.push_back(v_aux);
            }
        }
    }

    // Eje X
    else if(eje == 1){
        for(int i=0; i < this->N; i++){
            for(int j=0; j < perfil.size(); j++){
                v_aux(0) = perfil[j](0);
                v_aux(1) = perfil[j](1)*cos((2*PI*i)/this->N);
                v_aux(2) = perfil[j](1)*sin((2*PI*i)/this->N);

                this->v.push_back(v_aux);
            }
        } 
    }

    // Eje Z
    else if(eje == 3){
        for(int i=0; i < this->N; i++){
            for(int j=0; j < perfil.size(); j++){
                v_aux(0) = perfil[j](0)*sin((2*PI*i)/this->N);
                v_aux(1) = perfil[j](0)*cos((2*PI*i)/this->N);
                v_aux(2) = perfil[j](2);

                this->v.push_back(v_aux);
            }
        }        
    }
}

// Revolucionar sobre un eje
std::vector<Tupla3f> ObjRevolucion::revolucionarEnEje(std::vector<Tupla3f>& perfil, int ejeRevolucion)
{
    std::vector<Tupla3f> resultado;
    Tupla3f v_aux;

    // Eje Y
    if(ejeRevolucion == 2){
        resultado = perfil;
    }

    // Eje X
    else if(ejeRevolucion == 1){
        for(int i = 0; i < perfil.size(); i++){
            v_aux(0) = -perfil[i](1);
            v_aux(1) = perfil[i](0);
            v_aux(2) = 0.0;

            resultado.push_back(v_aux);
        }
    }

    // Eje Z
    else if(ejeRevolucion == 3){
        for(int i = 0; i < perfil.size(); i++){
            v_aux(0) = perfil[i](0);
            v_aux(1) = 0.0;
            v_aux(2) = perfil[i](1);

            resultado.push_back(v_aux);
        }
    }

    return resultado;
}

// Crear Malla
void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, int num_instancias_perf, int ejeRevolucion, bool conTextura)
{
    if(this->M == 0)
        this->M = perfil_original.size();

    if(this->N == 0)
        this->N = num_instancias_perf;

    Tupla3f v_aux; // Vértice auxiliar
    std::vector<Tupla3f> perfil;

    // Volteamos los vértices si están en orden ascendente
    perfil = (perfil_original[0](1) < perfil_original[perfil_original.size()-1](1)) ? voltearVertices(perfil_original) : perfil_original;

    // Revolucionamos en Y por defecto
    if(ejeRevolucion == 0)
        ejeRevolucion = 2;

    // Proyectamos los vértices según el eje indicado
    perfil = revolucionarEnEje(perfil, ejeRevolucion);

    // Nos aseguramos de que la tabla de vértices está vacía
    this->v.clear();

    // Comprobamos si tiene tapas, si es así, las sacamos
    gestionarTapas(perfil, ejeRevolucion);

    // Generamos los vértices
    generarVertices(perfil, ejeRevolucion);
    
    // Una vez generada la tabla de vértices, le añadimos las tapas
    this->v.push_back(tapaSup);
    this->v.push_back(tapaInf);

    // Nos aseguramos de que el vector de triángulos está vacío
    this->f.clear();

    // Generamos la tabla de vértices
    if(conTextura){
        this->v.push_back(perfil[0]);
        //perfil.push_back(perfil[0]);
        calcularCoordTextura(perfil);
    }

    // Generamos la tabla de triángulos
    for(int i=0; i < num_instancias_perf; i++){
        for(int j=0; j < perfil.size()-1; j++){
            int a = perfil.size()*i + j;
            int b = perfil.size()*((i+1)%num_instancias_perf) + j;

            // Creamos los triángulos
            Tupla3i t1(a, b, b+1);
            Tupla3i t2(a, b+1, a+1);

            this->f.push_back(t1);
            this->f.push_back(t2);
        }
    }

    // Una vez generada la tabla de triángulos, le añadimos los triángulos de las tapas
    for(int i=0; i < num_instancias_perf; i++){
        Tupla3i caraSup(perfil.size()*((i+1)%num_instancias_perf), perfil.size()*i, num_instancias_perf*perfil.size());
        this->f.push_back(caraSup);
        this->instancias_triangulos++;
    }

    for(int i=0; i < num_instancias_perf; i++){
        Tupla3i caraInf(num_instancias_perf*perfil.size()+1, perfil.size()*(i+1)-1, perfil.size()*(((i+1)%num_instancias_perf)+1)-1);
        this->f.push_back(caraInf);
        this->instancias_triangulos++;
    }
}

void ObjRevolucion::draw_ModoInmediato(int modoDibujado, bool tapas)
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
    if(tapas){
        glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    }

    else{
        glDrawElements(GL_TRIANGLES, f.size()*3-instancias_triangulos*3, GL_UNSIGNED_INT, f.data());
    }

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ObjRevolucion::draw_ModoDiferido(int modoDibujado, bool tapas)
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
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_COLOR_ARRAY);

   switch(modoDibujado)
   {
      case 1:
         if(vbo_cp == 0)
            vbo_cp = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(int)*cPuntos.size(), cPuntos.data());
         
         glColorPointer(3, GL_FLOAT, 0, cPuntos.data());
      break;

      case 2:
         if(vbo_cl == 0)
            vbo_cl = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(int)*cLineas.size(), cLineas.data());
         
         glColorPointer(3, GL_FLOAT, 0, cLineas.data());
      break;
      
      case 3:
         if(vbo_c == 0)
            vbo_c = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(int)*c.size(), c.data());
         
         glColorPointer(3, GL_FLOAT, 0, c.data());
      break;
   }

   // Tabla de texturas
   if(vbo_tex == 0){
      vbo_tex = CrearVBO(GL_ARRAY_BUFFER, 3*sizeof(float)*ct.size(), ct.data());
   }

   if(!ct.empty() && tex != nullptr){
      glBindBuffer(GL_ARRAY_BUFFER, vbo_tex);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
   }

  if(tapas){
        glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
   }

   else{
        glDrawElements(GL_TRIANGLES, f.size()*3-instancias_triangulos*3, GL_UNSIGNED_INT, 0);
   }

    glBindBuffer(GL_COLOR_ARRAY, 0);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ObjRevolucion::draw_Chess(bool tapas)
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

   if(tapas){
       glDrawElements(GL_TRIANGLES, 3*fpar.size(), GL_UNSIGNED_INT, fpar.data());
   }

   else{
       glDrawElements(GL_TRIANGLES, 3*fpar.size()-(instancias_triangulos/2)*3, GL_UNSIGNED_INT, fpar.data());
   }

   glColorPointer(3, GL_FLOAT, 0, cimpar.data());

    if(tapas){
        glDrawElements(GL_TRIANGLES, 3*fimpar.size(), GL_UNSIGNED_INT, fimpar.data());
    }

    else{
        glDrawElements(GL_TRIANGLES, 3*fimpar.size()-(instancias_triangulos/2)*3, GL_UNSIGNED_INT, fimpar.data());
    }

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

void ObjRevolucion::draw(int modoDibujado, bool puntos, bool lineas, bool solido, bool tapas)
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
            case 1: draw_ModoInmediato(1, tapas); break;
            case 2: draw_ModoDiferido(1, tapas); break;
            case 3: draw_Chess(tapas); break;
        }
    }

    if(lineas){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        switch(modoDibujado)
        {
            case 1: draw_ModoInmediato(2, tapas); break;
            case 2: draw_ModoDiferido(2, tapas); break;
            case 3: draw_Chess(tapas); break;
        }
    }

    if(solido){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        switch(modoDibujado)
        {
            case 1: draw_ModoInmediato(3, tapas); break;
            case 2: draw_ModoDiferido(3, tapas); break;
            case 3: draw_Chess(tapas); break;
        }
    }
}

// Calcular coordenadas de textura
void ObjRevolucion::calcularCoordTextura(const std::vector<Tupla3f> & perfil)
{   
    std::vector<float> distancias;
    std::vector<Tupla2f> aux;
    float s, t;
    distancias.resize(this->M+1);
    distancias.push_back(0);

    // Calculamos las distancias primeramente
    for(int i = 1; i < this->M; i++){
        distancias[i] = distancias[i-1] + distanciaVertices(perfil[i-1], perfil[i]);
    }

    for(float i=0; i < this->N; i++){
        for(float j=0; j < this->M; j++){
            s = i/(this->N-1);
            t = distancias[j]/distancias[this->M-1];

            aux.push_back(Tupla2f(s, t));
        }
    }

    // Metemos los vértices en orden inverso
    for(int i = aux.size(); i > 0; i--)
        this->ct.push_back(aux[i]);
}

// Norma euclídea de dos puntos
double ObjRevolucion::distanciaVertices(Tupla3f anterior, Tupla3f siguiente)
{
    double x, y, z;

    x = pow(anterior[0] - siguiente[0], 2);
    y = pow(anterior[1] - siguiente[1], 2);
    z = pow(anterior[2] - siguiente[2], 2);

    return sqrt(x+y+z);
}