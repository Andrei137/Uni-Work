// ================================================
//              Grafica pe calculator             |
// ================================================
//       Laboratorul IV - 04_05_Cerinta2.cpp      |
// ================================================

//	Biblioteci
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "SOIL.h"			//	Biblioteca pentru texturare;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint VaoId, VboId, EboId, ProgramId, myMatrixLocation, drawOptionLocation, texture;	//  Identificatorii obiectelor de tip OpenGL;
glm::mat4 myMatrix, resizeMatrix, scaleMatrix, translationMatrix;	 //	 Variabile catre matricile de transformare;

GLfloat winWidth = 800, winHeight = 800;							 //	 Dimensiunile ferestrei de afisare;
float xMin = -275.f, xMax = 275.f, yMin = -275.f, yMax = 275.f;		 //	 Variabile pentru proiectia ortogonala;
int drawOption;

//	Functia de incarcare a texturilor in program;
void LoadTexture(const char* photoPath)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//	Desfasurarea imaginii pe orizonatala/verticala in functie de parametrii de texturare;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image(photoPath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


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
	static const GLfloat Vertices[] =
	{
		// Coordonatele varfurilor     | Culorile varfurilor  |  Coordonatele de texturare
		-25.0f, -25.0f,  0.0f,  1.0f,     1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
		 25.0f, -25.0f,  0.0f,  1.0f,	  0.0f, 1.0f, 0.0f,	      1.0f, 0.0f,
		 25.0f,  25.0f,  0.0f,  1.0f,	  0.0f, 0.0f, 1.0f,       1.0f, 1.0f,
		-25.0f,  25.0f,  0.0f,  1.0f,     1.0f, 0.0f, 1.0f,       0.0f, 1.0f
	};

	//	Indicii care determina ordinea de parcurgere a varfurilor;
	static const GLuint Indices[] =
	{
		0, 1, 2, 3
	};


	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI - COORDONATE, CULORI si TEXTURARE;
	glGenBuffers(1, &VboId);													//  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);										//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	
	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	//  Se asociaza atributul (2 =  texturare) pentru shader;
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
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
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru VARFURI(Coordonate, Culori, Textura), INDICI;
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		//  Culoarea de fond a ecranului;
	CreateShaders();							//  Initilizarea shaderelor;
	
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	drawOptionLocation = glGetUniformLocation(ProgramId, "drawOption");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);

	scaleMatrix = glm::scale(glm::vec3(2.0f, 0.5f, 1.0f));			     // matrice pentru scalare cu factori (2.0, 0.5)
	translationMatrix = glm::translate(glm::vec3(100.0f, 100.0f, 0.0f)); // matrice pentru translatie de vector (100, 100)
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //  Se curata ecranul OpenGL pentru a fi desenat noul continut;

	CreateVBO();

	//	Incarcarea texturii si legarea acesteia cu shaderul;
	LoadTexture("textures/wallpaper.png");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);


	// Patratul initial
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	drawOption = 0;
	glUniform1i(drawOptionLocation, drawOption);
	glLineWidth(5.0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(0));

	// Intai scalarea, apoi translatia
	myMatrix = resizeMatrix  * translationMatrix * scaleMatrix;
	drawOption = 1;
	glUniform1i(drawOptionLocation, drawOption);
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, (void*)(0));

	// Intai translatia, apoi scalarea
	myMatrix = resizeMatrix * scaleMatrix * translationMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	drawOption = 2;
	glUniform1i(drawOptionLocation, drawOption);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, (void*)(0));


	glutSwapBuffers();						//  Inlocuieste imaginea desenata in fereastra cu cea randata
	glFlush();								//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);					//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Lab 04 - Ex 03");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	glewInit();

	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	glutMainLoop();
	return 0;
}
