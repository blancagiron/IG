//**************************************************************************
// Práctica 3
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <cstring>
#include <vector>
#include "objetos_B3.h"

// Biblioteca para el sonido
#include <AL/al.h>
#include <AL/alc.h>
#include <fstream>
// Librería para leer archivos de audio
#include <sndfile.h>

using namespace std;

// tipos
typedef enum
{
    EXTRUSION,
    MONTANA,
    BASE,
    TAPA,
    AGUJA,
    TOCADISCOS,
    DESLIZADOR,
    FIGURAS
} _tipo_objeto;
_tipo_objeto t_objeto = TOCADISCOS;
_modo modo = SOLID_EDGES;
_camara camara = CAMARA_1;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 650, Window_high = 650;

// variables booleanas para comprobar cuando esta girando el disco
bool girando = false, sonando = false;
// variables de OpenAL
ALCdevice *device;
ALCcontext *context;
ALuint buffer;
ALuint source;

// objetos
_extrusion *extrusion;
_montana montana(6, 0.9, 0.8);
_base base;
_aguja aguja;
_tocadiscos tocadiscos;
_tapa tapa;
_deslizador deslizador;
_figuras figuras;

// _objeto_ply *ply;

float giro1 = 0, giro2 = 0, giro_pieza = 0.04, giro4 = 0, giro5 = 0;
int pulsar = 0;
int paso = 0;

// velocidades
float velocidad_disco = 4;
float velocidad_deslizador = 0.5;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
    //  plano_delantero>0  plano_trasero>PlanoDelantero)
    glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -Observer_distance);
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}

void camara_pajaro()
{
    // fijar la camara
    float camara_x = 0.0;
    float camara_y = 80.0;
    float camara_z = 10.0;

    // cambiar modelo vista
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // configurar vista
    gluLookAt(camara_x, camara_y, camara_z, // Posición de la cámara
              0.0, 0.0, 0.0,                // Punto de referencia (mirando hacia el origen)
              0.0, 1.0, 0.0);               // Vector "up" (eje y positivo es la dirección "arriba")
    glTranslatef(0, -Observer_distance, 0);
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}

void camara_frontal()
{
    // Posición del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, -20, -Observer_distance - 60.0); // Empezar más alejada
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

    glDisable(GL_LIGHTING);
    glLineWidth(2);
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1, 0, 0);
    glVertex3f(-AXIS_SIZE, 0, 0);
    glVertex3f(AXIS_SIZE, 0, 0);
    // eje Y, color verde
    glColor3f(0, 1, 0);
    glVertex3f(0, -AXIS_SIZE, 0);
    glVertex3f(0, AXIS_SIZE, 0);
    // eje Z, color azul
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -AXIS_SIZE);
    glVertex3f(0, 0, AXIS_SIZE);
    glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

    switch (t_objeto)
    {
    case EXTRUSION:
        extrusion->draw(modo, 1.0, 0.0, 0.0, 5);
        break;
    case MONTANA:
        montana.draw(modo, 0.2, 0.7, 0.0, 1);
        break;
    case BASE:
        base.draw(modo, 1.0, 0.0, 0.0, 5);
        break;
    case TOCADISCOS:
        tocadiscos.draw(modo, 0.2, 0.4, 0.6, 3);
        break;
    case AGUJA:
        aguja.draw(modo, 1.0, 0.0, 0.0, 5);
        break;
    case TAPA:
        tapa.draw(modo, 1.0, 0.0, 0.0, 5);
        break;
    case DESLIZADOR:
        deslizador.draw(modo, 1.0, 0.0, 0.0, 5);
        break;
    case FIGURAS:
        figuras.draw(modo, 1.0, 0.0, 0.0, 5);
        break;
    }
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
    clean_window();
    // change_observer();
    switch (camara)
    {
    case CAMARA_1:
        camara_frontal();
        break;
    case CAMARA_ORIGINAL:
        change_observer();
        break;
    case CAMARA_PAJARO:
        camara_pajaro();

        break;
    }
    draw_axis();
    draw_objects();
    glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
    float Aspect_ratio;

    Aspect_ratio = (float)Alto1 / (float)Ancho1;
    Size_y = Size_x * Aspect_ratio;
    change_projection();
    glViewport(0, 0, Ancho1, Alto1);
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

