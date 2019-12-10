

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
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   // Cargamos los bjetos PLY
   ply1 = new ObjPLY("plys/ant.ply");

   // Cargamos objetos de revolución
   peon1 = new ObjRevolucion("plys/peon.ply", 50);
   peon2 = new ObjRevolucion("plys/peon.ply", 50);
   cilindro1 = new Cilindro(50, 50, 10);
   cono1 = new Cono(50, 30, 10);
   esfera1 = new Esfera(50, 20, 10);

   // Cargamos los objetos básicos
   cubo = new Cubo();
   tetraedro = new Tetraedro();
   cuadro = new Cuadro();

   // Modelo Jerárquico
   mol = new Molino();

   // Luces
   cuadroLuces[0] = new LuzPosicional({0, 0, 0}, GL_LIGHT1, {0.2, 0.2, 0.2, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
   cuadroLuces[1] = new LuzDireccional({0, 0}, GL_LIGHT2, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   // Cámaras
   cuadroCamaras[0] = new Camara({1, 1, 0}, {1, 1, 0}, {1, 1, 0}, 1, 45.0, 16/9, 50.0, 2000.0);
   cuadroCamaras[1] = new Camara({1, 1, 0}, {1, 1, 0}, {1, 1, 0}, 1, 45.0, 16/9, 50.0, 2000.0);
   cuadroCamaras[2] = new Camara({1, 1, 0}, {1, 1, 0}, {1, 1, 0}, 0, 45.0, 16/9, 50.0, 2000.0);

   // Materiales
   Tupla4f ambiente1(0.135, 0.2225, 0.1575, 0.1), especular1(0.0, 0.0, 0.0, 0.1), difuso1(0.786, 0.89, 0.97, 0.1);
   Tupla4f ambiente2(0.0215,	0.1745, 0.0215, 0.6), especular2(0.7038, 0.27048, 0.0828, 0.6), difuso2(0.0, 0.0, 0.0, 0.6);
   Tupla4f ambiente3(0.0, 0.05, 0.0, 0.078125), especular3(0.04, 0.7, 0.04, 0.078125), difuso3(0.4, 0.5, 0.4, 0.078125);

   Material mat1(difuso1, especular1, ambiente1, 0.1*128.0);
   Material mat2(difuso2, especular2, ambiente2, 0.01*128.0);
   Material mat3(difuso3, especular3, ambiente3, 0.6*128.0);
   peon1->setMaterial(mat1);
   peon2->setMaterial(mat2);
   ply1->setMaterial(mat1);
   cubo->setMaterial(mat1);
   tetraedro->setMaterial(mat2);
   cilindro1->setMaterial(mat3);
   esfera1->setMaterial(mat3);
   cono1->setMaterial(mat1);
   mol->setMaterial(mat3);
   cuadro->setMaterial(mat1);

   // Texturas
   tex1 = Textura("img/text-madera.jpg", 1);
   tex2 = Textura("img/text-lata-1.jpg", 2);
   cuadro->setTextura(tex1);
   cuadro->setCoordenadas();
   cubo->setTextura(tex1);
   cubo->setCoordenadas();
   cilindro1->setTextura(tex2);
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

   Width  = UI_window_width/10;
   Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
   glViewport( 0, 0, UI_window_width, UI_window_height );
}

// Función para invocar a los diferentes métodos para animar el modelo jerárquico
void Escena::animarModeloJerarquico()
{
   static float anguloEje, anguloCabezalY, anguloCabezalZ, altura;
   static int pausa = 0;
   static Tupla3f posicion{200, 200, 200};

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
            anguloEje += 1.2;
         break;
      }
   }

   if(animatePuntual){
      posicion[0] -= 1.0;
      posicion[1] -= 1.0;
      posicion[2] -= 1.0;
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
      case GLUT_LEFT_BUTTON: 
         if(estado == GLUT_UP){
            cuadroCamaras[camaraActiva]->mover(x, y, 0);
            moviendoCamaraFP = true;
         }

         else{
            moviendoCamaraFP = false;
         }
      break;

      case GLUT_MIDDLE_BUTTON: break;
      case GLUT_RIGHT_BUTTON: break;
   }
}

