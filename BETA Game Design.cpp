// My First Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

#define xSize 11
#define ySize 11
#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define NONE 4
void init();
int globalX = 10;
int globalY = -17;
int globalZ = 27;
int globalDirection = NONE;
bool start = true;


class background {
public:
	class square {
	public:
		bool empty;
		square();
		~square();
	};
	int squares[xSize][ySize];
	background();
	void drawBoard();
	void drawSquares();
	void redrawSquares();
	void newBoard();
	void printSquares();
	void drawPlayer();
	void movePlayer(int direction);
	void redisplay();
	~background();

};
background::background() {//constructor, used to set every element in the array to 0
	for(int count = 0; count < ySize; count++)
	{
		for(int count2 = 0; count2 < xSize; count2++)
		{
			squares[count2][count] = 0;
		}
	}
}
void background::drawSquares() {//Only runs once on startup to generate random squares
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
				if(count2 != xSize/2 && count != 0)//This if ensures a space to place the player
				{
				glutSolidCube(2.0);//Store where the squares are
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
void background::redrawSquares()//This function is used so it doesn't keep generating random numbers each player movement
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
void background::printSquares()//Very userful function for debugging.  Displays where each peice is on the terminal window
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
void background::drawPlayer() {//This draws the player once, I probably could eliminate this later on
	GLfloat mat_amb_diff[] = {0, 1, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	glPushMatrix();
	glTranslatef(xSize - 1, 0, 2);
	glutSolidSphere(1, 50, 50);
	squares[xSize /2][0] = 2;
	glPopMatrix();
}
void background::movePlayer(int direction)
{
	GLfloat mat_amb_diff[] = {0, 1, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	static int x = xSize / 2, y = 0;//Sadly, my first static varible
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(x * 2, y * 2, 2);
	globalDirection = direction; //Check if global varible is needed
	switch(direction)
	{
	case UP:
		if(squares[x][y+1] != 0 || y+1 > ySize-1)//The ySize-1 fixes the boundries, fixes #8
		{
			glutSolidSphere(1, 50, 50);
			break;
		}
		glTranslatef(0, 2, 0); glutSolidSphere(1, 50, 50);
		squares[x][y] = 0; squares[x][y + 1] = 2; y++; 
		break;
	case LEFT:
		if(squares[x-1][y] != 0 || x-1 < 0)
		{
			glutSolidSphere(1, 50, 50);
			break;
		}
		glTranslatef(-2, 0, 0); glutSolidSphere(1, 50, 50);
		squares[x][y] = 0; squares[x - 1][y] = 2; x += -1; 
		break;
	case RIGHT:
		if(squares[x+1][y] != 0 || x+1 > xSize-1)//The xSize-1 adds a fix to the boundries, fixes #8
		{
			glutSolidSphere(1, 50, 50);
			break;
		}
		glTranslatef(2, 0, 0); glutSolidSphere(1, 50, 50);
		squares[x][y] = 0; squares[x + 1][y] = 2; x++;
		break;
	case DOWN:
		if(squares[x][y-1] != 0 || y-1 < 0)
		{
			glutSolidSphere(1, 50, 50);
			break;
		}
		glTranslatef(0, -2, 0); glutSolidSphere(1, 50, 50);
		squares[x][y] = 0; squares[x][y - 1] = 2; y += -1; 
		break;
	default:
		glutSolidSphere(1, 50, 50);
		break;
	}
	glPopMatrix();
}
void background::redisplay()
{

}
background::~background() {//No destructor yet, TODO: Figure out how to properly close a openGL window

}

//Create an object entitled myBackground
background myBackground;

void display() {//A function containing multiple display functions
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	if(start)
	{
	myBackground.drawSquares();
	myBackground.drawPlayer();
	start = false;
	}
	else
	myBackground.movePlayer(globalDirection);//Have to use this variable, otherwise, the player wont display
	myBackground.drawBoard();
	myBackground.redrawSquares();
	
	glFlush();
}
void getGlobal()//Don't need this function anymore
{
	cout << globalX << "\n" << globalY << "\n" << globalZ << "\n";
}
void keyboard_handler(unsigned char c,int xi,int yi){
	switch(c)
	{
	case 'g':
		myBackground.printSquares();
		break;
		case 'w' :
		  globalY++;
		 init();
	break;
      case 'a' :
		  globalX--;
		 init();
	break;
      case 's' :
		  globalY--;
		  init();
	break;
	  case 'd':
		  globalX++;
		 init();
	break;
	  case 'e':
		  globalZ++;
		  init();
		  break;
	  case 'q':
		  globalZ--;
		  init();
		  break;
	  case 'r':
		  system("cls");
		  break;
    }   
	globalDirection = NONE;
}
void special_key_handler(int key,int xi,int yi) 
{
	//Come back to this
	switch(key)
	{
	case GLUT_KEY_LEFT:
		globalDirection = LEFT;
		break;
	case GLUT_KEY_UP:
		globalDirection = UP;
		break;
	case GLUT_KEY_RIGHT:
		globalDirection = RIGHT;
		break;
	case GLUT_KEY_DOWN:
		globalDirection = DOWN;
		break;
	}
	init();
}

void init() {
    glClearColor(0.8, 0.8, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(globalX, globalY, globalZ, 10, 10, 0, 0, 1, 0);

	//lighting
	
	glColor3f(1, 0, 0);
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {30, 0, 27, 0};
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
	glutPostRedisplay();
}

void prog_cont() {
}

int main(int argc, _TCHAR* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);//I can also change the window size if I need to
  glutCreateWindow("RUN!!!");//Change the name maybe? XD
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard_handler);
  
  glutIdleFunc(prog_cont);
  glutSpecialFunc(special_key_handler);
  glutMainLoop();
}
