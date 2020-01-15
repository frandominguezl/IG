

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;

   ejes.changeAxisSize( 5000 );

   // Cargamos los bjetos PLY
   ply1 = new ObjPLY("plys/ant.ply");

   // Cargamos objetos de revolución
   peon1 = new ObjRevolucion("plys/peon.ply", 20, 0);
   peon2 = new ObjRevolucion("plys/peon.ply", 20, 0);
   peon3 = new ObjRevolucion("plys/peon.ply", 20, 0);
   peon4 = new ObjRevolucion("plys/peon.ply", 20, 0);
   cilindro1 = new Cilindro(50, 50, 10);
   cono1 = new Cono(50, 30, 10);
   esfera1 = new Esfera(50, 50, 10);

   // Cargamos los objetos básicos
   cubo = new Cubo();
   tetraedro = new Tetraedro();
   cuadro = new Cuadro();
   suelo = new Cuadro();

   // Modelo Jerárquico
   mol = new Molino();

   // Luces
   cuadroLuces[0] = new LuzPosicional({0, 0, 0}, GL_LIGHT1, {0.2, 0.2, 0.2, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
   cuadroLuces[1] = new LuzDireccional({0, 0}, GL_LIGHT2, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   // Cámaras
   cuadroCamaras[0] = new Camara({0, 0, 600}, {0, 0, 0}, {0, 1, 0}, 1, 50, 50);
   cuadroCamaras[1] = new Camara({-300, 200, 600}, {0, 0, 0}, {0, 1, 0}, 0, 300, 300);
   cuadroCamaras[2] = new Camara({600, 200, 600}, {0, 0, 0}, {0, 1, 0}, 0, 600, 600);

   // Materiales
   Tupla4f ambiente1(0.135, 0.2225, 0.1575, 0.1), especular1(0.0, 0.0, 0.0, 0.1), difuso1(0.786, 0.89, 0.97, 0.1);
   Tupla4f ambiente2(0.0215,	0.1745, 0.0215, 0.6), especular2(0.7038, 0.27048, 0.0828, 0.6), difuso2(0.0, 0.0, 0.0, 0.6);
   Tupla4f ambiente3(0.0, 0.05, 0.0, 0.078125), especular3(0.04, 0.7, 0.04, 0.078125), difuso3(0.4, 0.5, 0.4, 0.078125);

   Material mat1(difuso1, especular1, ambiente1, 0.1*128.0);
   Material mat2(difuso2, especular2, ambiente2, 0.01*128.0);
   Material mat3(difuso3, especular3, ambiente3, 0.6*128.0);
   peon1->setMaterial(mat1);
   peon2->setMaterial(mat2);
   peon3->setMaterial(mat3);
   peon4->setMaterial(mat1);
   ply1->setMaterial(mat1);
   cubo->setMaterial(mat1);
   tetraedro->setMaterial(mat2);
   cilindro1->setMaterial(mat3);
   esfera1->setMaterial(mat3);
   cono1->setMaterial(mat1);
   mol->setMaterial(mat3);
   cuadro->setMaterial(mat1);
   suelo->setMaterial(mat1);

   // Texturas
   tex1 = Textura("img/text-madera.jpg", 1);
   tex2 = Textura("img/maxresdefault.jpg", 2);
   tex3 = Textura("img/text-lata-1.jpg", 3);
   tex4 = Textura("img/mundo.jpg", 4);
   tex5 = Textura("img/pacman.jpg", 5);
   cuadro->setTextura(tex2);
   cuadro->setCoordenadas();
   cubo->setTextura(tex1);
   cubo->setCoordenadas();
   cilindro1->setTextura(tex3);
   suelo->setTextura(tex5);
   suelo->setCoordenadas();
}

/* Dibujando la escena */
void Escena::creacionEscena()
{
   glPushMatrix();
      glEnable(GL_TEXTURE_2D);

      glPushMatrix();
         glTranslatef(-350, 650, -500);
         cuadro->setPosicion({-350, 650, -500});
         glScalef(8, 8, 8);
         glRotatef(-90, 0, 0, 1);
         cuadro->draw(modoDibujado, puntos, lineas, solido);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(-350, -100, -375);
         glRotatef(-90, 1, 0, 0);
         glRotatef(-90, 0, 0, 1);
         glScalef(8, 8, 8);
         suelo->draw(modoDibujado, puntos, lineas, solido);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(50, -70, -250);
         cubo->setPosicion({50, -70, -250});
         glScalef(0.5, 0.5, 0.5);
         cubo->draw(modoDibujado, puntos, lineas, solido);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(-200, -30, -100);
         cilindro1->setPosicion({-200, -30, -100});
         glScalef(3,3,3);
         cilindro1->draw(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();

      glDisable(GL_TEXTURE_2D);

      glPushMatrix();
         glTranslatef(-70, -50, 0);
         esfera1->setPosicion({0, -50, 0});
         glScalef(5,5,5);
         glRotatef(180, 1, 0, 0);
         esfera1->draw(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(145, -90, -250);
         glScalef(1.3, 1.3, 1.3);
         mol->drawMolino(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(-200, -60, -100);
         glScalef(0.65, 0.65, 0.65);
         tetraedro->setPosicion({-200, -60, -100});
         tetraedro->draw(modoDibujado, puntos, lineas, solido);
      glPopMatrix();
      
      glPushMatrix();
         glTranslatef(70, -50, 0);
         peon1->setPosicion({0, -50, 0});
         glScalef(25.0, 25.0, 25.0);
         peon1->draw(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(140, -50, 0);
         peon3->setPosicion({140, -50, 0});
         glScalef(25.0, 25.0, 25.0);
         peon3->draw(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();

      glPushMatrix();
         glRotatef(-20, 0, 1, 0);
         glTranslatef(-50, -70, 250);
         ply1->setPosicion({-50, -70, 250});
         glScalef(3,3,3);
         ply1->draw(modoDibujado, puntos, lineas, solido);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(210, -50, 0);
         peon2->setPosicion({210, -50, 0});
         glScalef(25, 25, 25);
         peon2->draw(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(280, -50, 0);
         peon4->setPosicion({280, -50, 0});
         glScalef(25, 25, 25);
         peon4->draw(modoDibujado, puntos, lineas, solido, tapas);
      glPopMatrix();
   glPopMatrix();
}

/* Parpadeo de los objetos seleccionables */
void Escena::parpadeo()
{
   Tupla3f actual = esfera1->getColor();
   Tupla3f actualT = tetraedro->getColor();

   /* Variamos los colores si no están las luces activadas */
   if(!modoIluminacion){
      if(actual[0] <= 1.0 && step1)
      {
         actual[0] += 0.01;

         if(actual[2] < 0.9)
            actual[1] += 0.01;
         
         if(actual[2] < 0.1)
            actual[2] += 0.01;

         if(actual[0] >= 1.0 && actual[1] >= 0.9 && actual[2] >= 0.1)
         {
            step1 = false;
         }
      }
      
      if(!step1){
         actual[0] -= 0.005;
         actual[1] -= 0.005;
         actual[2] -= 0.005;

         if(actual[0] <= 0.0 && actual[1] <= 0.0 && actual[2] <= 0.0)
         {
            step1 = true;
         }        
      }

   if(step2)
      {
         actualT[0] += 0.01;

         if(actualT[2] < 0.8)
            actualT[1] += 0.01;
         
         if(actualT[2] < 0.8)
            actualT[2] += 0.01;

         if(actualT[0] >= 0.8 && actualT[1] >= 0.8 && actualT[2] >= 0.8)
         {
            step2 = false;
         }
      }
      
      if(!step2){
         actualT[0] -= 0.005;
         actualT[1] -= 0.005;
         actualT[2] -= 0.005;

         if(actualT[0] <= 0.0 && actualT[1] <= 0.0 && actualT[2] <= 0.0)
         {
            step2 = true;
         }        
      }

      esfera1->cambiarColor(actual[0], actual[1], actual[2]);
      tetraedro->cambiarColor(actualT[0], actualT[1], actualT[2]);
   }

   /* Si las luces están activadas, es necesario cambiar los materiales */
   else
   {
      Material* mat_esfera = esfera1->getMaterial();
      Material* mat_tetra = tetraedro->getMaterial();

      Tupla4f esfera_dif = mat_esfera->getAmbiente();
      Tupla4f tetra_dif = mat_tetra->getAmbiente();

      if(step3)
      {
         if(esfera_dif[0] < 0.4)
            esfera_dif[0] += 0.01;
         
         if(esfera_dif[1] < 0.5)
            esfera_dif[1] += 0.01;
         
         if(esfera_dif[2] < 0.4)
            esfera_dif[2] += 0.01;
         
         if(esfera_dif[3] < 0.078)
            esfera_dif[3] += 0.012;

         if(esfera_dif[0] >= 0.4 && esfera_dif[1] >= 0.5 && esfera_dif[2] >= 0.4 && esfera_dif[3] >= 0.078)
            step3 = false;
      }

      if(!step3)
      {
         if(esfera_dif[0] > 0.0)
            esfera_dif[0] -= 0.01;
         
         if(esfera_dif[1] > 0.0)
            esfera_dif[1] -= 0.01;
         
         if(esfera_dif[2] > 0.0)
            esfera_dif[2] -= 0.01;
         
         if(esfera_dif[3] > 0.0)
            esfera_dif[3] -= 0.012;

         if(esfera_dif[0] <= 0.0 && esfera_dif[1] <= 0.0 && esfera_dif[2] <= 0.0 && esfera_dif[3] <= 0.0)
            step3 = true;         
      }

      if(step4)
      {
         if(tetra_dif[0] < 0.135)
            tetra_dif[0] += 0.01;
         
         if(tetra_dif[1] < 0.2225)
            tetra_dif[1] += 0.01;
         
         if(tetra_dif[2] < 0.1575)
            tetra_dif[2] += 0.01;
         
         if(tetra_dif[3] < 0.1)
            tetra_dif[3] += 0.01;

         if(tetra_dif[0] >= 0.135 && tetra_dif[1] >= 0.2225 && tetra_dif[2] >= 0.1575 && tetra_dif[3] >= 0.1)
            step4 = false;
      }

      if(!step4)
      {
         if(tetra_dif[0] > 0.0)
            tetra_dif[0] -= 0.01;
         
         if(tetra_dif[1] > 0.0)
            tetra_dif[1] -= 0.01;
         
         if(tetra_dif[2] > 0.0)
            tetra_dif[2] -= 0.01;
         
         if(tetra_dif[3] > 0.0)
            tetra_dif[3] -= 0.012;

         if(tetra_dif[0] <= 0.0 && tetra_dif[1] <= 0.0 && tetra_dif[2] <= 0.0 && tetra_dif[3] <= 0.0)
            step4 = true;         
      }

      mat_esfera->setAmbiente(esfera_dif);
      mat_tetra->setAmbiente(tetra_dif);
      esfera1->setMaterial(*mat_esfera);
      tetraedro->setMaterial(*mat_tetra);
   }
}

/* Los colores originales de los objetos */
void Escena::coloresOriginales()
{
   cuadro->cambiarColor(1.0, 1.0, 1.0);
   suelo->cambiarColor(1.0, 1.0, 1.0);
   cubo->cambiarColor(1.0, 1.0, 1.0);
   cilindro1->cambiarColor(1.0, 1.0, 1.0);
   mol->cambiarColor(1.0, 0, 0);
   peon1->cambiarColor(1.0, 0, 0);
   ply1->cambiarColor(1.0, 0, 0);
   peon2->cambiarColor(0.4, 0.7, 0.9);
   peon3->cambiarColor(1.0, 0.6, 0.7);
   peon4->cambiarColor(1.0, 0.7, 0.1);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
   glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

   glEnable(GL_DEPTH_TEST);   // se habilita el z-bufer
   glEnable(GL_CULL_FACE);    // no dibujar las caras traseras
   glEnable(GL_NORMALIZE);    // Flag para evitar que las transformaciones alteren las normales
   glEnable(GL_DITHER);  
   glDisable(GL_LIGHTING);

   Width  = UI_window_width/10;
   Height = UI_window_height/10;

   change_projection();
   glViewport( 0, 0, UI_window_width, UI_window_height );
}

// Función para invocar a los diferentes métodos para animar el modelo jerárquico
void Escena::animarModeloJerarquico()
{
   static float anguloEje, anguloCabezalY, anguloCabezalZ, altura;
   static int pausa = 0;
   static Tupla3f posicion{0, 0, 0};

   if(animate){
         switch(pausa){
         case 0:
            anguloEje += 1.2;
            anguloCabezalY += 0.5*fVGrado1*factorVelocidad;

            if(anguloCabezalY >= 60.0){
               pausa = 1;
            }
         break;

         case 1:
            anguloEje += 1.2;
            anguloCabezalZ -= 0.5*fVGrado2*factorVelocidad;

            if(anguloCabezalZ <= -35.0){
               pausa = 2;
            }
         break;

         case 2:
            anguloEje += 1.2;
            altura += 0.5*fVGrado3*factorVelocidad;

            if(altura >= 25.0){
               pausa = 3;
            }
         break;

         case 3:
            altura -= 0.5*fVGrado3*factorVelocidad;
            anguloEje += 1.2;

            if(altura <= 0.0)
               pausa = 4;
         break;

         case 4:
            anguloEje += 1.2;
            anguloCabezalZ += 0.5*fVGrado2*factorVelocidad;

            if(anguloCabezalZ >= 0.0){
               pausa = 5;
            }
         break;

         case 5:
            anguloEje += 1.2;
         
            anguloCabezalY -= 0.5*fVGrado1*factorVelocidad;

            if(anguloCabezalY <= 0.0){
               pausa = 0;
            }
         break;
      }
   }

   if(animatePuntual){
      static bool first = true, next = false;
      
      if(first){
         posicion[0] += 20.0;
         posicion[1] += 20.0;
         posicion[2] += 20.0;

         if(posicion[0] == 200){
            next = true;
            first = false;
         }
      }

      if(next){
         posicion[0] -= 20.0;
         posicion[1] -= 20.0;
         posicion[2] -= 20.0;

         if(posicion[0] == -200){
            next = false;
            first = true;
         }
      }
   }

   mol->setRotacionEje(anguloEje*fVGrado0*factorVelocidad);
   mol->setAnguloCabezalY(anguloCabezalY);
   mol->setAnguloCabezalZ(anguloCabezalZ);
   mol->setAltura(altura);
   cuadroLuces[0]->setPosicion(posicion);
}

// Función para controlar los botones del ratón
void Escena::clickRaton(int boton, int estado, int x, int y)
{
   switch(boton){
      case GLUT_RIGHT_BUTTON: 
         if(estado == GLUT_DOWN){
            moviendoCamaraFP = true;
            xant = x;
            yant = y;
         }

      break;

      case GLUT_LEFT_BUTTON:
         if(estado == GLUT_DOWN){
            xleido = x;
            yleido = y;
         }
      break;

      // Rueda del ratón hacia arriba
      case 3:
            cuadroCamaras[camaraActiva]->zoom(1.0);
      break;

      // Rueda del ratón hacia abajo
      case 4:
            cuadroCamaras[camaraActiva]->zoom(-1.0);
      break;
   }
}

// Función para controlar el movimiento del ratón
void Escena::ratonMovido(int x, int y)
{
   if(moviendoCamaraFP)
   {
      if(cuadroCamaras[camaraActiva]->getRotando())
      {
         cuadroCamaras[camaraActiva]->rotarXExaminar((x-xant)*0.1);
         cuadroCamaras[camaraActiva]->rotarYExaminar((y-yant)*0.1);
      }

      else
      {
         cuadroCamaras[camaraActiva]->rotarXFirstPerson((x-xant)*0.1);
         cuadroCamaras[camaraActiva]->rotarYFirstPerson((y-yant)*0.1);
      }

      xant = x;
      yant = y;
   }
}

// Activación de luces
void Escena::activacionLuces()
{
   if(modoIluminacion){
      if(!glIsEnabled(GL_LIGHTING)){
        glEnable(GL_LIGHTING);
      }

      for(int i=0; i<8; i++){
         if(cuadroLuces[i] != nullptr && luces[i]){
            cuadroLuces[i]->activar();
         }
         
         else if (cuadroLuces[i] != nullptr && !luces[i]){
            glDisable(cuadroLuces[i]->getID());
         }
      }  

      glShadeModel(GL_SMOOTH);
   }

   else{
      if(glIsEnabled(GL_LIGHTING)){
        glDisable(GL_LIGHTING);
      }

      glShadeModel(GL_FLAT);
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

   if(xleido != -1 && yleido != -1)
      dibujaSeleccion();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiamos de nuevo

   change_projection();
	change_observer();
   glDisable(GL_LIGHTING);
   ejes.draw();

   coloresOriginales();

   // Luces, cámaras...
   activacionLuces();

   // Acción
   creacionEscena();
}

// Asignamos los colores a los objetos seleccionables
void Escena::coloresSeleccionables()
{
   esfera1->cambiarColor(1.0, 0.9, 0.1);
   tetraedro->cambiarColor(0.8, 0.8, 0.8);
}

// Mueve la cámara según el objeto seleccionado. Si vuelve a ser pulsado, volvemos al eje de coordenadas
void Escena::objetoSeleccionado(int objSelec, Malla3D* obj)
{
   if(objSelec != objetoActivo)
   {
      switch(objSelec)
      {
         case 0: std::cout << "Esfera seleccionada" << std::endl; break;
         case 1: std::cout << "Tetraedro seleccionado" << std::endl; break;
      }

      objetoActivo = objSelec;
      rotacionSeleccion = true;
      cuadroCamaras[camaraActiva]->setAt(obj->getPosicion());

      // ¿Estamos rotando en la cámara?
      cuadroCamaras[camaraActiva]->setRotando(true);
   }

   else
   {
      switch(objSelec)
      {
         case 0: std::cout << "Esfera deseleccionada" << std::endl; break;
         case 1: std::cout << "Tetraedro deseleccionado" << std::endl; break;
      }

      objetoActivo = -1;
      rotacionSeleccion = false;
      cuadroCamaras[camaraActiva]->setAt({0, 0, 0});

      // ¿Estamos rotando en la cámara?
      cuadroCamaras[camaraActiva]->setRotando(false);
   }
}

// Obtiene el objeto correspondiente al pixel seleccionado
void Escena::seleccionPixel()
{
   GLint viewport[4];
   GLfloat seleccionado[3];

   // Vuelca el entero del viewport
   glGetIntegerv(GL_VIEWPORT, viewport);

   // Lee los píxeles
   glReadPixels(xleido, viewport[3]-yleido, 1, 1, GL_RGB, GL_FLOAT, (void *) seleccionado);

   // Seleccionamos ahora el objeto según el píxel seleccionado
   if(round(seleccionado[0]*10)/10 == 1.0)
      objetoSeleccionado(0, esfera1);

   else if(round(seleccionado[0]*10)/10 == 0.8)
      objetoSeleccionado(1, tetraedro);
}

/* Función para dibujar los objetos seleccionados en la escena */
void Escena::dibujaSeleccion()
{
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE);

   // Preservamos los estados anteriores y activamos el modo sólido
   int modoDibujado_ant = modoDibujado;
   bool estadosAnteriores[5] = {puntos, lineas, solido, chess, modoIluminacion};
   puntos = false, lineas = false, solido = true, chess = false, modoIluminacion = false, modoDibujado = 1;

   // Cambiamos los colores de los objetos a los colores con selección
   coloresSeleccionables();

   // Creamos la escena
   creacionEscena();

   // Obtenemos el píxel sobre el que hemos pulsado
   seleccionPixel();

   // Revertimos los colores iniciales y los estados de la escena
   coloresOriginales();

   modoDibujado = modoDibujado_ant;
   puntos = estadosAnteriores[0];
   lineas = estadosAnteriores[1];
   solido = estadosAnteriores[2];
   chess = estadosAnteriores[3];
   modoIluminacion = estadosAnteriores[4];
   xleido = -1;
   yleido = -1;
}

/* Función para mostrar por terminal las diferentes opciones de los diferentes modos */
void Escena::interaccionTerminal()
{
   if(modoMenu == NADA)
   {
      std::cout << "Opciones disponibles:\n";
      std::cout << "\tV: Modo de Visualización\n";
      std::cout << "\tD: Selección de Modo de Dibujo\n";
      std::cout << "\tA: Activar/Desactivar Animación automática de los objetos\n";
      std::cout << "\tM: Mover manualmente el grado de libertad (se desactiva la animación automática)\n";
      std::cout << "\tC: Modo Selección de Cámara\n";
      std::cout << "\tQ: Salir del programa\n";
   }

   if(modoMenu == SELDIBUJADO)
   {
      std::cout << "Modo selección de Modo de Dibujado - Opciones Disponibles\n";
      std::cout << "\t1: Activar el Modo Inmediato\n";
      std::cout << "\t2: Activar el Modo Diferido\n";
      std::cout << "\tQ: Salir del Modo de selección\n";
   }

   if(modoMenu == SELVISUALIZACION && !modoIluminacion)
   {
      std::cout << "Modo de Visualización - Opciones Disponibles\n";
      std::cout << "\tP: Activar/Desactivar el Modo Puntos\n";
      std::cout << "\tL: Activar/Desactivar el Modo Líneas\n";
      std::cout << "\tS: Activar/Desactivar el Modo Sólido\n";
      std::cout << "\tA: Activar/Desactivar el Modo Ajedrez (desactivando iluminación)\n";
      std::cout << "\tI: Activar/Desactivar el Modo Iluminación\n";
      std::cout << "\tQ: Salir del Modo Visualización\n";
   }

   if(modoMenu == SELVISUALIZACION && modoIluminacion)
   {
      std::cout << "Modo Iluminación - Opciones Disponibles\n";
      std::cout << "\t0-7: Activar/Desactivar las luces\n";
      std::cout << "\tA: Activar variación del ángulo alfa\n";
      std::cout << "\tB: Activar variación del ángulo beta\n";
      std::cout << "\t>: Incrementa el ángulo (según lo último pulsado)\n";
      std::cout << "\t<: Decrementa el ángulo (según lo último pulsado)\n";
      std::cout << "\tP: Animación automática de la luz puntual\n";
      std::cout << "\tQ: Salir del Modo Visualización\n";
   }

   if(modoMenu == MOVMANUAL)
   {
      std::cout << "Movimiento Manual de los Grados de Libertad - Opciones Disponibles\n";
      std::cout << "\t0-3: Seleccionar grado de libertad\n";
      std::cout << "\t+: Aumenta el valor del grado de libertad seleccionado\n";
      std::cout << "\t-: Decrementa el valor del grado de libertad seleccionado\n";
      std::cout << "\tQ: Salir del Modo\n";
   }

   if(modoMenu == MODOCAMARA)
   {
      std::cout << "Modo Cámara - Opciones Disponibles\n";
      std::cout << "\t0-7: Seleccionar cámara\n";
      std::cout << "\tQ: Salir del Modo Cámara\n";
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   bool salir = false;
   bool modoLibertad = false;
   static int gradoLibertad = -1;

   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
         {
         	modoMenu=NADA;
         }          
         else 
         {
            salir=true ;
         }
      break;

      case 'T' :
         tapas = !tapas;
      break;

      case 'D' :
         if(modoMenu == NADA)
         {
            modoMenu = SELDIBUJADO;
            std::cout << "\nEntrando en Modo Dibujado\n";
         }
      break;

      case 'V' :
         if(modoMenu == NADA)
         {
         	modoMenu = SELVISUALIZACION;
            std::cout << "\nEntrando en Modo Visualización\n";
         }
      break;

      case 'P' :
         if (modoMenu == SELVISUALIZACION && !modoIluminacion)
         {
            modoIluminacion = false;
            puntos = !puntos;

            if(puntos)
            {
               std::cout << "\nModo puntos activado\n";
            }

            else
            {
               std::cout << "\nModo puntos desactivado\n";
            }
         }

         if(modoMenu == SELVISUALIZACION && modoIluminacion && luces[0])
         {
            animatePuntual = !animatePuntual;

            if(animatePuntual)
            {
               std::cout << "\nLuz puntual animada\n";
            }

            else
            {
               std::cout << "\nLuz puntual parada\n";
            }
         }
      break;

      case 'L' :
         if (modoMenu == SELVISUALIZACION)
         {
            modoIluminacion = false;
            lineas = !lineas;

            if(lineas)
            {
               std::cout << "\nModo lineas activado\n";
            }

            else
            {
               std::cout << "\nModo lineas desactivado\n";
            }
         }
      break;

      case 'S' :
         if (modoMenu == SELVISUALIZACION)
         {
            modoIluminacion = false;
            solido = !solido;

            if(solido)
            {
               std::cout << "\nModo solido activado\n";
            }

            else
            {
               std::cout << "\nModo solido desactivado\n";
            }
         }
      break;

      case 'A' :
         if (modoMenu == SELVISUALIZACION && !modoIluminacion)
         {
            modoIluminacion = false;
            chess = !chess;

            if(chess){
               modoDibujado = 3;
               std::cout << "\nModo ajedrez activado\n";
            }

            else{
               modoDibujado = 1;
               std::cout << "\nModo lineas desactivado\n";
            }
         }

         else if (modoMenu == SELVISUALIZACION && modoIluminacion)
         {
            selecComponente = 0;
            std::cout << "\nSeleccionado 'Alfa'\n";
         }

         else if (modoMenu == NADA)
         {
            std::cout << "\nAnimación automática activada\n";
            animate = !animate;
         }
      break;

      case 'I' :
         if (modoMenu == SELVISUALIZACION)
         {
            modoIluminacion = !modoIluminacion;

            if(modoIluminacion)
            {
               std::cout << "\nIluminación activada\n";
            }

            else
            {
               std::cout << "\nIluminación desactivada\n";
            }
         }
      break;

      case 'B' :
         if (modoIluminacion)
         {
            selecComponente = 1;
            std::cout << "\nSeleccionado 'Beta'\n";
         }
      break;

      case '<' :
         if (modoIluminacion){
            if(selecComponente == 0)
               cuadroLuces[1]->variarAnguloAlpha(-1.0);

            else if(selecComponente == 1)
               cuadroLuces[1]->variarAnguloBeta(-1.0);
         }
      break;

      case '>' :
         if (modoIluminacion){
            if(selecComponente == 0)
               cuadroLuces[1]->variarAnguloAlpha(1.0);

            else if(selecComponente == 1)
               cuadroLuces[1]->variarAnguloBeta(1.0);
         }
      break;

      case '+' :
         if(animate){
            factorVelocidad += 1.0;
         }

         else{
            switch(gradoLibertad)
            {
               case 0: fVGrado0 += 1.0; break;
               case 1: fVGrado1 += 1.0; break;
               case 2: fVGrado2 += 1.0; break;
               case 3: fVGrado3 += 1.0; break;
            }
         }
      break;

      case '-' :
         if(animate){
            factorVelocidad -= 1.0;
         }

         else{
            switch(gradoLibertad)
            {
               case 0: fVGrado0 -= 1.0; break;
               case 1: fVGrado1 -= 1.0; break;
               case 2: fVGrado2 -= 1.0; break;
               case 3: fVGrado3 -= 1.0; break;
            }
         }
      break;

      case 'M':
         if(modoMenu == NADA)
         {
            animate = false;
            movManual = !movManual;
            modoMenu = MOVMANUAL;
            std::cout << "\nMovimiento manual de los grados de libertad activado\n";
         }
      break;

      case 'C':
         if(modoMenu == NADA)
         {
            modoCamara = !modoCamara;
            modoMenu = MODOCAMARA;
            std::cout << "\nModo Cámara activado\n";
         }
      break;

      case '0' :
         if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[0] = !luces[0];
            std::cout<<"\n\tLuz 0 activada\n";
         }

         else if (modoMenu == MOVMANUAL && movManual){
            gradoLibertad = 0;
            std::cout << "\n\tSeleccionado grado de libertad 0\n";
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[0] = !camaras[0];
            camaraActiva = 0;
            std::cout << "\n\tCámara 0 activada\n";
         }
      break;

      case '1' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = 1;
            std::cout << "\n\tModo de dibujado: Inmediato\n";
         }

         else if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[1] = !luces[1];
            std::cout << "\n\tLuz 1 activada\n";
         }

         else if (modoMenu == MOVMANUAL && movManual){
            gradoLibertad = 1;
            std::cout << "\n\tSeleccionado grado de libertad 1\n";
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[1] = !camaras[1];
            camaraActiva = 1;
            std::cout << "\n\tCámara 1 activada\n";
         }
      break;

      case '2' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = 2;
            std::cout << "\n\tModo de dibujado: Diferido\n";
         }

         else if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[2] = !luces[2];
            std::cout << "\n\tLuz 2 activada\n";
         }

         else if (modoMenu == MOVMANUAL && movManual){
            gradoLibertad = 2;
            std::cout << "\n\tSeleccionado grado de libertad 2\n";
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[2] = !camaras[2];
            camaraActiva = 2;
            std::cout << "\n\tCámara 2 activada\n";
         }
      break; 

      case '3' :
         if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[3] = !luces[3];
         }

         else if (modoMenu == MOVMANUAL && movManual){
            gradoLibertad = 3;
            std::cout << "\n\tSeleccionado grado de libertad 3\n";
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[3] = !camaras[3];

            if(cuadroCamaras[3] != nullptr)
               camaraActiva = 3;
               std::cout << "\n\tCámara 3 activada\n";
         }
      break;  

      case '4' :
         if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[4] = !luces[4];
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[4] = !camaras[4];

            if(cuadroCamaras[4] != nullptr)  
               camaraActiva = 4;
         }
      break;

      case '5' :
         if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[5] = !luces[5];
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[5] = !camaras[5];

            if(cuadroCamaras[5] != nullptr)  
               camaraActiva = 5;
         }
      break;

      case '6' :
         if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[6] = !luces[6];
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[6] = !camaras[6];

            if(cuadroCamaras[6] != nullptr)  
               camaraActiva = 6;
         }
      break;

      case '7' :
         if (modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[7] = !luces[7];
         }

         else if (modoMenu == MODOCAMARA && modoCamara){
            camaras[7] = !camaras[7];

            if(cuadroCamaras[7] != nullptr)  
               camaraActiva = 7;
         }
      break;  
   }

   interaccionTerminal();

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         cuadroCamaras[camaraActiva]->rotarXExaminar(-1);
         break;
	   case GLUT_KEY_RIGHT:
         cuadroCamaras[camaraActiva]->rotarXExaminar(1);
         break;
	   case GLUT_KEY_UP:
         cuadroCamaras[camaraActiva]->rotarYExaminar(1);
         break;
	   case GLUT_KEY_DOWN:
         cuadroCamaras[camaraActiva]->rotarYExaminar(-1);
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   cuadroCamaras[camaraActiva]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   cuadroCamaras[camaraActiva]->setObserver();
}