// Imprimir información de ayuda
void printHelp()
{
    cout << "Práctica 3: Tocadiscos" << endl;
    cout << "------------------------" << endl;
    cout << "Teclas:" << endl;
    cout << "Shift + RePag: alejar cámara / Shift + AvPag: acercar cámara" << endl;
    cout << "1, 2, 3, 4, 5: Cambiar modo de visualización" << endl;
    cout << "A: Objeto jerárquico tocadiscos" << endl;
    cout << "C: Visualizar las figuras" << endl;
    cout << "X: Visualizar la extrusión" << endl;
    cout << "M: Visualizar la montaña" << endl;
    cout << "S: Visualizar la animación (tiene sonido, por si se desea bajar el volumen)" << endl;
    cout << "6: Aumentar velocidad del disco" << endl;
    cout << "7: Disminuir velocidad del disco" << endl;
    cout << "B: Cambiar a base" << endl;
    cout << "G: Cambiar a aguja" << endl;
    cout << "Y: Cambiar a tapa" << endl;
    cout << "D: Cambiar a deslizador" << endl;
    cout << "Q: Salir" << endl;
    cout << "----Cámaras----" << endl;
    cout << "I: Cámara original" << endl;
    cout << "P: Cámara pájaro" << endl;
    cout << "O: Cámara frontal" << endl;
    cout << "----Movimientos----" << endl;
    cout << "F1: Subir aguja / F2: Bajar aguja" << endl;
    cout << "F3: Mover aguja a la derecha / F4: Mover aguja a la izquierda" << endl;
    cout << "F5: Girar ruedas de sonido en sentido antihorario / F6: Girar ruedas de sonido en sentido horario" << endl;
    cout << "F7: Bajar tapa / F8: Subir tapa" << endl;
    cout << "F9: rotar disco (debe estar la aguja sobre el disco)" << endl;
    cout << "F10: mover deslizador hacia atrás / F11: mover deslizador hacia adelante" << endl;
}
void normal_key(unsigned char Tecla1, int x, int y)
{
    switch (toupper(Tecla1))
    {
    case 'Q':
        exit(0);
    case '1':
        modo = POINTS;
        break;
    case '2':
        modo = EDGES;
        break;
    case '3':
        modo = SOLID;
        break;
    case '4':
        modo = SOLID_COLORS;
        break;
    case '5':
        modo = SOLID_EDGES;
        break;
    case '6':
        velocidad_disco += 1;
        if (velocidad_disco > 8)
        {
            velocidad_disco = 8;
        }
        break;
    case '7':
        velocidad_disco -= 1;
        if (velocidad_disco < 1)
        {
            velocidad_disco = 1;
        }
        break;

    case 'C':
        t_objeto = FIGURAS;
        break;
    case 'X':
        t_objeto = EXTRUSION;
        break;
    case 'M':
        t_objeto = MONTANA;
        break;
    case 'S':
        if (pulsar == 0)
        {
            giro1 = 1.0;
            giro2 = 4.0;
            giro_pieza = 0.04;
            pulsar = 1;
        }
        else
        {
            giro1 = 0.0;
            giro2 = 0.0;
            giro_pieza = 0.0;
            pulsar = 0;
        }
        break;
    case 'B':
        t_objeto = BASE;
        break;
    case 'A':
        t_objeto = TOCADISCOS;
        break;
    case 'G':
        t_objeto = AGUJA;
        break;
    case 'Y':
        t_objeto = TAPA;
        break;
    case 'D':
        t_objeto = DESLIZADOR;
        break;
    case 'H':
        printHelp();
        break;
    case 'I':
        camara = CAMARA_ORIGINAL;
        break;
    case 'P':
        camara = CAMARA_PAJARO;
        break;
    case 'O':
        camara = CAMARA_1;
        break;
    }

    glutPostRedisplay();
}

