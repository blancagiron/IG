//**************************************************************************
// Práctica 2
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

const float AXIS_SIZE = 5000;
typedef enum
{
       POINTS,
       EDGES,
       SOLID,
       SOLID_COLORS,
       SOLID_EDGES
} _modo;

enum _camara
{
       CAMARA_ORIGINAL,
       CAMARA_1,
       CAMARA_PAJARO
};
//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
       _puntos3D();
       void draw_puntos(float r, float g, float b, int grosor);

       vector<_vertex3f> vertices;
       vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D
{
public:
       _triangulos3D();
       void draw_aristas(float r, float g, float b, int grosor);
       void draw_solido(float r, float g, float b);
       void draw_solido_colores();
       void draw(_modo modo, float r, float g, float b, float grosor);

       /* asignación de colores */
       void colors_random();
       void colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
       void draw_personalizado(float r, float g, float b, float grosor);
       vector<_vertex3i> caras;
       vector<_vertex3f> colores_caras;
};

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
public:
       _cubo(float tam = 0.5);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D
{
public:
       _piramide(float tam = 0.5, float al = 1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply : public _triangulos3D
{
public:
       _objeto_ply();

       void parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion : public _triangulos3D
{
public:
       _rotacion();

       void parametros(vector<_vertex3f> perfil, int num,
                       int tapa_in, int tapa_su, int tipo);
};

// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa
// tipo=0 revolucion normal
// tipo=1 esfera
// tipo=2 cono

//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion : public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z, int tapa_su);
};

//************************************************************************
// objeto por revolución especiales
//************************************************************************

//************************************************************************
// cilindro
//************************************************************************

class _cilindro : public _rotacion
{
public:
       _cilindro(float radio = 1.0, float altura = 2.0, int num = 12);
};

//************************************************************************
// cono
//************************************************************************

class _cono : public _rotacion
{
public:
       _cono(float radio = 1.0, float altura = 2.0, int num = 12, int tapa = 0);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera : public _rotacion
{
public:
       _esfera(float radio = 1.0, int latitud = 6, int longitud = 6);
};

//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY : public _rotacion
{
public:
       _rotacion_PLY();
       void parametros_PLY(char *archivo, int num);
};

//************************************************************************
// objeto montaña fractal
//************************************************************************

class _montana : public _triangulos3D
{
public:
       _montana(int nivelmax, float sigma, float h);
};

// nivelmax, ha de ser par es el tamaño de la cuadrícula
// sigma, se relaciona con la altura máxima de la montaña
// h 0<=h<=1, dimensión de Hausdorff indica la forma del relieve, más suave 1

//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

class _pala : public _triangulos3D
{
public:
       _pala(float radio = 1.0, float ancho = 2.0, int num = 8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo : public _triangulos3D
{
public:
       _brazo();
       void draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

protected:
       _cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina : public _triangulos3D
{
public:
       _cabina();
       void draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

protected:
       _cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion : public _triangulos3D
{
public:
       _sustentacion();
       void draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

       float radio;

protected:
       _cilindro rueda;
       _cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora : public _triangulos3D
{
public:
       _excavadora();

       void draw(_modo modo, float r, float g, float b, float grosor);

       float giro_cabina;
       float giro_primer_brazo;
       float giro_segundo_brazo;
       float giro_pala;

       float giro_primer_brazo_max;
       float giro_primer_brazo_min;
       float giro_segundo_brazo_max;
       float giro_segundo_brazo_min;
       float giro_pala_max;
       float giro_pala_min;

       float tamanio_pala;

protected:
       _pala pala;
       _brazo brazo;
       _cabina cabina;
       _sustentacion sustentacion;
};

//************************************************************************
// objeto articulado tocadiscos
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// rectángulo
//************************************************************************

class _rectangulo : public _triangulos3D
{
public:
       _rectangulo(float an = 1.0, float alt = 1.0);
       void draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
};

//************************************************************************
// circulo
//************************************************************************
class _circulo : public _triangulos3D
{
public:
       _circulo(float r);
       _circulo();
       void draw(_modo modo, float r, float g, float b, float grosor);

protected:
       float radio;
       int num;
};

//************************************************************************
// disco
//************************************************************************

class _disco : public _triangulos3D
{
public:
       _disco();
       void draw(_modo modo, float r, float g, float b, float grosor);

       _objeto_ply disco;

       _circulo mini_disco;
       _circulo punto;

       float radio_punto;
       float radio;
       float rotacion_disco;
};

//************************************************************************
// ruedas_sonido
//************************************************************************

class _ruedas_sonido : public _triangulos3D
{
public:
       _ruedas_sonido();
       void draw(_modo modo, float r, float g, float b, float grosor);

       _cilindro rueda1;
       _cilindro rueda2;
       _circulo circulo1;

       float radio1, radio2;
       float radio_circulo1;
       float altura1, altura2;
       float rotacion_ruedas;
       float rotacion_ruedas_max;
};

//************************************************************************
// deslizador
//************************************************************************

class _deslizador : public _triangulos3D
{
public:
       _deslizador();
       void draw(_modo modo, float r, float g, float b, float grosor);

       float radio;
       _cilindro pieza = _cilindro(radio, 0.5, 3);
       _cubo base_deslizador;

       float ancho_base_deslizador;
       float alto_base_deslizador;
       float largo_base_deslizador;

       float alto_pieza;

       float pos_pieza;
       float pos_pieza_max;
       float pos_pieza_min;
};

//************************************************************************
// tapa
//************************************************************************

class _tapa : public _triangulos3D
{
public:
       _tapa();
       void draw(_modo modo, float r, float g, float b, float grosor);

       vector<_vertex3f> poligono;

       _extrusion tapa = _extrusion(poligono, 0, 0, 0, 1);
};

//************************************************************************
// base
//************************************************************************

class _base : public _triangulos3D
{
public:
       _base();
       void draw(_modo modo, float r, float g, float b, float grosor);

       _cubo base;
       _cubo base_tocadiscos;
       _cubo deco_cubo;
       _objeto_ply base_disco;
       _objeto_ply disco;
       _rectangulo base_rectangulo;
       _rectangulo deco_rectangulo;
       _rectangulo deco_rectangulo_mini;

       _cilindro pata;
       _tapa tapa;

       // ruedas decorativas
       float radio_figura_decor;
       float altura_figura_decor;
       _cilindro figura = _cilindro(radio_figura_decor, altura_figura_decor, 20);

       float radio;
       float altura;

       float ancho_base;
       float alto_base;
       float largo_base;

       float ancho_base_tocadiscos;
       float alto_base_tocadiscos;
       float largo_base_tocadiscos;

       // rectángulo base;
       float ancho_rectangulo;
       float alto_rectangulo;

       float ancho_decoracion;
       float alto_decoracion;

       float ancho_decoracion_mini;
       float alto_decoracion_mini;

       float ancho_deco_cubo;
       float alto_deco_cubo;
       float largo_deco_cubo;
};

//************************************************************************
// aguja
//************************************************************************

class _aguja : public _triangulos3D
{
public:
       _aguja();
       void draw(_modo modo, float r, float g, float b, float grosor);

       _cubo columna;
       _cubo base;
       _cubo pieza;
       _cilindro brazo;
       _piramide punta;

       float rotacion_base;
       float rotacion_base_max;
       float rotacion_base_min;

       float subida_base;
       float subida_base_max;
       float subida_base_min;

       float ancho_columna;
       float alto_columna;
       float fondo_columna;

       float ancho_base;
       float alto_base;
       float fondo_base;

       float ancho_pieza;
       float alto_pieza;
       float fondo_pieza;

       float radio_brazo;
       float alto_brazo;

       float ancho_punta;
       float alto_punta;
       float fondo_punta;
};

//************************************************************************
// tocadiscos
//************************************************************************

class _tocadiscos : public _triangulos3D
{
public:
       _tocadiscos();
       void draw(_modo modo, float r, float g, float b, float grosor);

       _base base;
       _disco disco;
       _aguja aguja;
       _ruedas_sonido ruedas_sonido;
       _tapa tapa;

       _deslizador deslizador;

       float altura_figura;
       float rotacion_tapa;
       float rotacion_tapa_max;
       float rotacion_tapa_min;
};

// clase con todas las figuras

class _figuras : public _triangulos3D
{
public:
       _figuras();
       _cubo cubo;
       _piramide piramide;
       _objeto_ply obj_ply;
       _rotacion rotacion;
       _cilindro cilindro;
       _esfera esfera;
       _cono cono;
       _excavadora excavadora;

       vector<_vertex3f> perfil; // Rotacion
       _vertex3f aux;
       int num, tapa_in, tapa_su, tipo;
       
       float radio_cilindro, altura_cilindro;

       _extrusion extrusion(vector<_vertex3f> poligono, float x, float y, float z, int tapa);

       void draw(_modo modo, float r, float g, float b, float grosor);
};