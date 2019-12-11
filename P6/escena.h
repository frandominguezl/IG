#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "material.h"
#include "molino.h"
#include "cuadro.h"
#include "textura.h"
#include "camara.h"


typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

    private:

    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
        
        // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection( const float ratio_xy );
    void change_observer();



    void clear_window();

    menu modoMenu=NADA;

    // Objetos de la escena
    Ejes ejes;

    // Objetos PLY
    ObjPLY * ply1 = nullptr;

    // Objetos de revolución
    ObjRevolucion * peon1 = nullptr;
    ObjRevolucion * peon2 = nullptr;
    Cilindro * cilindro1 = nullptr;
    Cono * cono1 = nullptr;
    Esfera * esfera1 = nullptr;

    // Objetos básicos
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'

    // Cuadro
    Cuadro* cuadro = nullptr;

    // Luces
    LuzPosicional * luzP = nullptr;

    // Materiales
    Material mat1;

    // Texturas
    Textura tex1;
    Textura tex2;

    // Modelo Jerárquico
    Molino * mol = nullptr;
    
    // Modo de Visualización
    // int modoDibujado = (1 = modoInmediato, 2 = modoDiferido, 3 = modoAjedrez)
    int modoDibujado = 1;

    // Booleanos para modo visualización en modo puntos, líneas, sólido y ajedrez
    bool puntos = false, lineas = false, solido = true, chess = false;

    // Controlar las tapas en tiempo de ejecución
    bool tapas = true;

    // Modo Iluminación
    bool modoIluminacion = false;

    // Cuadro de luces
    Luz* cuadroLuces[8] = {nullptr};

    // Activación de las luces
    bool luces[8] = {false};

    // Modo Cámara
    bool modoCamara = false;

    // Vector de cámaras de la escena
    Camara* cuadroCamaras[8] = {nullptr};

    // Activación de las cámaras
    bool camaras[8] = {false};

    // Cámara activa
    int camaraActiva = 0;

    // Estado del ratón
    bool moviendoCamaraFP = false;
    int xant = 0, yant = 0;

    // Booleano para activar/desactivar animación
    bool animate = false;
    bool animatePuntual = false;

    // Factores de velocidad
    float factorVelocidad = 1.0;
    float fVGrado0 = 1.0;
    float fVGrado1 = 1.0;
    float fVGrado2 = 1.0;
    float fVGrado3 = 1.0;

    // Controlador para el ángulo seleccionado
    // 0 = alpha
    // 1 = beta
    int selecComponente = -1;

   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
    void animarModeloJerarquico();
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    void dibujaSelecion();

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
