//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VII - 07_01_desenare_cub.cpp       |
// ============================================
//
//  Program ce deseneaza un cub, cu observator deplasabil, folosindu-se tehnicile MODERN OpenGL;
//  ELEMENTE DE NOUTATE:
//   - diverse tipuri de proiectii;
//   - folosirea indexarii pentru a trasa separat fetele si muchiile unui obiect 3D (cub);
//   - rolul testului de adancime;
//
//
//  Biblioteci
#include <windows.h>        //  Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna;
#include <GL/freeglut.h>    //  Include functii pentru:
                            //  - gestionarea ferestrelor si evenimentelor de tastatura si mouse,
                            //  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii,
                            //  - crearea de meniuri si submeniuri;
#include "loadShaders.h"    //  Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"      //  Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//  Identificatorii obiectelor de tip OpenGL;
GLuint
    VaoId,
    VboId,
    EboId,
    ProgramId,
    viewLocation,
    projLocation,
    codColLocation;
//  Dimensiunile ferestrei de afisare;
GLfloat
    winWidth = 600,
    winHeight = 600;
//  Vectori pentru matricea de vizualizare;
glm::vec3
    obs,
    pctRef,
    vert;
//  Variabile catre matricile de transformare;
glm::mat4
    view,
    projection;

//  Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;
//  Valaorea lui pi;
float PI = 3.141592;
//  Elemente pentru matricea de vizualizare;
float
    obsX = 0.0,
    obsY = 0.0,
    obsZ = 300.f,
    refX = 0.0f,
    refY = 0.0f,
    refZ = -100.f,
    vX = 0.0;
//  Elemente pentru matricea de proiectie;
float
    xMin = -300.f,
    xMax = 300.f,
    yMin = -300.f,
    yMax = 300.f,
    dNear = 100.f,
    dFar = 500.f,
    width = 600.f,
    height = 600.f,
    fov = 90.f*PI/180;

void ProcessNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'l':           //  Apasarea tastelor `l` si `r` modifica pozitia verticalei in planul de vizualizare;
        vX += 0.1;
        break;
    case 'r':
        vX -= 0.1;
        break;
    case '+':           //  Apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
        obsZ += 10;
        break;
    case '-':
        obsZ -= 10;
        break;
    }
    if (key == 27)
        exit(0);
}

void ProcessSpecialKeys(int key, int xx, int yy)
{
    switch (key)                //  Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
    {                           //  duce la deplasarea observatorului pe axele Ox si Oy;
    case GLUT_KEY_LEFT:
        obsX -= 5;
        break;
    case GLUT_KEY_RIGHT:
        obsX += 5;
        break;
    case GLUT_KEY_UP:
        obsY += 5;
        break;
    case GLUT_KEY_DOWN:
        obsY -= 5;
        break;
    }
}

//  Crearea si compilarea obiectelor de tip shader;
//  Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
    ProgramId = LoadShaders("shaders/01.vert", "shaders/01.frag");
    glUseProgram(ProgramId);
}