// Función para controlar el movimiento del ratón
void Escena::ratonMovido(int x, int y)
{
   if(moviendoCamaraFP){
      cuadroCamaras[camaraActiva]->girar(x-xant, y-yant, 0);
      xant = x;
      yant = y;
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
	change_observer();
   glDisable(GL_LIGHTING);
   ejes.draw();

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

   glEnable(GL_TEXTURE_2D);

   glPushMatrix();
      glTranslatef(100, 0, 0);
      cuadro->cambiarColor(1.0, 0.0, 0.0);
      cuadro->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(65, 100, 0);
      glScalef(0.5, 0.5, 0.5);
      cubo->cambiarColor(1.0, 0, 0);
      cubo->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100, 0, -100);
      glScalef(3,3,3);
      cilindro1->cambiarColor(1.0, 0, 0);
      cilindro1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   glDisable(GL_TEXTURE_2D);

   glPushMatrix();
      mol->cambiarColor(1.0, 0, 0);
      mol->drawMolino(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   /*glPushMatrix();
      glTranslatef(100, 0, 0);
      tetraedro->cambiarColor(1.0, 0, 0);
      tetraedro->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(0, -50, 0);
      glScalef(25.0, 25.0, 25.0);
      peon1->cambiarColor(1.0, 0, 0);
      peon1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100, 0, 0);
      glScalef(3,3,3);
      ply1->cambiarColor(1.0, 0, 0);
      ply1->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();*/

   /*glPushMatrix();
      glTranslatef(100, 0, -100);
      glScalef(25, 25, 25);
      peon2->cambiarColor(1.0, 0, 0);
      peon2->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(100, 0, 100);
      glScalef(5,5,5);
      esfera1->cambiarColor(1.0, 0, 0);
      esfera1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();*/
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
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   bool modoLibertad = false;
   static int gradoLibertad = -1;

   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
         	modoMenu=NADA;
         }          
         else {
            salir=true ;
         }
      break;

      case 'T' :
         tapas = !tapas;
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

      case 'V' :
         if(modoMenu != SELOBJETO || modoMenu != SELDIBUJADO){
         	modoMenu=SELVISUALIZACION;
         }
         break;
      case 'D' :
         if(modoMenu != SELOBJETO || modoMenu != SELVISUALIZACION){
         	modoMenu=SELVISUALIZACION;
         }
      break;

      case 'P' :
        if (modoMenu == SELVISUALIZACION && !modoIluminacion){
            modoIluminacion = false;
            puntos = !puntos;
        }

         if(modoIluminacion && luces[0])
            animatePuntual = !animatePuntual;
      break;

      case 'L' :
        if (modoMenu == SELVISUALIZACION){
            modoIluminacion = false;
            lineas = !lineas;
        }
      break;

      case 'S' :
        if (modoMenu == SELVISUALIZACION){
            modoIluminacion = false;
            solido = !solido;
        }
      break;

      case 'A' :
         if (modoMenu == SELVISUALIZACION && !modoIluminacion){
            modoIluminacion = false;
            chess = !chess;

            if(chess){
               modoDibujado = 3;
            }

            else{
               modoDibujado = 1;
            }
         }

         else if (modoIluminacion){
            selecComponente = 0;
         }

         else{
            animate = !animate;
         }
      break;

      case 'B' :
         if (modoIluminacion){
            selecComponente = 1;
         }
      break;

      case 'M':
         animate = false;
      break;

      case '<' :
         if (modoIluminacion){
            if(selecComponente == 0){
               cuadroLuces[1]->variarAnguloAlpha(-1.0);
            }

            else if(selecComponente == 1){
               cuadroLuces[1]->variarAnguloBeta(-1.0);
            }
         }
      break;

      case '>' :
         if (modoIluminacion){
            if(selecComponente == 0){
               cuadroLuces[1]->variarAnguloAlpha(1.0);
            }

            else if(selecComponente == 1){
               cuadroLuces[1]->variarAnguloBeta(1.0);
            }
         }
      break;      

      case 'I' :
         if (modoMenu == SELVISUALIZACION){
            modoIluminacion = !modoIluminacion;
         }
      break;

      case 'C':
         modoCamara = !modoCamara;
      break;

      case '0' :
         if (modoIluminacion){
            luces[0] = !luces[0];
         }

         else if (modoCamara){
            camaraActiva = 0;
         }

         else if (!modoIluminacion && !animate){
            gradoLibertad = 0;
         }
      break;

      case '1' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = 1;
         }

         else if (modoCamara){
            camaraActiva = 1;
         }

         else if (modoIluminacion){
            luces[1] = !luces[1];
         }

         else if (!modoIluminacion && !animate){
            gradoLibertad = 1;
         }
      break;

      case '2' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = 2;
         }

         else if (modoCamara){
            camaraActiva = 2;
         }

         else if (modoIluminacion){
            luces[2] = !luces[2];
         }

         else if (!modoIluminacion && !animate){
            gradoLibertad = 2;
         }
      break; 

      case '3' :
         if (modoIluminacion){
            luces[3] = !luces[3];
         }

         else if (modoCamara){
            camaraActiva = 3;
         }

         else if (!modoIluminacion && !animate){
           gradoLibertad = 3;
        }
      break;  

      case '4' :
         if (modoMenu == SELVISUALIZACION){
            luces[4] = !luces[4];
         }
      break;

      case '5' :
         if (modoMenu == SELVISUALIZACION){
            luces[5] = !luces[5];
         }
      break;

      case '6' :
         if (modoMenu == SELVISUALIZACION){
            luces[6] = !luces[6];
         }
      break;

      case '7' :
         if (modoMenu == SELVISUALIZACION){
            luces[7] = !luces[7];
         }
      break;  
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
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

void Escena::change_projection( const float ratio_xy )
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
   change_projection( float(newHeight)/float(newWidth) );
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
