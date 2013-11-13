// My First Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

#define xSize 11
#define ySize 11
#define max 1
#define min 0
#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
void init();
int globalX = 0;
int globalY = 0;
int globalZ = 0;
bool start = true;

class background {
public:
	class square {
	public:
		bool empty;
		square();
		~square();
	};
	bool squares[xSize][ySize];
	background();
	void drawBoard();
	void drawSquares();
	void redrawSquares();
	void newBoard();
	void printSquares();
	void drawPlayer();
	void movePlayer(int direction);
	~background();

};
background::background() {
	for(int count = 0; count < ySize; count++)
	{
		for(int count2 = 0; count2 < xSize; count2++)
		{
			squares[count2][count] = false;
		}
	}
}
void background::drawSquares() {
	int isOb;
	GLfloat mat_amb_diff[] = {1, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	srand(time(0));
    glPushMatrix();
	glTranslatef(0, 0, 2.0);
	glColor3f(1.0, 0.0, 0.0);
	for(int count = 0; count < ySize; count++)
	{
		glPushMatrix();
		for(int count2 = 0; count2 < xSize; count2++)
		{
			isOb = rand() % 10;
			if(isOb == 0)
			{
				//This if ensures a space to place the player
				if(count2 != xSize/2 && count != 0)
				{
				//Store where the squares are
				glutSolidCube(2.0);
				squares[count2][count] = true;
				}
				glTranslatef(2.0, 0, 0);
			}
			else
			glTranslatef(2.0, 0, 0);
		}
		glPopMatrix();
		glTranslatef(0, 2.0, 0);
	}
	glPopMatrix();
	glFlush();
}
void background::redrawSquares()
{
	GLfloat mat_amb_diff[] = {1, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, 2);
	for(int count = 0; count < ySize; count++)
	{
		glPushMatrix();
		for(int count2 = 0; count2 < xSize; count2++)
		{
			if(squares[count2][count] == 1)
			glutSolidCube(2.0);
			glTranslatef(2, 0, 0);
		}
		glPopMatrix();
		glTranslatef(0, 2, 0);
	}
	glPopMatrix();
	glFlush();
}
void background::drawBoard()
{
	GLfloat mat_amb_diff[] = {0, 0, 1, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();

	for(int count = 0; count < ySize; count++)
	{
		glPushMatrix();
		for(int count2 = 0; count2 < xSize; count2++)
		{
			glutSolidCube(2.0);
			glTranslatef(2.0, 0, 0);
		}
		glPopMatrix();
		glTranslatef(0, 2.0, 0);
	}
	glPopMatrix();
	glFlush();
}
void background::newBoard()
{
	glClear(GL_COLOR_BUFFER_BIT);
    background();
	drawBoard();
	drawSquares();
}
void background::printSquares()
{
	system("cls");
	for(int count = 0; count < ySize; count++)
	{
		for(int count2 = 0; count2 < xSize; count2++)
		{
			cout << squares[count2][count] << ' ';
		}
		cout << "\n";
	}
}
void background::drawPlayer() {
	GLfloat mat_amb_diff[] = {0, 1, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	//glColor3f(0, 1.0, 0);
	glPushMatrix();
	glTranslatef(xSize - 1, 0, 0);
	glutSolidSphere(1, 50, 50);
	squares[xSize - 1][0] = 2;
	glPopMatrix();
}
void background::movePlayer(int direction)
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0, 1, 0);
	switch(direction)
	{
	case UP:
		glTranslatef(0, 2, 0);
		glutSolidSphere(1, 50, 50);
		break;
	case LEFT:
		glTranslatef(-2, 0, 0);
		glutSolidSphere(1, 50, 50);
		break;
	case RIGHT:
		glTranslatef(2, 0, 0);
		glutSolidSphere(1, 50, 50);
		break;
	case DOWN:
		glTranslatef(0, -2, 0);
		glutSolidSphere(1, 50, 50);
		break;
	}
	glPopMatrix();
	glutPostRedisplay();
}
background::~background() {

}

//Create an object entitled myBackground
background myBackground;

void display() {
	glClearColor(0.7, 0.7, 0, 0);
	myBackground.drawBoard();
	if(start)
	{
	myBackground.drawSquares();
	myBackground.drawPlayer();
	start = false;
	}
	myBackground.printSquares();
	myBackground.redrawSquares();
	glFlush();
}
void getGlobal()
{
	cout << globalX << "\n" << globalY << "\n" << globalZ << "\n";
}
void keyboard_handler(unsigned char c,int xi,int yi){
	switch(c)
	{
	case 'g':
		//creating bugs
		//myBackground.newBoard();
		myBackground.printSquares();
		glutPostRedisplay();
		break;
		/*case 'w' :
		  globalY++;
		  myBackground.drawSquares();
	break;
      case 'a' :
		  globalX--;
		  myBackground.drawSquares();
	break;
      case 's' :
		  globalY--;
		  myBackground.drawSquares();
	break;
	  case 'd':
		  globalX++;
		  myBackground.drawSquares();
	break;
	  case 'e':
		  globalZ++;
		  myBackground.drawSquares();
		  break;
	  case 'q':
		  globalZ--;
		  myBackground.drawSquares();
		  break;
	  case 'r':
		  system("cls");
		  break;
		  */
    }   
	
}
void special_key_handler(int key,int xi,int yi) 
{
	//Come back to this

	/*switch(key)
	{
	case GLUT_KEY_LEFT:
		myBackground.movePlayer(LEFT);
		break;
	case GLUT_KEY_UP:
		myBackground.movePlayer(UP);
		break;
	case GLUT_KEY_RIGHT:
		myBackground.movePlayer(RIGHT);
		break;
	case GLUT_KEY_DOWN:
		myBackground.movePlayer(DOWN);
		break;
	}
	*/
}

void init() {
    glClearColor(0.8, 0.8, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, -17, 27, 10, 10, 0, 0, 1, 0);

	//lighting
	
	glColor3f(1, 0, 0);
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1, 1, 1, 0};
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {1, 1, 1, 1.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lmodel_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glutPostRedisplay();

	
}

void prog_cont() {
}

int main(int argc, _TCHAR* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("RUN!!!");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard_handler);
  
  glutIdleFunc(prog_cont);
  glutSpecialFunc(special_key_handler);
  glutMainLoop();
}