//***************************************************************************
// sonido
//***************************************************************************
// Función para cargar un archivo .wav en un buffer de OpenAL
bool loadWavFile(const char *filename, ALuint &buffer)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error al abrir el archivo de sonido" << std::endl;
        return false;
    }

    char chunkId[4];
    file.read(chunkId, 4);

    if (strncmp(chunkId, "RIFF", 4) != 0)
    {
        std::cerr << "Formato de archivo no compatible (no es un RIFF)" << std::endl;
        return false;
    }

    file.seekg(22, std::ios::cur); // Saltamos 22 bytes hasta el número de canales
    int16_t numChannels;
    file.read(reinterpret_cast<char *>(&numChannels), sizeof(numChannels));

    int32_t sampleRate;
    file.read(reinterpret_cast<char *>(&sampleRate), sizeof(sampleRate));

    file.seekg(6, std::ios::cur); // Saltamos otros 6 bytes hasta el formato de bits
    int16_t bitsPerSample;
    file.read(reinterpret_cast<char *>(&bitsPerSample), sizeof(bitsPerSample));

    file.seekg(4, std::ios::cur); // Saltamos hasta los datos de audio
    int32_t dataSize;
    file.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));

    std::vector<char> data(dataSize);
    file.read(data.data(), dataSize);

    // Elegir el formato de OpenAL según los canales y el tamaño de bits
    ALenum format;
    if (numChannels == 1)
        format = (bitsPerSample == 16) ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
    else
        format = (bitsPerSample == 16) ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;

    // Almacenar los datos de audio en el buffer de OpenAL
    alBufferData(buffer, format, data.data(), dataSize, sampleRate);

    return true;
}

