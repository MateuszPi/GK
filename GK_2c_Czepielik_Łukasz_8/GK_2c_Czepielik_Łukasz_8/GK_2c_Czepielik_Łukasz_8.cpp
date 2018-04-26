// GK_2c_Czepielik_Łukasz_8.cpp : Defines the entry point for the console application.
//
// Wariant 1) (Ostrosłup SUB Kula) OR (Torus AND Kula)

#include "stdafx.h"
#include <GL/glut.h>
#include "colors.h"
#include "gltools_extracted.h"
#include "VectorMath.cpp"

void ostroslup()
{
	GLTVector3 vNormal;
	GLTVector3 vCorners[10] = { { 0.0f, 3.00f, 0.0f }, // Góra 0
	{ -1.04f, -1.0f, -2.48f }, // Skrajny tył lewy 1
	{ 1.04f, -1.0f, -2.48f }, // Skrajny tył prawy 2
	{ -2.56f, -1.0f, -1.08f } , // Tył lewy (za środkiem) 3
	{ 2.56f, -1.0f, -1.08f } ,// Tył prawy (za środkiem) 4
	{ -2.56f, -1.0f,1.08f }, // Lewy przód (za środkiem) 5
	{ 2.56f, -1.0f, 1.08f }, // Prawy przód (za środkiem) 6
	{ -1.04f, -1.0f, 2.48f } , // Skrajny przód lewy 7
	{ 1.04f, -1.0f, 2.48f } , // Skrajny  przód prawy 8
	{ 0.0f, -1.0f, 0.0f } }; // Środek podstawy

	 // Rysowanie piramidy
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	//Rysowanie podstawy - 8 trójkątów:
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[9]);

	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[9]);

	//Ściany boczne
	gltGetNormalVector(vCorners[1], vCorners[2], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[2], vCorners[4], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[4], vCorners[6], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[6], vCorners[8], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[8], vCorners[7], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[7], vCorners[5], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[5], vCorners[3], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[3], vCorners[1], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[0]);
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// włączenie bufora szablonowego
	glEnable(GL_STENCIL_TEST);
	// rysujemy ostrosłup i uzupełniamy bufor szablonowy
	// jedynkami w tym miejscu gdzie narysujemy ostrosłup
	glStencilFunc(GL_ALWAYS, 1, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	ostroslup();
	
	// uzupełniamy bufor szablonowy dwójkami w tych miejscach
	// gdzie kula pokrywa ostroslup
	glStencilFunc(GL_ALWAYS, 2, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glutSolidSphere(2, 100, 100);

	// // czyszczenie bufora koloru i bufora głębokości
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wyłączenie testu bufora szablonowego i rysujemy niebieski torus
	glDisable(GL_STENCIL_TEST);
	glColor3d(0, 0, 1);
	glutSolidTorus(0.50, 0.6, 80, 100);
	// zielona kula 
	glColor3d(0, 1, 0);
	glutSolidSphere(0.90, 100, 100);
	// jeszcze raz pozwalamy test buforu szablonowego
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_EQUAL, 1, 255);
	ostroslup();

	// wracamy scenę
	glRotated(0.3, 1, 0, 0);
	glRotated(0.5, 0, 1, 0);
	glRotated(0.7, 0, 0, 1);
	glFlush();
	glutSwapBuffers();
}
void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	display();
}
///////////////////////////////////////////////////////////
// Wywoływana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkość
void TimerFunction(int value) {
	display();
	// Ponowne rysowanie sceny z nowymi współrzędnymi
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	float pos[4] = { 3,3,3,1 };
	float dir[3] = { -1,-1,-1 };
	GLfloat mat_specular[] = { 1,1,1,1 };
	glutInitWindowPosition(50, 10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Stencil buffer");
	glutInitDisplayMode(GL_DOUBLE | GL_RGB | GL_DEPTH);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	glutTimerFunc(33, TimerFunction, 1);
	glutMainLoop();
	return 0;
}