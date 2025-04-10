//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_03_resize.cpp |
// ======================================
//
//	Program care arata modalitati de utilizare ale proiectiei ortogonale. Se vor desena un patrat si un sistem de axe, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	- pentru a stabili o fereastra de "decupare" intr-o scena 2D putem folosi atat functia glm::ortho, cat si indicarea explicita a transformarilor;
//
//
//	Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Define?te prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//  Identificatorii obiectelor de tip OpenGL;
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
matrRotlLocation,
codColLocation;
//	Dimensiunile ferestrei de afisare;
GLfloat
winWidth = 900, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4
myMatrix, resizeMatrix, matrTransl, matrScale, matrTransl1, matrTransl2, matrRot;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;
//	Variabile pentru proiectia ortogonala;
float
xMin = -400, xMax = 400, yMin = -400, yMax = 400;
float PI = 3.141592;				//	Valoarea lui PI;
float
deltax = xMax - xMin, deltay = yMax - yMin, // lungimile laturilor dreptunghiului decupat
xcenter = (xMin + xMax) * 0.5, ycenter = (yMin + yMax) * 0.5; // centrul dreptunghiului decupat


//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("shaders/03.vert", "shaders/03.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	// a = 150, b = 250
	// middlepoint = (100, 137)
	GLfloat Vertices[] = {
		// Margini
		-400.0f, -400.0f, 0.0f, 1.0f,
		400.0f,  -400.0f, 0.0f, 1.0f,
		400.0f, 400.0f, 0.0f, 1.0f,
		-400.0f, 400.0f, 0.0f, 1.0f,
		//  Varfuri pentru axe;
		-400.0f, 0.0f, 0.0f, 1.0f,
		400.0f,  0.0f, 0.0f, 1.0f,
		0.0f, -400.0f, 0.0f, 1.0f,
		0.0f, 400.0f, 0.0f, 1.0f,
		//  P1
		100.0f,  150.0f, 0.0f, 1.0f,
		50.0f, 200.0f, 0.0f, 1.0f,
		100.0f,  250.0f, 0.0f, 1.0f,
		150.0f,  200.0f, 0.0f, 1.0f,
		// P2
		50.0f, 125.0, 0.0f, 1.0f,
		150.0f, 75.0f, 0.0f, 1.0f,
		75.0f, 75.0f, 0.0f, 1.0f,
		50.0f, 20.0f, 0.0f, 1.0f,
	};

	GLfloat Colors[] = {
		// Gradient
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		// Culorile varfurilor din colturi;
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.8f, 0.4f, 0.0f, 1.0f,
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
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

	//  Stergerea bufferelor pentru varfuri, culori;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		//  Culoarea de fond a ecranului;
	CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();							//  Initilizarea shaderelor;
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

	// Pentru decupare avem de translatat si de scalat;
	// Este decupat dreptunghiul delimitat de xMin, xMax, yMin, yMax

	// Varianta 1 (recomandat) - Se aplica functia glm::ortho;
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);

	// Matricea de translatie pentru dreptunghi
	GLfloat angle = PI / 8;
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
	matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.0));
	matrTransl1 = glm::translate(glm::mat4(1.0f), glm::vec3(-100.f, -137.f, 0.0));
	//	Translatia 2: inversa/opusa translatiei T1;
	matrTransl2 = glm::translate(glm::mat4(1.0f), glm::vec3(100.f, 137.f, 0.0));
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	//	Matrice pentru elemente "fixe" - puncte, axe;
	//	Transmiterea variabilei uniforme pentru MATRICEA DE TRANSFORMARE spre shadere;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	codCol = 0;                                 //  Culoarea;
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_QUADS, 0, 4);

	//	Desenarea axelor;
	codCol = 1;									//	Culoarea;
	glUniform1i(codColLocation, codCol);
	glLineWidth(2.0);
	glDrawArrays(GL_LINES, 4, 4);

	//  Desenarea dreptunghiul;
	//  Matricea asociata dreptunghiul - este translatat fata de axe;
	codCol = 2;									//	Culoarea;
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLES, 12, 3);
	glDrawArrays(GL_TRIANGLES, 13, 3);

	codCol = 3;
	myMatrix = resizeMatrix * matrTransl2 * matrScale * matrRot * matrTransl1;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLES, 12, 3);
	glDrawArrays(GL_TRIANGLES, 13, 3);

	glFlush();	//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);					//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Lab 03 - Ex 03");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}