/// Función para inicializar OpenAL y cargar el archivo de sonido
void initializeSound(const char *filename)
{
    // Crear el dispositivo y contexto de OpenAL
    device = alcOpenDevice(NULL);
    if (!device)
    {
        std::cerr << "Error al abrir el dispositivo de sonido" << std::endl;
        return;
    }

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    // Generar un buffer y una fuente de sonido
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    // Abrir el archivo de sonido usando sndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile)
    {
        std::cerr << "Error al abrir el archivo de sonido" << std::endl;
        return;
    }

    // Leer los datos del archivo de sonido
    short *membuf = new short[sfinfo.frames * sfinfo.channels];
    sf_read_short(sndfile, membuf, sfinfo.frames * sfinfo.channels);
    sf_close(sndfile);

    // Cargar los datos en el buffer de OpenAL
    ALenum format = (sfinfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(buffer, format, membuf, sfinfo.frames * sfinfo.channels * sizeof(short), sfinfo.samplerate);

    // Liberar el buffer temporal
    delete[] membuf;

    // Asignar el buffer a la fuente de sonido
    alSourcei(source, AL_BUFFER, buffer);
}

// Función para reproducir el sonido
void playSound()
{
    if (!sonando)
    {
        alSourcePlay(source);
        sonando = true;
    }
}

// Función para limpiar OpenAL y liberar recursos
void cleanupSound()
{
    // Detener la fuente de sonido
    alSourceStop(source);

    // Eliminar la fuente de sonido
    alDeleteSources(1, &source);

    // Eliminar el buffer de sonido
    alDeleteBuffers(1, &buffer);

    // Destruir el contexto
    if (context)
    {
        alcDestroyContext(context);
        context = nullptr;
    }

    // Cerrar el dispositivo
    if (device)
    {
        alcCloseDevice(device);
        device = nullptr;
    }
}

// Función para detener el sonido
void stopSound()
{
    if (sonando)
    {
        alSourceStop(source);
        sonando = false;
    }
}

// Función para limpiar y cerrar OpenAL
void cleanupOpenAL()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void updateSound()
{
    if (girando)
    {
        playSound();
    }
    else
    {
        stopSound();
    }
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

    switch (Tecla1)
    {
    case GLUT_KEY_LEFT:
        Observer_angle_y--;
        break;
    case GLUT_KEY_RIGHT:
        Observer_angle_y++;
        break;
    case GLUT_KEY_UP:
        Observer_angle_x--;
        break;
    case GLUT_KEY_DOWN:
        Observer_angle_x++;
        break;
    case GLUT_KEY_PAGE_UP:
        Observer_distance *= 1.2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        Observer_distance /= 1.2;
        break;

    case GLUT_KEY_F1:
        // cout << tocadiscos.aguja.subida_base << endl;
        if (tocadiscos.rotacion_tapa != 90) // si la tapa no esta cerrada
        {
            tocadiscos.aguja.subida_base -= 1;
            if (tocadiscos.aguja.subida_base < tocadiscos.aguja.subida_base_max)
                tocadiscos.aguja.subida_base = tocadiscos.aguja.subida_base_max;
        }
        break;
    case GLUT_KEY_F2:
        if (tocadiscos.rotacion_tapa != 90) // si la tapa no esta cerrada
        {
            tocadiscos.aguja.subida_base += 1;
            if (tocadiscos.aguja.subida_base > tocadiscos.aguja.subida_base_min)
                tocadiscos.aguja.subida_base = tocadiscos.aguja.subida_base_min;
        }
        break;
    case GLUT_KEY_F5:
        tocadiscos.ruedas_sonido.rotacion_ruedas += 1;
        if (tocadiscos.ruedas_sonido.rotacion_ruedas > tocadiscos.ruedas_sonido.rotacion_ruedas_max)
            tocadiscos.ruedas_sonido.rotacion_ruedas = tocadiscos.ruedas_sonido.rotacion_ruedas_max;
        break;
    case GLUT_KEY_F6:
        tocadiscos.ruedas_sonido.rotacion_ruedas -= 1;
        if (tocadiscos.ruedas_sonido.rotacion_ruedas < 0)
            tocadiscos.ruedas_sonido.rotacion_ruedas = 0;
        break;
    case GLUT_KEY_F3:
        if (tocadiscos.rotacion_tapa != 90) // si la tapa no esta cerrada
        {
            tocadiscos.aguja.rotacion_base += 1;
            if (tocadiscos.aguja.rotacion_base > tocadiscos.aguja.rotacion_base_min)
                tocadiscos.aguja.rotacion_base = tocadiscos.aguja.rotacion_base_min;
            break;
        }

    case GLUT_KEY_F4:
        if (tocadiscos.rotacion_tapa != 90) // si la tapa no esta cerrada
        {
            tocadiscos.aguja.rotacion_base -= 1;
            if (tocadiscos.aguja.rotacion_base < -tocadiscos.aguja.rotacion_base_max)
                tocadiscos.aguja.rotacion_base = -tocadiscos.aguja.rotacion_base_max;
        }

        break;
    case GLUT_KEY_F8:
        tocadiscos.rotacion_tapa -= 1; // subimos la tapa
        // cout << tocadiscos.rotacion_tapa << endl;
        if (tocadiscos.rotacion_tapa < tocadiscos.rotacion_tapa_min)
            tocadiscos.rotacion_tapa = tocadiscos.rotacion_tapa_min;
        break;
    case GLUT_KEY_F7:
        tocadiscos.rotacion_tapa += 1; // bajamos la tapa
        if (tocadiscos.rotacion_tapa > tocadiscos.rotacion_tapa_max)
            tocadiscos.rotacion_tapa = tocadiscos.rotacion_tapa_max;
        break;
    case GLUT_KEY_F9: // si la tapa no esta cerrada y la aguja está sobre el disco

        if (tocadiscos.aguja.rotacion_base < -45 and tocadiscos.rotacion_tapa != 90 and tocadiscos.aguja.subida_base == -1.0)
        {

            tocadiscos.disco.rotacion_disco -= velocidad_disco;
            girando = true;

            // cout <<girando<< endl;
            // girando = true;
        }
        else
        {
            girando = false;
        }
        // tocadiscos.disco.rotacion_disco -= 1;
        break;

    case GLUT_KEY_F10:
        // cambiar posicion en z de pieza del deslizador
        tocadiscos.deslizador.pos_pieza += 0.05;
        if (tocadiscos.deslizador.pos_pieza > tocadiscos.deslizador.pos_pieza_min)
            tocadiscos.deslizador.pos_pieza = tocadiscos.deslizador.pos_pieza_min;
        break;

    case GLUT_KEY_F11:
        // // cambiar posicion en z de pieza del deslizador
        tocadiscos.deslizador.pos_pieza -= 0.05;
        if (tocadiscos.deslizador.pos_pieza < tocadiscos.deslizador.pos_pieza_max)
            tocadiscos.deslizador.pos_pieza = tocadiscos.deslizador.pos_pieza_max;
        break;
    }

    glutPostRedisplay();
}

//***************************************************************************
// Funcion de animación automáticam
//***************************************************************************

// void animacion()
// {

//     switch (paso)
//     {
//     case 0:
//         excavadora.giro_cabina -= giro1;
//         if (excavadora.giro_cabina < -45)
//             paso = 1;
//         break;
//     case 1:
//         excavadora.giro_primer_brazo -= giro3;
//         if (excavadora.giro_primer_brazo < -80)
//             paso = 2;
//         break;
//     case 2:
//         excavadora.giro_pala -= giro2;
//         if (excavadora.giro_pala < excavadora.giro_pala_min)
//         {
//             excavadora.giro_pala = excavadora.giro_pala_min;
//             paso = 0;
//             excavadora.giro_cabina = 0.0;
//             excavadora.giro_primer_brazo = 0.0;
//             excavadora.giro_pala = 0.0;
//         }
//         break;
//     }

//     glutPostRedisplay();
// }

void animacion_tocadiscos()
{
    switch (paso)
    {
    case 0: // Primer movimiento -> levantar la tapa y el deslizador

        tocadiscos.rotacion_tapa -= giro1;
        if (tocadiscos.rotacion_tapa <= tocadiscos.rotacion_tapa_min)
        {
            tocadiscos.rotacion_tapa = tocadiscos.rotacion_tapa_min;
            paso = 1;
        }

        break;
    case 1: // Segundo movimiento -> mover ruedas de sonido, levantar la aguja y posicionarla sobre el disco
        tocadiscos.deslizador.pos_pieza -= 0.05;
        if (tocadiscos.deslizador.pos_pieza < tocadiscos.deslizador.pos_pieza_max)
        {
            tocadiscos.deslizador.pos_pieza = tocadiscos.deslizador.pos_pieza_max;
        }
        tocadiscos.aguja.subida_base -= giro1;
        tocadiscos.ruedas_sonido.rotacion_ruedas += giro1;
        if (tocadiscos.ruedas_sonido.rotacion_ruedas > tocadiscos.ruedas_sonido.rotacion_ruedas_max)
            tocadiscos.ruedas_sonido.rotacion_ruedas = tocadiscos.ruedas_sonido.rotacion_ruedas_max;

        if (tocadiscos.aguja.subida_base < tocadiscos.aguja.subida_base_max)
            tocadiscos.aguja.subida_base = tocadiscos.aguja.subida_base_max;

        tocadiscos.aguja.rotacion_base -= giro1;
        if (tocadiscos.aguja.rotacion_base < -tocadiscos.aguja.rotacion_base_max)
        {
            tocadiscos.aguja.rotacion_base = -tocadiscos.aguja.rotacion_base_max;
            paso = 2;
        }
        break;
    case 2:
        // Tercer movimiento, mover las ruedas y bajar la aguja sobre el disco

        tocadiscos.ruedas_sonido.rotacion_ruedas -= 1;
        if (tocadiscos.ruedas_sonido.rotacion_ruedas < 0)
            tocadiscos.ruedas_sonido.rotacion_ruedas = 0;

        tocadiscos.aguja.subida_base += giro1;
        if (tocadiscos.aguja.subida_base > tocadiscos.aguja.subida_base_min)
        {
            tocadiscos.aguja.subida_base = tocadiscos.aguja.subida_base_min;
            paso = 3;
        }
        break;
    case 3: // Cuarto movimiento, si esta la aguja abajo se mueve el disco hasta que el deslizador vuelva a su sitio
        if (tocadiscos.aguja.subida_base == -1)
        {
            tocadiscos.disco.rotacion_disco -= giro2;
            // ponemos el sonido
            playSound();
        }

        // cambiar posicion en z de pieza del deslizador
        tocadiscos.deslizador.pos_pieza += 0.005;
        if (tocadiscos.deslizador.pos_pieza > tocadiscos.deslizador.pos_pieza_min)
        {
            tocadiscos.deslizador.pos_pieza = tocadiscos.deslizador.pos_pieza_min;
            paso = 4;
        }
        break;
    case 4: // Quinto movimiento, volver la aguja a su sitio
        stopSound();

        tocadiscos.aguja.subida_base -= giro1;
        if (tocadiscos.aguja.subida_base < tocadiscos.aguja.subida_base_max)
        {
            tocadiscos.aguja.subida_base = tocadiscos.aguja.subida_base_max;
        }
        tocadiscos.aguja.rotacion_base += giro1;
        if (tocadiscos.aguja.rotacion_base > tocadiscos.aguja.rotacion_base_min)
        {
            tocadiscos.aguja.rotacion_base = tocadiscos.aguja.rotacion_base_min;
            paso = 5;
        }

        break;
    case 5: // Sexto, bajar aguja
        tocadiscos.aguja.subida_base += giro1;
        if (tocadiscos.aguja.subida_base > tocadiscos.aguja.subida_base_min)
        {
            tocadiscos.aguja.subida_base = tocadiscos.aguja.subida_base_min;
            paso = 6;
        }

        break;
    case 6: // Septimo, bajar la tapa
        tocadiscos.rotacion_tapa += giro1;
        if (tocadiscos.rotacion_tapa >= tocadiscos.rotacion_tapa_max)
        {
            tocadiscos.rotacion_tapa = tocadiscos.rotacion_tapa_max;
            paso = 0;
        }
    }
    glutPostRedisplay(); // Solicitar redibujado
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Size_x = 0.5;
    Size_y = 0.5;
    Front_plane = 1;
    Back_plane = 1000;

    // se incia la posicion del observador, en el eje z
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0;
    Observer_angle_y = 0;

    // se indica el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1, 1, 1, 1);

    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{
    cout << "Pulsar H para ver las instrucciones de las teclas: " << endl;

    initializeSound("sonido.wav");

    _vertex3f aux;
    vector<_vertex3f> poligono;

    aux.x = -1.0;
    aux.y = -1.0;
    aux.z = -1.0;
    poligono.push_back(aux);
    aux.x = 1.0;
    aux.y = -1.0;
    aux.z = -1.0;
    poligono.push_back(aux);
    aux.x = 1.0;
    aux.y = -1.0;
    aux.z = 1.0;
    poligono.push_back(aux);
    aux.x = -1.0;
    aux.y = -1.0;
    aux.z = 1.0;
    poligono.push_back(aux);
    // aux.x = -1.2;
    // aux.y = 0.0;
    // aux.z = 1.0;
    // poligono.push_back(aux);

    extrusion = new _extrusion(poligono, 0.0, 2.0, 0.0, 0.0);

    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(Window_x, Window_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(Window_width, Window_high);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("PRACTICA - 3");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw);
    // asignación de la funcion llamada "change_window_size" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "normal_key" al evento correspondiente
    glutKeyboardFunc(normal_key);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_key);

    // glutIdleFunc(animacion);
    glutIdleFunc(animacion_tocadiscos);

    // funcion de inicialización
    initialize();

    // creación del objeto ply

    // ply = new _objeto_ply(argv[1]);
    

    // inicio del bucle de eventos
    glutMainLoop();
    cleanupSound();

    return 0;
}
