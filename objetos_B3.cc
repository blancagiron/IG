//**************************************************************************
// Práctica 3
//**************************************************************************

#include "objetos_B3.h"
#include "file_ply_stl.hpp"
#include <time.h>

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  //**** usando vertex_array ****
  glPointSize(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawArrays(GL_POINTS, 0, vertices.size());

  /*int i;
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
    glVertex3fv((GLfloat *) &vertices[i]);
    }
  glEnd();*/
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  //**** usando vertex_array ****
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);

  /*int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores()
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glColor3f(colores_caras[i].r, colores_caras[i].g, colores_caras[i].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
  switch (modo)
  {
  case POINTS:
    draw_puntos(r, g, b, grosor);
    break;
  case EDGES:
    draw_aristas(r, g, b, grosor);
    break;
  case SOLID:
    draw_solido(r, g, b);
    break;
  case SOLID_COLORS:
    draw_solido_colores();
    break;
  case SOLID_EDGES:
    draw_personalizado(r, g, b, grosor);
    break;
  }
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  srand(time(NULL));
  for (i = 0; i < n_c; i++)
  {
    colores_caras[i].r = rand() % 1000 / 1000.0;
    colores_caras[i].g = rand() % 1000 / 1000.0;
    colores_caras[i].b = rand() % 1000 / 1000.0;
  }
}

//*************************************************************************
// dibujar en modo sólido pero con aristas
//*************************************************************************
void _triangulos3D::draw_personalizado(float r, float g, float b, float grosor)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(0, 0, 0);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  for (i = 0; i < n_c; i++)
  {
    if (i % 2 == 0)
    {
      colores_caras[i].r = r1;
      colores_caras[i].g = g1;
      colores_caras[i].b = b1;
    }
    else
    {
      colores_caras[i].r = r2;
      colores_caras[i].g = g2;
      colores_caras[i].b = b2;
    }
  }
}

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
  // vertices
  vertices.resize(8);
  vertices[0].x = -tam;
  vertices[0].y = -tam;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = -tam;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = tam;
  vertices[2].z = tam;
  vertices[3].x = -tam;
  vertices[3].y = tam;
  vertices[3].z = tam;
  vertices[4].x = -tam;
  vertices[4].y = -tam;
  vertices[4].z = -tam;
  vertices[5].x = tam;
  vertices[5].y = -tam;
  vertices[5].z = -tam;
  vertices[6].x = tam;
  vertices[6].y = tam;
  vertices[6].z = -tam;
  vertices[7].x = -tam;
  vertices[7].y = tam;
  vertices[7].z = -tam;

  // triangulos
  caras.resize(12);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 3;
  caras[1]._0 = 3;
  caras[1]._1 = 1;
  caras[1]._2 = 2;
  caras[2]._0 = 1;
  caras[2]._1 = 5;
  caras[2]._2 = 2;
  caras[3]._0 = 5;
  caras[3]._1 = 6;
  caras[3]._2 = 2;
  caras[4]._0 = 5;
  caras[4]._1 = 4;
  caras[4]._2 = 6;
  caras[5]._0 = 4;
  caras[5]._1 = 7;
  caras[5]._2 = 6;
  caras[6]._0 = 0;
  caras[6]._1 = 7;
  caras[6]._2 = 4;
  caras[7]._0 = 0;
  caras[7]._1 = 3;
  caras[7]._2 = 7;
  caras[8]._0 = 3;
  caras[8]._1 = 2;
  caras[8]._2 = 7;
  caras[9]._0 = 2;
  caras[9]._1 = 6;
  caras[9]._2 = 7;
  caras[10]._0 = 0;
  caras[10]._1 = 1;
  caras[10]._2 = 4;
  caras[11]._0 = 1;
  caras[11]._1 = 5;
  caras[11]._2 = 4;

  // colores de las caras
  colors_random();
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
  int i;
  // vertices
  vertices.resize(5);
  vertices[0].x = -tam;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = -tam;
  vertices[3].x = -tam;
  vertices[3].y = 0;
  vertices[3].z = -tam;
  vertices[4].x = 0;
  vertices[4].y = al;
  vertices[4].z = 0;

  caras.resize(6);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 2;
  caras[1]._2 = 4;
  caras[2]._0 = 2;
  caras[2]._1 = 3;
  caras[2]._2 = 4;
  caras[3]._0 = 3;
  caras[3]._1 = 0;
  caras[3]._2 = 4;
  caras[4]._0 = 3;
  caras[4]._1 = 1;
  caras[4]._2 = 0;
  caras[5]._0 = 3;
  caras[5]._1 = 2;
  caras[5]._2 = 1;

  // colores de las caras
  colors_random();
}
//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z, int tapa_su)
{
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice

  num_aux = poligono.size();
  vertices.resize(num_aux * 2);
  for (i = 0; i < num_aux; i++)
  {
    vertices[2 * i] = poligono[i];
    vertices[2 * i + 1].x = poligono[i].x + x;
    vertices[2 * i + 1].y = poligono[i].y + y;
    vertices[2 * i + 1].z = poligono[i].z + z;
  }

  // tratamiento de las caras

  caras.resize(num_aux * 2);
  int c = 0;
  for (i = 0; i < num_aux; i++)
  {
    caras[c]._0 = i * 2;
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
    caras[c]._0 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2) + 1;
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
  }

  if (tapa_su == 1)
  {
    // Tapa inferior
    _vertex3i tapa_inferior;
    int indice_centro_inferior = vertices.size();
    vertices.push_back({0, 0, 0}); // Añadimos el centro de la tapa inferior

    for (i = 0; i < num_aux; i++)
    {
      tapa_inferior._0 = 2 * i;                   // Vértice en la base
      tapa_inferior._1 = 2 * ((i + 1) % num_aux); // Siguiente vértice en la base
      tapa_inferior._2 = indice_centro_inferior;  // Centro de la tapa inferior
      caras.push_back(tapa_inferior);
    }
  }

  // colores de las caras
  colors_random();
}
//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::parametros(char *archivo)
{
  int i, n_ver, n_car;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);
  // vértices

  for (i = 0; i < n_ver; i++)
  {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  // vértices
  for (i = 0; i < n_car; i++)
  {
    caras[i].x = car_ply[3 * i];
    caras[i].y = car_ply[3 * i + 1];
    caras[i].z = car_ply[3 * i + 2];
  }

  // colores
  colors_random();
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num,
                           int tapa_in, int tapa_su, int tipo)
{
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio;

  // tratamiento de los vértice
  radio = sqrt(perfil[0].x * perfil[0].x + perfil[0].y * perfil[0].y);

  num_aux = perfil.size();
  if (tipo == 2)
    num_aux = 1;
  vertices.resize(num_aux * num);

  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux; i++)
    {
      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].y;
      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  // tratamiento de las caras
  if (tipo < 2)
  {
    for (j = 0; j < num; j++)
    {
      for (i = 0; i < num_aux - 1; i++)
      {
        cara_aux._0 = i + j * num_aux;
        cara_aux._1 = i + ((j + 1) % num) * num_aux;
        cara_aux._2 = i + 1 + j * num_aux;
        caras.push_back(cara_aux);

        cara_aux._0 = i + ((j + 1) % num) * num_aux;
        cara_aux._1 = i + 1 + ((j + 1) % num) * num_aux;
        cara_aux._2 = i + 1 + j * num_aux;
        caras.push_back(cara_aux);
      }
    }
  }

  // tapa inferior
  if (tapa_in == 1)
  {
    // punto central de la tapa
    vertice_aux.x = 0.0;
    if (tipo == 1)
      vertice_aux.y = -radio;
    else
      vertice_aux.y = perfil[0].y;
    vertice_aux.z = 0.0;
    vertices.push_back(vertice_aux);
    // caras tapa inferior
    int indice_centro_inferior = vertices.size() - 1;

    // caras tapa inferior
    for (int j = 0; j < num; j++)
    {
      cara_aux._0 = indice_centro_inferior;
      cara_aux._1 = j * perfil.size();
      cara_aux._2 = ((j + 1) % num) * perfil.size();
      caras.push_back(cara_aux);
    }
  }

  // tapa superior

  if (tapa_su == 1)
  {
    // punto central de la tapa
    vertice_aux.x = 0.0;
    vertice_aux.y = perfil[num_aux - 1].y;
    if (tipo == 1)
      vertice_aux.y = radio;
    if (tipo == 2)
      vertice_aux.y = perfil[1].y;
    vertice_aux.z = 0.0;
    vertices.push_back(vertice_aux);

    // caras tapa superior
    int indice_centro_superior = vertices.size() - 1;

    // caras tapa superior
    for (int j = 0; j < num; j++)
    {
      cara_aux._0 = indice_centro_superior;
      cara_aux._1 = ((j + 1) % num) * perfil.size() + (perfil.size() - 1);
      cara_aux._2 = j * perfil.size() + (perfil.size() - 1);
      caras.push_back(cara_aux);
    }
  }

  // colores de las caras
  colors_random();
}

//************************************************************************
//************************************************************************

//************************************************************************
// objeto cilindro (caso especial de rotacion)
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = -altura / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = radio;
  aux.y = altura / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  parametros(perfil, num, 1, 1, 0);
}

//************************************************************************
// objeto cono (caso especial de rotacion)
//************************************************************************

_cono::_cono(float radio, float altura, int num, int tapa)
{
  vector<_vertex3f> perfil;
  perfil.push_back(_vertex3f(radio, 0, 0));  // Punto en la base
  perfil.push_back(_vertex3f(0, altura, 0)); // Vértice del cono

  // Generar vértices por revolución
  for (int i = 0; i < num; i++)
  {
    float angulo = 2.0 * M_PI * i / num;
    for (int j = 0; j < perfil.size(); j++)
    {
      _vertex3f vertice;
      vertice.x = perfil[j].x * cos(angulo);
      vertice.z = perfil[j].x * sin(angulo);
      vertice.y = perfil[j].y;
      vertices.push_back(vertice);
    }
  }

  // Generar caras
  for (int i = 0; i < num; i++)
  {
    int siguiente = (i + 1) % num;
    // Cara lateral
    caras.push_back(_vertex3i(i * 2, siguiente * 2, i * 2 + 1));
    caras.push_back(_vertex3i(siguiente * 2, siguiente * 2 + 1, i * 2 + 1));
  }

  if (tapa == 1)
  {
    // Generar tapa inferior
    int vertice_inferior = vertices.size();
    vertices.push_back(_vertex3f(0, 0, 0)); // Vértice central de la base
    for (int i = 0; i < num; i++)
    {
      int siguiente = (i + 1) % num;
      caras.push_back(_vertex3i(vertice_inferior, siguiente * 2, i * 2));
    }
  }

  // Colorear las caras aleatoriamente
  colors_random();
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
//************************************************************************

_esfera::_esfera(float radio, int latitud, int longitud)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;
  for (i = 1; i < latitud; i++)
  {
    aux.x = radio * cos(M_PI * i / (latitud * 1.0) - M_PI / 2.0);
    aux.y = radio * sin(M_PI * i / (latitud * 1.0) - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);
  }
  parametros(perfil, longitud, 1, 1, 1);
}

//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{
}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{
}

//************************************************************************
// objeto montaña fractal
//************************************************************************

float gauss(float ga, float gf)
{
  float sum;
  int i;
  sum = 0.0;
  for (i = 0; i < 4; i++)
    sum = sum + rand() % 32767;
  return gf * sum / 4.0 - ga;
}

_montana::_montana(int nivelmax, float sigma, float h)

{

  if (nivelmax > 8)
    nivelmax = 8;
  int i, j, etapa;
  float ga = sqrt(12.0);
  float gf = 2 * ga / (32767 * 1.0);
  int num = pow(2, nivelmax) + 1;
  srand(time(NULL));

  vertices.resize(num * num);

  for (j = 0; j < num; j++)
    for (i = 0; i < num; i++)
    {
      vertices[i + j * num].x = -0.1 * (num - 1) / 2.0 + i * 0.1;
      vertices[i + j * num].z = -0.1 * (num - 1) / 2.0 + j * 0.1;
      vertices[i + j * num].y = 0.0;
    }

  vertices[0].y = sigma * gauss(ga, gf);
  vertices[num - 1].y = sigma * gauss(ga, gf);
  vertices[num * (num - 1)].y = sigma * gauss(ga, gf);
  vertices[num * num - 1].y = sigma * gauss(ga, gf);

  int d1 = num - 1;
  int d2 = (num - 1) / 2;

  for (etapa = 0; etapa < nivelmax; etapa++)
  {
    sigma = sigma * pow(0.5, 0.5 * h);
    for (j = d2; j < num - d2; j = j + d1)
      for (i = d2; i < num - d2; i = i + d1)
      {
        vertices[i + j * num].y = sigma * gauss(ga, gf) +
                                  (vertices[i + d2 + (j + d2) * num].y + vertices[i + d2 + (j - d2) * num].y +
                                   vertices[i - d2 + (j + d2) * num].y + vertices[i - d2 + (j - d2) * num].y) /
                                      4.0;
      }
    sigma = sigma * pow(0.5, 0.5 * h);
    for (i = d2; i < num - d2; i = i + d1)
    {
      vertices[i].y = sigma * gauss(ga, gf) + (vertices[i + d2].y +
                                               vertices[i - d2].y + vertices[i + d2 * num].y) /
                                                  3.0;
      vertices[i + num * (num - 1)].y = sigma * gauss(ga, gf) +
                                        (vertices[i + d2 + num * (num - 1)].y +
                                         vertices[i - d2 + num * (num - 1)].y +
                                         vertices[i + (num - 1 - d2) * num].y) /
                                            3.0;
      vertices[i * num].y = sigma * gauss(ga, gf) + (vertices[(i + d2) * num].y +
                                                     vertices[(i - d2) * num].y + vertices[d2 + i * num].y) /
                                                        3.0;
      vertices[num - 1 + i * num].y = sigma * gauss(ga, gf) +
                                      (vertices[num - 1 + (i + d2) * num].y +
                                       vertices[num - 1 + (i - d2) * num].y +
                                       vertices[num - 1 - d2 + i * num].y) /
                                          3;
    }

    for (j = d2; j < num - d2; j = j + d1)
      for (i = d1; i < num - d2; i = i + d1)
        vertices[i + j * num].y = sigma * gauss(ga, gf) +
                                  (vertices[i + (j + d2) * num].y + vertices[i + (j - d2) * num].y +
                                   vertices[i + d2 + j * num].y + vertices[i - d2 + j * num].y) /
                                      4.0;
    for (j = d1; j < num - d2; j = j + d1)
      for (i = d2; i < num - d2; i = i + d1)
        vertices[i + j * num].y = sigma * gauss(ga, gf) +
                                  (vertices[i + (j + d2) * num].y + vertices[i + (j - d2) * num].y +
                                   vertices[i + d2 + j * num].y + vertices[i - d2 + j * num].y) /
                                      4.0;

    d1 = (int)d1 / 2;
    d2 = (int)d2 / 2;
  }

  // caras
  caras.resize((num - 1) * (num - 1) * 2);
  int c = 0;
  for (j = 0; j < num - 1; j++)
    for (i = 0; i < num - 1; i++)
    {
      caras[c]._0 = i + j * num;
      caras[c]._1 = i + 1 + j * num;
      caras[c]._2 = i + 1 + (j + 1) * num;
      c = c + 1;
      caras[c]._0 = i + j * num;
      caras[c]._1 = i + 1 + (j + 1) * num;
      caras[c]._2 = i + (j + 1) * num;
      c = c + 1;
    }
  // colores de las caras
  colors_chess(0.2, 1.0, 0.2, 0.3, 0.8, 0.1);
}

//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

_pala::_pala(float radio, float ancho, int num)
{
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int i, j;

  vertice_aux.x = radio;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  perfil.push_back(vertice_aux);
  vertice_aux.z = ancho / 2.0;
  perfil.push_back(vertice_aux);

  // tratamiento de los vértices

  for (j = 0; j <= num; j++)
  {
    for (i = 0; i < 2; i++)
    {
      vertice_aux.x = perfil[i].x * cos(M_PI * j / (1.0 * num)) -
                      perfil[i].y * sin(M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].x * sin(M_PI * j / (1.0 * num)) +
                      perfil[i].y * cos(M_PI * j / (1.0 * num));
      vertice_aux.z = perfil[i].z;
      vertices.push_back(vertice_aux);
    }
  }

  // tratamiento de las caras

  for (j = 0; j < num; j++)
  {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = (j + 1) * 2 + 1;
    caras.push_back(cara_aux);

    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = j * 2 + 1;
    caras.push_back(cara_aux);
  }

  // tapa inferior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++)
  {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  // tapa superior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++)
  {
    cara_aux._0 = j * 2 + 1;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

//************************************************************************
// brazo
//************************************************************************

_brazo::_brazo()
{
  ancho = 0.6;
  alto = 0.1;
  fondo = 0.1;
  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  glTranslatef(0.5, 0, 0);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
  ancho = 0.4;
  alto = 0.6;
  fondo = 0.4;
  cubo.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion()
{
  ancho = 1.2;
  alto = 0.3;
  fondo = 0.8;
  radio = 0.15;
  base.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glTranslatef(2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora()
{
  giro_cabina = 0.0;
  giro_primer_brazo = 0.0;
  giro_primer_brazo_max = 0;
  giro_primer_brazo_min = -90;
  giro_segundo_brazo = 0.0;
  giro_segundo_brazo_max = 30;
  giro_segundo_brazo_min = 0;
  giro_pala = 0.0;
  giro_pala_max = 50.0;
  giro_pala_min = -90.0;

  tamanio_pala = 0.15;
};

void _excavadora::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();

  sustentacion.draw(modo, r, g, b, grosor);

  glTranslatef(0, (cabina.alto + sustentacion.alto) / 2.0, 0);
  glRotatef(giro_cabina, 0, 1, 0);
  cabina.draw(modo, r, g, b, grosor);

  glTranslatef(cabina.ancho / 2.0, 0, 0);
  glRotatef(giro_segundo_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_primer_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_pala, 0, 0, 1);
  glTranslatef(tamanio_pala, 0, 0);
  glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
  pala.draw(modo, r, g, b, grosor);

  glPopMatrix();
};

//************************************************************************
// objeto articulado -> tocadiscos
//************************************************************************
void drawEstrella(float radio, float grosor, int num_puntas, float r, float g, float b)
{

  // Establecer el color
  glColor3f(r, g, b);
  glLineWidth(grosor);

  // Dibujar la estrella de 16 puntas
  glPushMatrix();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0.0f, 0.0f); // Centro de la estrella
  for (int i = 0; i < num_puntas * 2 + 1; ++i)
  {
    float angulo = i * M_PI / num_puntas;                     // Ángulo actual
    float radio_actual = (i % 2 == 0) ? radio : radio / 3.0f; // Alternar entre el radio exterior e interior
    float x = radio_actual * cos(angulo);                     // Coordenada X
    float y = radio_actual * sin(angulo);                     // Coordenada Y
    glVertex2f(x, y);                                         // Añadir vértice
  }
  glEnd();
  glPopMatrix();

  glColor3f(0.0f, 0.0f, 0.0f); // Negro

  // Dibujar el contorno de la estrella de 16 puntas
  glPushMatrix();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < num_puntas * 2 + 1; ++i)
  {
    float angulo = i * M_PI / num_puntas;                     // Ángulo actual
    float radio_actual = (i % 2 == 0) ? radio : radio / 3.0f; // Alternar entre el radio exterior e interior
    float x = radio_actual * cos(angulo);                     // Coordenada X
    float y = radio_actual * sin(angulo);                     // Coordenada Y
    glVertex2f(x, y);                                         // Añadir vértice
  }
  glEnd();
  glPopMatrix();
}
//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// circulo
//************************************************************************

_circulo::_circulo(float r)
{
  radio = r;
  num = 100;
}

_circulo::_circulo()
{
}
void _circulo::draw(_modo modo, float r, float g, float b, float grosor)
{

  // Establecer el color
  glColor3f(r, g, b);
  glLineWidth(grosor);

  // Dibujar el círculo relleno
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0, 0); // Centro del círculo
  for (int i = 0; i <= num; ++i)
  {
    float theta = 2.0f * M_PI * float(i) / float(num); // Ángulo actual
    float x = radio * cos(theta);                      // Coordenada X
    float y = radio * sin(theta);                      // Coordenada Y
    glVertex2f(x, y);                                  // Añadir vértice
  }
  glEnd();

  // Dibujar el contorno del círculo
  glColor3f(0, 0, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < num; ++i)
  {
    float theta = 2.0f * M_PI * float(i) / float(num); // Ángulo actual
    float x = radio * cos(theta);                      // Coordenada X
    float y = radio * sin(theta);                      // Coordenada Y
    glVertex2f(x, y);                                  // Añadir vértice
  }
  glEnd();
}

//************************************************************************
// rectangulo
//************************************************************************

_rectangulo::_rectangulo(float an, float alt)
{
  ancho = an;
  alto = alt;
}

void _rectangulo::draw(_modo modo, float r, float g, float b, float grosor)
{

  glColor3f(r, g, b);
  glLineWidth(grosor);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_QUADS);
  glVertex3f(-ancho / 2.0, -alto / 2.0, 0.0);
  glVertex3f(ancho / 2.0, -alto / 2.0, 0.0);
  glVertex3f(ancho / 2.0, alto / 2.0, 0.0);
  glVertex3f(-ancho / 2.0, alto / 2.0, 0.0);
  glEnd();

  glColor3f(0, 0, 0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-ancho / 2.0, -alto / 2.0, 0.0);
  glVertex3f(ancho / 2.0, -alto / 2.0, 0.0);
  glVertex3f(ancho / 2.0, alto / 2.0, 0.0);
  glVertex3f(-ancho / 2.0, alto / 2.0, 0.0);
  glEnd();
};

//************************************************************************
// deslizador decorativo
//************************************************************************

_deslizador::_deslizador()
{
  ancho_base_deslizador = 0.2;
  alto_base_deslizador = 0.1;
  largo_base_deslizador = 3;
  radio = 0.7;
  alto_pieza = 0.35;

  pos_pieza = 0.5;
  pos_pieza_min = 1.0;
  pos_pieza_max = -1.0;

  pieza = _cilindro(radio, alto_pieza, 3);
};

void _deslizador::draw(_modo modo, float r, float g, float b, float grosor)
{

  // dibujar la base
  glPushMatrix();
  glScalef(ancho_base_deslizador, alto_base_deslizador, largo_base_deslizador);
  base_deslizador.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // dibujar la pieza

  glPushMatrix();
  glTranslatef(0, 0.1, pos_pieza);
  glRotatef(90, 0, 1, 0);
  glScalef(radio, alto_pieza, radio);
  pieza.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// disco
//************************************************************************

_disco::_disco()
{
  radio = 3.0;
  mini_disco = _circulo(radio);
  disco.parametros("disco");
  rotacion_disco = 0.0;
}

void _disco::draw(_modo modo, float r, float g, float b, float grosor)
{

  glPushMatrix(); // movimiento del disco
  glRotatef(rotacion_disco, 0, 1, 0);

  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  glScalef(0.035, 0.035, 0.035);
  disco.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  // dibujamos el mini disco
  glPushMatrix();
  glTranslatef(0.0, 0.2, 0.0);
  glRotatef(90, 1, 0, 0);
  mini_disco.draw(modo, 1.0, 0.0, 0.0, grosor);
  glPopMatrix();

  // dibujar estrella en un lado del disco como decoracion
  glPushMatrix();
  glTranslatef(-6.0, 0.2, 0.0);
  glRotatef(90, 1, 0, 0);
  drawEstrella(1.5, 0.01, 7, 1.0, 0.0, 0.0);
  glPopMatrix();

  glPopMatrix();
};

//************************************************************************
// rueda sonido (decoracion)
//************************************************************************

_ruedas_sonido::_ruedas_sonido()
{
  radio1 = 1.5;
  radio2 = 0.8;

  altura1 = 0.9;
  altura2 = 0.5;

  radio_circulo1 = 0.4;
  circulo1 = _circulo(radio_circulo1);
  rotacion_ruedas = 0.0;
  rotacion_ruedas_max = 200.0;
}

void _ruedas_sonido::draw(_modo modo, float r, float g, float b, float grosor)
{

  // mover las ruedas
  glPushMatrix();
  glRotatef(rotacion_ruedas, 0, 1, 0);

  glPushMatrix();

  // Dibujar la rueda 1
  glScalef(radio1, altura1, radio1);
  rueda1.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar el circulo 1 encima de la rueda 1
  glPushMatrix();
  glTranslatef(0.3, altura1 + 0.2, -1);
  glRotatef(90, 1, 0, 0);
  glScalef(radio_circulo1, radio_circulo1, radio_circulo1);
  circulo1.draw(modo, 1.0, 0.0, 0.0, 1);
  glPopMatrix();

  glPopMatrix();
};

//************************************************************************
// tapa
//************************************************************************

_tapa::_tapa()
{
  poligono = {
      _vertex3f(-22.5, 0, -12.5), // Vértice 0
      _vertex3f(22.5, 0, -12.5),  // Vértice 1
      _vertex3f(22.5, 0, 12.5),   // Vértice 2
      _vertex3f(-22.5, 0, 12.5)   // Vértice 3
  };

  tapa = _extrusion(poligono, 0, 8, 0, 1);
}

void _tapa::draw(_modo modo, float r, float g, float b, float grosor)
{
  // Dibujar la tapa

  glPushMatrix();
  glTranslatef(0, 12.5, -8);
  glRotatef(90, 1, 0, 0);

  tapa.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

//************************************************************************
// base
//************************************************************************

_base::_base()
{
  ancho_base = 45.0;
  alto_base = 5.0;
  largo_base = 25.0;

  ancho_rectangulo = 43.0;
  alto_rectangulo = 23.0;

  ancho_decoracion = 5.0;
  alto_decoracion = 20.0;

  ancho_decoracion_mini = 4.0;
  alto_decoracion_mini = 7.0;

  ancho_base_tocadiscos = 55.0;
  alto_base_tocadiscos = 1;
  largo_base_tocadiscos = 30;

  ancho_deco_cubo = 6.0;
  alto_deco_cubo = 4;
  largo_deco_cubo = 0;

  // figuras decorativas
  radio_figura_decor = 1.5;
  altura_figura_decor = 0.9;
  figura = _cilindro(radio_figura_decor, altura_figura_decor, 20);

  deco_rectangulo_mini = _rectangulo(ancho_decoracion_mini, alto_decoracion_mini);
  base_rectangulo = _rectangulo(ancho_rectangulo, alto_rectangulo);
  deco_rectangulo = _rectangulo(ancho_decoracion, alto_decoracion);

  base_disco.parametros("base_disco");
  disco.parametros("disco");

  // tapa = _rectangulo_hueco(ancho_rectangulo + 2, alto_rectangulo + 2, 6);
  radio = 4.0;
  altura = 1.0;
};

void _base::draw(_modo modo, float r, float g, float b, float grosor)
{
  // Dibujamos las patas en las esquinas
  glPushMatrix();
  glTranslatef(-largo_base / 2 - 4, 0, -ancho_base / 8 - 1);
  glScalef(radio, altura, radio);
  pata.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(largo_base / 2 + 4, 0, -ancho_base / 8 - 1);
  glScalef(radio, altura, radio);
  pata.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-largo_base / 2 - 4, 0, ancho_base / 8 + 1);
  glScalef(radio, altura, radio);
  pata.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(largo_base / 2 + 4, 0, ancho_base / 8 + 1);
  glScalef(radio, altura, radio);
  pata.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();
  // FIN PATAS

  // BASE RECTANGULAR
  glPushMatrix();
  glTranslatef(0, 3.0, 0);
  glScalef(ancho_base, alto_base, largo_base);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Decoración de la base
  glPushMatrix();
  glTranslatef(-ancho_base / 2 + 5, alto_base / 2 + 0.5, 12.8);
  glScalef(ancho_deco_cubo, alto_deco_cubo, largo_deco_cubo);
  deco_cubo.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ancho_base / 2 - 5, alto_base / 2 + 0.5, 12.8);
  glScalef(ancho_deco_cubo, alto_deco_cubo, largo_deco_cubo);
  deco_cubo.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  // Dibujamos la figura decorativa con estrellas
  glPushMatrix();
  glTranslatef(0, alto_base / 2 + 0.5, 12.8);
  glRotatef(90, 1, 0, 0);
  glScalef(radio_figura_decor, altura_figura_decor, radio_figura_decor);
  figura.draw(modo, 1.0, 0.0, 0.0, grosor);
  glPopMatrix();

  // Dibujar estrellas
  glPushMatrix();
  glTranslatef(0, alto_base / 2 + 0.5, 13.5);
  drawEstrella(1.5, 0.5, 8, 0.0, 0.0, 1.0);
  glPopMatrix();

  // dibujamos las clavijas
  glPushMatrix();
  glTranslatef(-11, alto_base / 2 + 1, 12.8);
  glRotatef(90, 1, 0, 0);
  glScalef(radio_figura_decor * 0.2, altura_figura_decor * 1.2 + 1, radio_figura_decor * 0.2);
  figura.draw(modo, 0.6, 0.6, 0.6, 2);
  glPopMatrix();
  // dibujamos las clavijas
  glPushMatrix();
  glTranslatef(-12.4, alto_base / 2 + 1, 12.8);
  glRotatef(90, 1, 0, 0);
  glScalef(radio_figura_decor * 0.2, altura_figura_decor * 1.2 + 1, radio_figura_decor * 0.2);
  figura.draw(modo, 0.6, 0.6, 0.6, 2);
  glPopMatrix();

  // dibujamos las clavijas
  glPushMatrix();
  glTranslatef(-9.6, alto_base / 2 + 1, 12.8);
  glRotatef(90, 1, 0, 0);
  glScalef(radio_figura_decor * 0.2, altura_figura_decor * 1.2 + 1, radio_figura_decor * 0.2);
  figura.draw(modo, 0.6, 0.6, 0.6, 2);
  glPopMatrix();

  // Dibujamos el rectángulo encima
  glPushMatrix();
  glTranslatef(0, alto_base + 0.7, 0);
  glRotatef(90, 1, 0, 0);
  base_rectangulo.draw(modo, 0.75, 0.75, 0.75, grosor);
  glPopMatrix();

  // BASE DISCO

  // Dibujamos la base del disco
  glPushMatrix();
  glTranslatef(-5.0, alto_base + 1.3, -2.0);
  glScalef(0.04, 0.04, 0.04);
  base_disco.draw(modo, 0.3, 0.3, 0.3, grosor);
  glPopMatrix();

  // FIN BASE DISCO

  // AGUJA

  // Dibujamos la base de la aguja
  glPushMatrix();
  glTranslatef(13.0, alto_base + 1.1, 0.0);
  glRotatef(90, 1, 0, 0);
  deco_rectangulo.draw(modo, 0.3, 0.3, 0.3, grosor);
  glPopMatrix();

  // FIN AGUJA

  // Base de regulador de volumen
  glPushMatrix();
  glTranslatef(18.5, alto_base + 1.1, -6.5);
  glRotatef(90, 1, 0, 0);
  deco_rectangulo_mini.draw(modo, 0.3, 0.3, 0.3, grosor);
  glPopMatrix();

  // FIN BASE RECTANGULAR
};

//************************************************************************
// aguja
//************************************************************************

_aguja::_aguja()
{
  ancho_columna = 1.5;
  alto_columna = 4.0;
  fondo_columna = 1.5;

  ancho_base = 4.0;
  alto_base = 4.0;
  fondo_base = 4.0;

  ancho_pieza = 2.0;
  alto_pieza = 2.0;
  fondo_pieza = 3.0;

  rotacion_base = 0.0;
  rotacion_base_max = 50.0;
  rotacion_base_min = 0;

  subida_base = -5.0;
  subida_base_max = -15.0;
  subida_base_min = -1.0;

  radio_brazo = 0.5;
  alto_brazo = 8.0;

  ancho_punta = 0.7;
  alto_punta = 3;
  fondo_punta = 0.7;
}

void _aguja::draw(_modo modo, float r, float g, float b, float grosor)
{

  // Dibujamos la columna
  glPushMatrix();
  glTranslatef(0, 0, 0);

  glScalef(ancho_columna, alto_columna, fondo_columna);
  columna.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(rotacion_base, 0, 1, 0);
  glRotatef(subida_base, 1, 0, 0);

  // Dibujamos la base de la columna
  glPushMatrix();
  glTranslatef(0, alto_base, 0);
  glScalef(ancho_base, alto_base, fondo_base);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujamos la pieza en medio de la base
  glPushMatrix();
  glTranslatef(0, alto_base, 3.5);
  glScalef(ancho_pieza, alto_pieza, fondo_pieza);
  pieza.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujamos el brazo de la aguja
  glPushMatrix();
  glTranslatef(0, alto_base, 12);
  glRotatef(90, 1, 0, 0);

  glScalef(radio_brazo, alto_brazo + 2, radio_brazo);
  brazo.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // otra pieza
  glPushMatrix();
  glTranslatef(0, alto_base, 23);
  glScalef(ancho_pieza - 0.4, alto_pieza - 0.4, fondo_pieza - 0.4);
  pieza.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // otra pieza
  glPushMatrix();
  glTranslatef(1, alto_base - 1, 24);
  glScalef(ancho_pieza + 0.5, alto_pieza - 1.5, fondo_pieza);
  pieza.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // aguja
  glPushMatrix();
  glTranslatef(1, alto_base - 1, 24);
  glRotatef(180, 1, 0, 0);
  glScalef(ancho_punta, alto_punta, fondo_punta);
  punta.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPopMatrix(); // fin movimiento de la base
};

//************************************************************************
// tocadiscos
//************************************************************************

_tocadiscos::_tocadiscos()
{
  altura_figura = 1;
  rotacion_tapa = 10.0;
  rotacion_tapa_max = 90.0;
  rotacion_tapa_min = 0.0;
}

void _tocadiscos::draw(_modo modo, float r, float g, float b, float grosor)
{

  // BASE
  glPushMatrix();
  glTranslatef(0, altura_figura, 0);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // TAPA
  glPushMatrix();
  glTranslatef(0, base.alto_base + 1.5, -12.6);
  glRotatef(rotacion_tapa, 1, 0, 0);
  tapa.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // DISCO
  glPushMatrix();
  glTranslatef(-5.0, base.alto_base + 3.0 + altura_figura, 0.0);
  disco.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // aguja
  glPushMatrix();
  glTranslatef(13, base.alto_base + 2.4 + altura_figura, -7.5);
  glScalef(0.6, 0.6, 0.6);
  aguja.draw(modo, 0.5, 0.5, 0.5, grosor);
  glPopMatrix();

  // ruedas sonido
  glPushMatrix();
  glTranslatef(18.2, base.alto_base + 2 + altura_figura, -7.8);
  // glScalef(0.6, 0.6, 0.6);
  ruedas_sonido.draw(modo, 0.5, 0.5, 0.5, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(18.2, base.alto_base + 1.6 + altura_figura, -4.5);
  glScalef(0.6, 0.6, 0.6);
  ruedas_sonido.draw(modo, 0.5, 0.5, 0.5, grosor);
  glPopMatrix();

  // deslizador
  glPushMatrix();
  glTranslatef(18.2, base.alto_base + 1.6 + altura_figura, 4);
  glScalef(2.5, 2.5, 2.5);
  deslizador.draw(modo, 0.5, 0.5, 0.5, grosor);

  glPopMatrix();
};

_figuras::_figuras()
{
  obj_ply.parametros("beethoven"); // Cargar el objeto ply
  piramide = _piramide(0.5, 1);    // Crear la pirámide
  // rotacion
  aux.x = 1.0;
  aux.y = -1.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 1.5;
  aux.y = 0.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 1.0;
  aux.y = 1.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 1.5;
  aux.y = 1.2;
  aux.z = 0.0;
  perfil.push_back(aux);
  rotacion.parametros(perfil, 6, 1, 1, 0);
  // fin rotacion
  // cilindro
  radio_cilindro = 1.0;
  altura_cilindro = 3.0;
  cilindro = _cilindro(radio_cilindro, altura_cilindro, 20);
  // esfera
  esfera = _esfera(1.0, 12, 12);
}

void _figuras::draw(_modo modo, float r, float g, float b, float grosor)
{

  // Dibujar el cubo
  glPushMatrix();
  glTranslatef(-2, 0, -2);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar la pirámide
  glPushMatrix();
  glTranslatef(-0.5, 0, -2);
  piramide.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar objeto ply
  glPushMatrix();
  glTranslatef(1.5, 0, -2);
  glScalef(0.2, 0.2, 0.2);
  obj_ply.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar rotacion
  glPushMatrix();
  glTranslatef(0, 0, 0);
  // glRotatef(90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  rotacion.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar cilindro
  glPushMatrix();
  glTranslatef(-1, 0, 2);
  glScalef(0.5, 0.5, 0.5);
  cilindro.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar esfera
  glPushMatrix();
  glTranslatef(1, 0, 2);
  glScalef(0.5, 0.5, 0.5);
  esfera.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar cono
  glPushMatrix();
  glTranslatef(3, 0, 2);
  glScalef(0.5, 0.5, 0.5);
  cono.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Dibujar excavadora
  glPushMatrix();
  glTranslatef(-3, 0, 1);
  excavadora.draw(modo, r, g, b, grosor);
  glPopMatrix();

}