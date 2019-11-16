

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
    cilindro1 = new Cilindro(50, 50, 10);
    cono1 = new Cono(50, 30, 10);
    esfera1 = new Esfera(50, 20, 10);

    // Cargamos los objetos básicos
    cubo = new Cubo();
    tetraedro = new Tetraedro();

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
   ejes.draw();

   glPushMatrix();
      glTranslatef(0,170,0);
      cubo->cambiarColor(1.0, 0, 0);
      cubo->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(100,0,0);
      tetraedro->cambiarColor(1.0, 0, 0);
      tetraedro->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();
   
   glPushMatrix();
      glScalef(25.0,25.0,25.0);
      peon1->cambiarColor(1.0, 0, 0);
      peon1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100,0,0);
      glScalef(3,3,3);
      ply1->cambiarColor(1.0, 0, 0);
      ply1->draw(modoDibujado, puntos, lineas, solido);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100,0,-100);
      glScalef(3,3,3);
      cilindro1->cambiarColor(1.0, 0, 0);
      cilindro1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(100,0,-100);
      glScalef(3,3,3);
      cono1->cambiarColor(1.0, 0, 0);
      cono1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(100,0,100);
      glScalef(5,5,5);
      esfera1->cambiarColor(1.0, 0, 0);
      esfera1->draw(modoDibujado, puntos, lineas, solido, tapas);
   glPopMatrix();
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
   char anterior;

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

      case 'O' :
         if(modoMenu != SELVISUALIZACION || modoMenu != SELDIBUJADO){
         	modoMenu=SELOBJETO;
         }
      break;

      case 'T' :
         tapas = !tapas;
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
        if (modoMenu == SELVISUALIZACION){
          puntos = !puntos;
        }
      break;

      case 'L' :
        if (modoMenu == SELVISUALIZACION){
          lineas = !lineas;
        }
      break;

      case 'S' :
        if (modoMenu == SELVISUALIZACION){
            solido = !solido;
        }
      break;

      case 'A' :
        if (modoMenu == SELVISUALIZACION){
          chess = !chess;

          if(chess){
             modoDibujado = 3;
          }

          else{
             modoDibujado = 1;
          }
        }

        else if (modoMenu == SELVISUALIZACION){
          anterior = 'A';
        }
      break;

      case '1' :
        if (modoMenu == SELDIBUJADO){
          modoDibujado = 1;
        }
      break;

      case '2' :
        if (modoMenu == SELDIBUJADO){
          modoDibujado = 2;
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
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
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
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
