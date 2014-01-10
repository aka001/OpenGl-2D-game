#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<stdio.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len, int flag);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(unsigned char key, int x, int y);
void lasermove(int key, int x, int y);
void basketmove_red(int key, int x, int y);
void basketmove_green(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
typedef struct laser
{
	float x1,y1,x2,y2,speedx,speedy;
}laser;

typedef struct ball
{
	float ball_x,ball_y,ball_velx,ball_vely,ball_rad;
}ball;

ball arr[1000000];
float ball1_x = 0.5f;
float ball1_y = 0.5f;
float ball1_velx = 0.02f;
float ball1_vely = 0.03f;
float ball1_rad = 0.3f;

float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;

float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = -1.8f;
float theta = 0.0f;

float gb_x=3.4f;
float gb_y=-3.4f;
float rb_x=-3.4f;
float rb_y=-3.4f;

int w,h,windowWidth,windowHeight;

int main(int argc, char **argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	w = glutGet(GLUT_SCREEN_WIDTH);
	h = glutGet(GLUT_SCREEN_HEIGHT);
	windowWidth = w * 2 / 3;
	windowHeight = h * 2 / 3;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutKeyboardFunc(handleKeypress2);
	//glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	// Draw Box
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawBox(box_len,0);

	// Draw Green box
	glPushMatrix();
	glTranslatef(3.4f,-3.4f,-5.0f);
	glColor3f(gb_x,gb_y,0.0f);
	drawBox(1.0f,1);
	glPopMatrix();

	// Draw Red Box
	glPushMatrix();
	glTranslatef(rb_x,rb_y,-5.0f);
	glColor3f(0.0f,1.0f,0.0f);
	drawBox(1.0f,2);
	glPopMatrix();

	// Draw Ball
	glPushMatrix();
	glTranslatef(ball_x, ball_y, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	drawBall(ball_rad);
	glPopMatrix();

	//Draw Triangle
	glPushMatrix();
	glTranslatef(tri_x, tri_y, 0.0f);
	glRotatef(theta, 0.0f, 0.0f, 1.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	drawTriangle();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {

	// Handle ball collisions with box
	if(ball_rad + ball1_rad > sqrt(((ball_x-ball1_x)*(ball_x-ball1_x))+(ball_y-ball1_y)*(ball_y-ball1_y)))
	{
		int x;
		x=ball_velx;
		ball_velx=ball1_velx;
		ball1_velx=x;

		//	x=ball_vely;
		//	ball_vely=ball1_vely;
		//	ball1_vely=x;
		//ball1_vely=0.4;
		ball_velx*=-1;
		ball_vely*=-1;
		ball1_velx*=-1;
		ball1_vely*=-1;
	}
	if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
		ball_velx *= -1;
	if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
		ball_vely *= -1;
	if(ball1_x + ball1_rad > box_len/2 || ball1_x - ball1_rad < -box_len/2)
		ball1_velx *= -1;
	if(ball1_y + ball1_rad > box_len/2 || ball1_y - ball1_rad < -box_len/2)
		ball1_vely *= -1;
	ball_x += ball_velx;
	ball_y += ball_vely;
	ball1_x += ball1_velx;
	ball1_y += ball1_vely;
	glutTimerFunc(10, update, 0);
	// Update position of ball
}

void drawBox(float len, int flag=0) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-len / 2, -len / 2);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(len / 2, -len / 2);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(len / 2, len / 2);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-len / 2, len / 2); glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
}

void handleKeypress2(unsigned char key, int x, int y) {

	if(key=='b' || key=='B')
	{
		glutSpecialFunc(lasermove);
	}
	else if(key=='r')
	{
		glutSpecialFunc(basketmove_red);
	}
	else if(key=='g')
	{
		glutSpecialFunc(basketmove_green);
	}
	else if(key==27)
	{
		exit(0);
	}
}
void basketmove_green(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		
		gb_x -= 0.1;
	}
	else if (key == GLUT_KEY_RIGHT)
		gb_x += 0.1;
	/*else if (key == GLUT_KEY_UP)
		gb_y += 0.1;
	else if (key == GLUT_KEY_DOWN)
		gb_y -= 0.1;*/
}
void basketmove_red(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		rb_x -= 0.1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		rb_x += 0.1;
	}
	/*else if (key == GLUT_KEY_UP)
	{
		rb_y += 0.1;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		rb_y -= 0.1;
	}*/
}
void lasermove(int key, int x, int y){
	if (key == GLUT_KEY_LEFT)
		tri_x -= 0.1;
	else if (key == GLUT_KEY_RIGHT)
		tri_x += 0.1;
	else if (key == GLUT_KEY_UP)
		tri_y += 0.1;
	else if (key == GLUT_KEY_DOWN)
		tri_y -= 0.1;
	else
	{
		printf("here\n");
		glutKeyboardFunc(handleKeypress1);
		glutKeyboardFunc(handleKeypress2);	
	}
}

void handleMouseclick(int button, int state, int x, int y) {

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			theta += 15;
		else if (button == GLUT_RIGHT_BUTTON)
			theta -= 15;
	}
}