//  Se initializeaza un vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
    //  Atributele varfurilor -  COORDONATE si CULORI;
    GLfloat Vertices[] =
    {
        //  Coordonatele bazei
        -75.0f, -75.0f, -45.0f, 1.0f,   0.956f, 0.541f, 0.113f,
         75.0f, -75.0f, -45.0f, 1.0f,   0.470f, 0.007f, 0.850f,
         75.0f,  75.0f, -45.0f, 1.0f,   0.998f, 0.866f, 0.007f,
        -75.0f,  75.0f, -45.0f, 1.0f,   0.160f, 0.796f, 0.180f,

        //  Coordonatele varfului
         0.0f,   0.0f,  45.0f, 1.0f,   1.0f, 1.0f, 1.0f,
    };

    //  Indicii pentru varfuri;
    GLubyte Indices[] =
    {
        0, 1, 2, 3,     //  Baza
        0, 3, 4,        //  Fata din stanga
        3, 2, 4,        //  Fata din spate
        1, 2, 4,        //  Fata din dreapta
        0, 1, 4,        //  Fata din fata

        0, 1, 2, 3,     //  Conturul bazei
        0, 4, 1, 4, 2, 4, 3, 4
    };

    //  Transmiterea datelor prin buffere;

    //  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
    glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
    glBindVertexArray(VaoId);

    //  Se creeaza un buffer pentru VARFURI - COORDONATE si CULORI;
    glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
    glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    //  Se creeaza un buffer pentru INDICI;
    glGenBuffers(1, &EboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila EboId;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);                                   //  Setarea tipului de buffer - atributele varfurilor;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    //  Se activeaza lucrul cu atribute;
    //  Se asociaza atributul (0 = coordonate) pentru shader;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
    //  Se asociaza atributul (1 =  culoare) pentru shader;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
    glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
    //  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    //  Stergerea bufferelor pentru VARFURI (Coordonate, Culori), INDICI;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VboId);
    glDeleteBuffers(1, &EboId);

    //  Eliberaea obiectelor de tip VAO;
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);       //  Culoarea de fond a ecranului;
    CreateVBO();                                //  Trecerea datelor de randare spre bufferul folosit de shadere;
    CreateShaders();                            //  Initilizarea shaderelor;
    //  Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
    viewLocation = glGetUniformLocation(ProgramId, "view");
    projLocation = glGetUniformLocation(ProgramId, "projection");
    codColLocation = glGetUniformLocation(ProgramId, "codCol");
}

//  Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //  Se curata ecranul OpenGL pentru a fi desenat noul continut (bufferul de culoare & adancime);
    glEnable(GL_DEPTH_TEST);

    //  CreateVBO(); //  Decomentati acest rand daca este cazul;
    glBindVertexArray(VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);

    //  Matricea de vizualizare;
    //  Pozitia observatorului;
    obs = glm::vec3(obsX, obsY, obsZ);
    //  Pozitia punctului de referinta;
    refX = obsX; refY = obsY;
    pctRef = glm::vec3(refX, refY, refZ);
    //  Verticala din planul de vizualizare;
    vert = glm::vec3(vX, 1.0f, 0.0f);
    view = glm::lookAt(obs, pctRef, vert);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


    projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), dNear, dFar);
    //  projection = glm::ortho(xMin, xMax, yMin, yMax, dNear, dFar);
    //  projection = glm::frustum(xMin, xMax, yMin, yMax, dNear, dFar);
    //  projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), dNear, dFar);
    //  projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), dNear);
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);


    codCol = 0;
    glUniform1i(codColLocation, codCol);

    //  Desenarea bazei
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, (void*)(0));

    //  Desenarea fetelor;
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (void*)(4));

    //  Desenarea muchiilor;
    codCol = 1;
    glUniform1i(codColLocation, codCol);
    glLineWidth(3.5);

    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(16));
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, (void*)(20));

    glutSwapBuffers();  //  Inlocuieste imaginea deseneata in fereastra cu cea randata;
    glFlush();          //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//  Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
    //  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);       //  Se folosesc 2 buffere pentru desen (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB + 1 buffer pentru adancime;
    glutInitWindowSize(winWidth, winHeight);                        //  Dimensiunea ferestrei;
    glutInitWindowPosition(100, 100);                               //  Pozitia initiala a ferestrei;
    glutCreateWindow("Lab 07 Ex 01");       //  Creeaza fereastra de vizualizare, indicand numele acesteia;

    //  Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
    //  Trebuie initializat inainte de desenare;

    glewInit();

    Initialize();                           //  Setarea parametrilor necesari pentru fereastra de vizualizare;
    glutDisplayFunc(RenderFunction);        //  Desenarea scenei in fereastra;
    glutIdleFunc(RenderFunction);           //  Asigura rularea continua a randarii;
    glutKeyboardFunc(ProcessNormalKeys);    //  Functii ce proceseaza inputul de la tastatura utilizatorului;
    glutSpecialFunc(ProcessSpecialKeys);
    glutCloseFunc(Cleanup);                 //  Eliberarea resurselor alocate de program;

    //  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
    //  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

    glutMainLoop();

    return 0;
}