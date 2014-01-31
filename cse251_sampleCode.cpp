#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstring>

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
void handleMouseDrag(int,int);
void changeit(int value);
void drawLaser();
void generateSpider(int value);
void exitit(int value);
void speedchange(int value);
void drawGluCylinder(float height,float radius,float slices,float stacks); 
void drawrect(float,float);
void drawrect1(float,float);
void drawrect2(float,float);
void drawrect3(float,float);
void drawrect4(float,float);
void drawrect5(float,float);
void generateLaser(float,float,float);
void drawleg1(float,float,float,float); 
void DrawEllipse(float, float);
void drawEndGame(void);
void Score();

// Global Variables
typedef struct laser
{
	float x1,y1,x2,y2,theta;
}laser;
vector <laser> lser;

typedef struct rectangle
{
	float x1,y1,x2,y2,flag;
	int flg,check;
	float spider_x,spider_y,spider_z;
	float speed,min_speed,max_speed;
}spider;
vector <spider> spidy;

float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = -0.875*box_len;
float theta = 0.0f;

int green_flag=0,red_flag=0,once_flag=1;
float gb_x=0.9*box_len;
float gb_y=-0.95*box_len;
float rb_x=-0.9*box_len;
float rb_y=-0.95*box_len;

float tri_limx1=-0.9*box_len,tri_limx2=0.9*box_len;
float speed_min=0.01f,speed_max=0.05f;

int update_flag=1;
int start_flag=1;

int score=0;

char selectit;

int ball_flag=1,tri_flag=1,decide,exit_flag=0;

int default_flag=1,space_flag=1;

int w,h,windowWidth,windowHeight;

float gb_limx1=-0.775*box_len,gb_limx2=0.8*box_len,rb_limx1=-0.8*box_len,rb_limx2=0.775*box_len;

//laser variables
float laser_len=0.2*box_len;
//tank variables 
float tank1_hei=0.1*box_len*0.4; 
float tank1_wid=0.1*box_len;

float tank2_hei=0.1*box_len*0.6; 
float tank2_wid=0.05*box_len;

float tank3_hei=0.01*box_len/4; 
float tank3_wid=0.1*box_len/4*2;

float tank4_hei=0.3*box_len/4; 
float tank4_wid=0.05*box_len/4; //tank variables end

//Mouse pointer position
float mouseposx,mouseposy,mouseposz;
//spider variables begin

float rad_x=0.05*box_len/4; 
float rad_y=0.07*box_len/4;

float leg1_x=-1*0.05*box_len/4; 
float leg1_y=0.0f; 
float leg1_hei=0.1*box_len/4; 
float leg1_ele=0.01*box_len/4;

float leg2_x=-0.15*box_len/4; 
float leg2_y=0.01*box_len/4; 
float leg2_hei=0.1*box_len/4; 
float leg2_ele=0.05*box_len/4;

float leg3_x=-0.15*box_len/4; 
float leg3_y=-0.03*box_len/4; 
float leg3_hei=0.1*box_len/4; 
float leg3_ele=-0.05*box_len/4;

float leg4_x=0.05*box_len/4; 
float leg4_y=0.0; 
float leg4_hei=-0.1*box_len/4; 
float leg4_ele=0.01*box_len/4;

float leg5_x=0.15*box_len/4; 
float leg5_y=0.01*box_len/4; 
float leg5_hei=-0.1*box_len/4; 
float leg5_ele=0.05*box_len/4;

float leg6_x=-0.05*box_len/4; 
float leg6_y=-0.03*box_len/4; 
float leg6_hei=0.1*box_len/4; 
float leg6_ele=-0.01*box_len/4;

float leg7_x=0.05*box_len/4; 
float leg7_y=-0.03*box_len/4; 
float leg7_hei=-0.1*box_len/4; 
float leg7_ele=-0.01*box_len/4;

float leg8_x=0.15*box_len/4; 
float leg8_y=-0.03*box_len/4; 
float leg8_hei=-0.1*box_len/4; 
float leg8_ele=-0.05*box_len/4;

float leg9_x=-0.05*box_len/4; 
float leg9_y=0.13*box_len/4; 
float leg9_hei=-0.05*box_len/4; 
float leg9_ele=-0.1*box_len/4;

float leg10_x=-0.15*box_len/4; 
float leg10_y=0.18*box_len/4; 
float leg10_hei=-0.1*box_len/4; 
float leg10_ele=-0.05*box_len/4;

float leg11_x=0.03*box_len/4; 
float leg11_y=0.05*box_len/4; 
float leg11_hei=-0.05*box_len/4; 
float leg11_ele=0.1*box_len/4;

float leg12_x=0.08*box_len/4; 
float leg12_y=0.15*box_len/4; 
float leg12_hei=-0.1*box_len/4; 
float leg12_ele=0.05*box_len/4;

float leg13_x=-0.02*box_len/4; 
float leg13_y=-0.06*box_len/4; 
float leg13_hei=0.05*box_len/4; 
float leg13_ele=-0.1*box_len/4;

float leg14_x=-0.07*box_len/4; 
float leg14_y=-0.15*box_len/4; 
float leg14_hei=0.1*box_len/4; 
float leg14_ele=-0.05*box_len/4;

float leg15_x=0.02*box_len/4; 
float leg15_y=-0.05*box_len/4; 
float leg15_hei=-0.05*box_len/4; 
float leg15_ele=-0.1*box_len/4;

float leg16_x=0.06*box_len/4; 
float leg16_y=-0.14*box_len/4; 
float leg16_hei=-0.1*box_len/4; 
float leg16_ele=-0.05*box_len/4;

int turn=0,difficulty_level=2;
char ch='n';

void initialiseagain()
{
	tri_x = 0.0f;
	tri_y = -0.875*box_len;
	theta = 0.0f;

	gb_x=0.9*box_len;
	gb_y=-0.95*box_len;
	rb_x=-0.9*box_len;
	rb_y=-0.95*box_len;

	tri_limx1=-0.9*box_len,tri_limx2=0.9*box_len;
	speed_min=0.01f,speed_max=0.05f;

	update_flag=1;
	start_flag=1;

	gb_limx1=-0.775*box_len;
	gb_limx2=0.8*box_len;
	rb_limx1=-0.8*box_len;
	rb_limx2=0.775*box_len;

	//laser variables
	laser_len=0.2*box_len;
	//tank variables 
	tank1_hei=0.1*box_len*0.4; 
	tank1_wid=0.1*box_len;

	tank2_hei=0.1*box_len*0.6; 
	tank2_wid=0.05*box_len;

	tank3_hei=0.01*box_len/4; 
	tank3_wid=0.1*box_len/4;
	tank4_hei=0.3*box_len/4; 
	tank4_wid=0.05*box_len/4; //tank variables end

	//spider variables begin
	rad_x=0.05*box_len/4; 
	rad_y=0.07*box_len/4;

	leg1_x=-1*0.05*box_len/4; 
	leg1_y=0.0f; 
	leg1_hei=0.1*box_len/4; 
	leg1_ele=0.01*box_len/4;

	leg2_x=-0.15*box_len/4; 
	leg2_y=0.01*box_len/4; 
	leg2_hei=0.1*box_len/4; 
	leg2_ele=0.05*box_len/4;

	leg3_x=-0.15*box_len/4; 
	leg3_y=-0.03*box_len/4; 
	leg3_hei=0.1*box_len/4; 
	leg3_ele=-0.05*box_len/4;

	leg4_x=0.05*box_len/4; 
	leg4_y=0.0; 
	leg4_hei=-0.1*box_len/4; 
	leg4_ele=0.01*box_len/4;

	leg5_x=0.15*box_len/4; 
	leg5_y=0.01*box_len/4; 
	leg5_hei=-0.1*box_len/4; 
	leg5_ele=0.05*box_len/4;

	leg6_x=-0.05*box_len/4; 
	leg6_y=-0.03*box_len/4; 
	leg6_hei=0.1*box_len/4; 
	leg6_ele=-0.01*box_len/4;

	leg7_x=0.05*box_len/4; 
	leg7_y=-0.03*box_len/4; 
	leg7_hei=-0.1*box_len/4; 
	leg7_ele=-0.01*box_len/4;

	leg8_x=0.15*box_len/4; 
	leg8_y=-0.03*box_len/4; 
	leg8_hei=-0.1*box_len/4; 
	leg8_ele=-0.05*box_len/4;

	leg9_x=-0.05*box_len/4; 
	leg9_y=0.13*box_len/4; 
	leg9_hei=-0.05*box_len/4; 
	leg9_ele=-0.1*box_len/4;

	leg10_x=-0.15*box_len/4; 
	leg10_y=0.18*box_len/4; 
	leg10_hei=-0.1*box_len/4; 
	leg10_ele=-0.05*box_len/4;

	leg11_x=0.03*box_len/4; 
	leg11_y=0.05*box_len/4; 
	leg11_hei=-0.05*box_len/4; 
	leg11_ele=0.1*box_len/4;

	leg12_x=0.08*box_len/4; 
	leg12_y=0.15*box_len/4; 
	leg12_hei=-0.1*box_len/4; 
	leg12_ele=0.05*box_len/4;

	leg13_x=-0.02*box_len/4; 
	leg13_y=-0.06*box_len/4; 
	leg13_hei=0.05*box_len/4; 
	leg13_ele=-0.1*box_len/4;

	leg14_x=-0.07*box_len/4; 
	leg14_y=-0.15*box_len/4; 
	leg14_hei=0.1*box_len/4; 
	leg14_ele=-0.05*box_len/4;

	leg15_x=0.02*box_len/4; 
	leg15_y=-0.05*box_len/4; 
	leg15_hei=-0.05*box_len/4; 
	leg15_ele=-0.1*box_len/4;

	leg16_x=0.06*box_len/4; 
	leg16_y=-0.14*box_len/4; 
	leg16_hei=-0.1*box_len/4; 
	leg16_ele=-0.05*box_len/4;
}
int main(int argc, char **argv) 
{
	printf("These are the default values of the world\n");
	printf("==========================================\n");
	printf("box_len=%f\ndifficulty_level=%d\n",box_len,difficulty_level);
	printf("==========================================\n");
	printf("Do you want to enter the values or continue(y/n)");
	ch=getchar();
	float box_lend;
	int difficulty_leveld;
	if(ch=='y')
	{
		scanf("%f",&box_lend);
		scanf("%d",&difficulty_leveld);
	}
	if(ch=='y')
	{
		if(box_lend>0)
			box_len=box_lend;
		if(difficulty_leveld>=1 && difficulty_leveld<=3)
			difficulty_level=difficulty_leveld;
	}
	printf("%f %d\n",box_len,difficulty_level);
	initialiseagain();
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
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(handleMouseDrag);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	if(update_flag==1)
	{
		glutTimerFunc(100,generateSpider,0);
		glutTimerFunc(1000,speedchange,0);
	}
	glutMainLoop();
	return 0;
}

//Get mouse pointer positions
void GetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	mouseposx=posX*100/2;
	mouseposy=(posY*100)/2;
	mouseposz=posZ*100;
}


//Draw Spider
void drawSpider()
{
	int i,l=spidy.size();
	for(i=0;i<l;i++)
	{
		glPushMatrix();
		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		DrawEllipse(rad_x,rad_y); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg1_x,leg1_y,leg1_hei,leg1_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg2_x,leg2_y,leg2_hei,leg2_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg6_x,leg6_y,leg6_hei,leg6_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg3_x,leg3_y,leg3_hei,leg3_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg4_x,leg4_y,leg4_hei,leg4_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg5_x,leg5_y,leg5_hei,leg5_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg7_x,leg7_y,leg7_hei,leg7_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z);
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg8_x,leg8_y,leg8_hei,leg8_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{
			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg9_x,leg9_y,leg9_hei,leg9_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg10_x,leg10_y,leg10_hei,leg10_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		}
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg11_x,leg11_y,leg11_hei,leg11_ele);

		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg12_x,leg12_y,leg12_hei,leg12_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg13_x,leg13_y,leg13_hei,leg13_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg14_x,leg14_y,leg14_hei,leg14_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg15_x,leg15_y,leg15_hei,leg15_ele); 
		glPopMatrix();

		glPushMatrix();

		glTranslatef(spidy[i].spider_x, spidy[i].spider_y, spidy[i].spider_z); 
		if(spidy[i].flg==0) 
		{ 
			glColor3f(1.0f, 0.0f, 0.0f); 
		} 
		else if(spidy[i].flg==1) 
		{ 
			glColor3f(0.0f, 1.0f, 0.0f); 
		} 
		else if(spidy[i].flg==2) 
		{

			glColor3f(0.0f, 0.0f, 0.0f); 
		} 
		drawleg1(leg16_x,leg16_y,leg16_hei,leg16_ele);
		glPopMatrix();
	}
}
void DrawEllipse(float radiusX, float radiusY) 
{ 
	int i; 
	glBegin(GL_TRIANGLE_FAN); 
	for(i=0;i<360;i++) 
	{ 
		glVertex2f(cos(DEG2RAD(i))*radiusX, sin(DEG2RAD(i))*radiusY); 
	} 
	glEnd(); 
}
void speedchange(int value)
{
	if(update_flag)
	{
		speed_min+=0.01f;
		speed_max+=0.01f;
	}
	if(difficulty_level==1)
		glutTimerFunc(8000,speedchange,0);
	else if(difficulty_level==2)
		glutTimerFunc(6000,speedchange,0);
	else
		glutTimerFunc(4000,speedchange,0);
}
void generateSpider(int value)
{
	if(update_flag)
	{	
		std::srand(std::time(0));
		spider spd;
		float x1 = static_cast<double>(std::rand()) / RAND_MAX * box_len * 2 ;
		float calcit=speed_min+static_cast<double>((std::rand()/RAND_MAX * (speed_max-speed_min)));
		x1=x1-box_len;
		spd.spider_x=x1;
		spd.spider_y=0.875*box_len;
		spd.spider_z=-5.0f;
		int flg=static_cast<double>(std::rand())/RAND_MAX*3;
		spd.flag=0;
		spd.flg=flg;
		spd.speed=calcit;
		spd.min_speed=speed_min;
		spd.max_speed=speed_max;
		spd.check=0;
		spidy.push_back(spd);
	}
	if(difficulty_level==1)
		glutTimerFunc(3000,generateSpider,0);
	else if(difficulty_level==2)
		glutTimerFunc(2000,generateSpider,0);
	else
		glutTimerFunc(1000,generateSpider,0);
	//printf("x1=%f y1=%f x2=%f y2=%f flag=%d\n",spd.x1,spd.y1,spd.x2,spd.y2,flg);
}
//Function to draw Cylinder
//Function to change the color of the triangle
void changeit(int value)
{
	tri_flag=1;
	//printf("%d\n",tri_flag);
}

//To exit out of the game
void exitit(int value)
{
	exit(0);
}


// Function to draw objects on the screen
void drawScene() 
{
	if(exit_flag)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawEndGame();
		if(once_flag)
		{
			once_flag=0;
			glutTimerFunc(1000,exitit,0);
		}
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();


		// Draw Box
		glTranslatef(0.0f, 0.0f, -5.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		drawBox(box_len,0);

		//Draw Tank
		glPushMatrix(); 
		glTranslatef(tri_x, tri_y, -5.0f); 
		glRotatef(theta, 0.0f, 0.0f, -5.0f);
		if(turn==0)
		{
			if(tri_flag==1)
				glColor3f(3.5f, 0.5f, 0.5f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		else
		{
			if(tri_flag==1)
				glColor3f(0.5f, 0.2f, 0.0f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		drawrect(tank1_wid,tank1_hei); 
		glPopMatrix();

		glPushMatrix(); 
		glTranslatef(tri_x, tri_y, -5.0f);
		glRotatef(theta, 0.0f, 0.0f, -5.0f); 
		if(turn==0)
		{
			if(tri_flag==1)
				glColor3f(3.5f, 0.5f, 0.5f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		else
		{
			if(tri_flag==1)
				glColor3f(0.5f, 0.2f, 0.0f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		drawrect1(tank2_wid,tank2_hei); 
		glPopMatrix();

		glPushMatrix(); 
		glTranslatef(tri_x, tri_y, -5.0f); 
		glRotatef(theta, 0.0f, 0.0f, -5.0f); 
		if(turn==0)
		{
			if(tri_flag==1)
				glColor3f(3.5f, 0.5f, 0.5f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		else
		{
			if(tri_flag==1)
				glColor3f(0.5f, 0.2f, 0.0f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		drawrect2(tank3_wid,tank3_hei); 
		glPopMatrix();

		glPushMatrix(); 
		glTranslatef(tri_x, tri_y, -5.0f);
		glRotatef(theta, 0.0f, 0.0f, -5.0f); 
		if(turn==0)
		{
			if(tri_flag==1)
				glColor3f(3.5f, 0.5f, 0.5f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		else
		{
			if(tri_flag==1)
				glColor3f(0.5f, 0.2f, 0.0f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		drawrect3(tank3_wid,tank3_hei); 
		glPopMatrix();

		glPushMatrix(); 
		glTranslatef(tri_x, tri_y, -5.0f);
		glRotatef(theta, 0.0f, 0.0f, -5.0f); 
		if(turn==0)
		{
			if(tri_flag==1)
				glColor3f(3.5f, 0.5f, 0.5f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		else
		{
			if(tri_flag==1)
				glColor3f(0.5f, 0.2f, 0.0f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		drawrect4(tank4_wid,tank4_hei);
		glPopMatrix();

		glPushMatrix(); 
		glTranslatef(tri_x, tri_y, -5.0f); 
		glRotatef(theta, 0.0f, 0.0f, -5.0f); 
		if(turn==0)
		{
			if(tri_flag==1)
				glColor3f(3.5f, 0.5f, 0.5f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		else
		{
			if(tri_flag==1)
				glColor3f(0.5f, 0.2f, 0.0f); 
			else
				glColor3f(0.37f,0.62f,0.62f);
		}
		drawrect5(tank4_wid,tank4_hei); 
		glPopMatrix();	

		//Draw Play area
		float play_x1,play_x2,play_y1,play_y2;
		play_x1=-box_len;
		play_x2=box_len;
		play_y1=-0.8*box_len;
		play_y2=-box_len;
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(play_x1,play_y1,-5.0f);
		glVertex3f(play_x2,play_y1,-5.0f);
		glVertex3f(play_x2,play_y2,-5.0f);
		glVertex3f(play_x1,play_y2,-5.0f);
		glEnd();
		glPopMatrix();

		//Draw green cylinder
		glPushMatrix();
		glTranslatef(gb_x,gb_y,-5.0f);
		glRotatef(-90.0f,1.0f,0.0f,0.0f);
		if(green_flag==0)
			glColor3f(0.0f,1.0f,0.0f);
		else
			glColor3f(0.0f,0.7f,0.0f);
		drawGluCylinder(box_len/10.0,box_len/10.0,35,36);
		glPopMatrix();

		//Draw Red cylinder
		glPushMatrix();
		glTranslatef(rb_x,rb_y,-5.0f);
		glRotatef(-90.0f,1.0f,0.0f,0.0f);
		if(red_flag==0)
			glColor3f(1.0f,0.0f,0.0f);
		else
			glColor3f(0.7f,0.0f,0.0f);
		drawGluCylinder(box_len/10.0,box_len/10.0,35,36);
		glPopMatrix();

		// Draw Laser
		drawLaser();

		// Draw Spider
		drawSpider();

		//Display Score
		Score();

		glPopMatrix();
		glutSwapBuffers();
		glutPostRedisplay();
	}
}
void Score() 
{ 
	glRasterPos2f(box_len/2.0,box_len/4.0f); 
	char string[10]="SCORE : "; 
	int i; 
	for(i=0;i<(int)(strlen(string));i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]); 
	char str[80]; 
	sprintf(str,"%d",score); 
	for(i=0;i<(int)(strlen(str));i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);

}
void drawEndGame() 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0,4, 0.0,4);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
	glRasterPos2f(box_len/2.0,0.625*box_len);
	std::string s = "Game Over";
	void * font = GLUT_BITMAP_9_BY_15;

	for (std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		//this does nothing, color is fixed for Bitmaps when calling glRasterPos
		//glColor3f(1.0, 0.0, 1.0);
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
	glRasterPos2f(box_len/2.0,0.65*box_len);
	ostringstream convert;
	convert << score;
	string res=convert.str();
	std::string s1 = "Your Score is:"+res;
	//void * font = GLUT_BITMAP_9_BY_15;

	for (std::string::iterator i = s1.begin(); i != s1.end(); ++i)
	{
		char c = *i;
		//this does nothing, color is fixed for Bitmaps when calling glRasterPos
		//glColor3f(1.0, 0.0, 1.0);
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void drawrect(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS); 
	glVertex2f(-len1 / 2, -len2); 
	glVertex2f(len1 / 2, -len2); 
	glVertex2f(len1/2, len2); 
	glVertex2f(-len1 / 2, len2); 
	glEnd(); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 

void drawrect1(float len1,float len2) 
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glBegin(GL_QUADS); 
	glVertex2f(-len1 / 2, -len2+tank1_hei/2); 
	glVertex2f(len1 / 2, -len2+tank1_hei/2); 
	glVertex2f(len1/2, len2+tank1_hei/2); 
	glVertex2f(-len1 / 2, len2+tank1_hei/2); 
	glEnd(); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 

void drawrect2(float len1,float len2) 
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glBegin(GL_QUADS); 
	glVertex2f(-len1 / 2-tank1_wid/2, -len2); 
	glVertex2f(len1 / 2-tank1_wid/2, -len2); 
	glVertex2f(len1/2-tank1_wid/2, len2); 
	glVertex2f(-len1 / 2-tank1_wid/2, len2); 
	glEnd(); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 
void drawrect3(float len1,float len2) 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glBegin(GL_QUADS); 
	glVertex2f(-len1 / 2+tank1_wid/2, -len2); 
	glVertex2f(len1 / 2+tank1_wid/2, -len2); 
	glVertex2f(len1/2+tank1_wid/2, len2); 
	glVertex2f(-len1 / 2+tank1_wid/2, len2); 
	glEnd(); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 
void drawrect4(float len1,float len2) 
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glBegin(GL_QUADS); 
	glVertex2f(-len1 / 2-tank1_wid/2-tank3_wid/2, -len2+tank1_hei/2); 
	glVertex2f(len1 / 2-tank1_wid/2-tank3_wid/2, -len2+tank1_hei/2); 
	glVertex2f(len1/2-tank1_wid/2-tank3_wid/2, len2); 
	glVertex2f(-len1 / 2-tank1_wid/2-tank3_wid/2, len2); 
	glEnd(); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 
void drawrect5(float len1,float len2) 
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glBegin(GL_QUADS); 
	glVertex2f(-len1 / 2+tank1_wid/2+tank3_wid/2, -len2+tank1_hei/2);
	glVertex2f(len1 / 2+tank1_wid/2+tank3_wid/2, -len2+tank1_hei/2); 
	glVertex2f(len1/2+tank1_wid/2+tank3_wid/2, len2); 
	glVertex2f(-len1 / 2+tank1_wid/2+tank3_wid/2, len2); 
	glEnd(); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
}

//Draw Legs of Spiders
void drawleg1(float x1,float y1,float len,float ele) 
{ 
	//glColor3f(1.0, 0.0, 0.0); 
	glBegin(GL_LINES); 
	glVertex3f(x1, y1,0.0f);
	glVertex3f(x1-len,y1+ele,0.0f); 
	glEnd();

} 
void drawleg2(float x1,float y1)
{ //glColor3f(1.0, 0.0, 0.0); 
	glBegin(GL_LINES); 
	glVertex3f(x1, y1,0.0f); 
	glVertex3f(x1-0.1,y1+0.01,0.0f); 
	glEnd();

}
int test_flag=1;
//Draw Baskets
GLUquadricObj* myReusableQuadric = 0; 
void drawGluCylinder(float height,float radius,float slices,float stacks) 
{ 
	if ( ! myReusableQuadric ) 
	{ 
		myReusableQuadric = gluNewQuadric(); 
		gluQuadricNormals( myReusableQuadric, GL_TRUE ); 
	} 
	gluCylinder( myReusableQuadric, radius, radius, height, slices, stacks ); 
}
float shift_it=0.25;
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
	// Update value of laser
	if(update_flag && exit_flag==0)
	{
		int i,j,l2,l1=lser.size();
		float val,calc,xit1,yit1;
		laser strct;
		for(i=0;i<l1;i++)
		{
			strct=lser[i];
			val=90-strct.theta;
			strct.x1+=shift_it*cos(DEG2RAD(val));
			strct.y1+=shift_it*sin(DEG2RAD(val));
			strct.x2=laser_len*cos(DEG2RAD(val))+strct.x1;
			strct.y2=laser_len*sin(DEG2RAD(val))+strct.y1;
			if(strct.y2>box_len)
			{
				lser.erase(lser.begin()+i);
			}
			else if(fabs(strct.x2)>=box_len)
			{
				xit1=strct.x2;
				yit1=strct.y2;
				lser.erase(lser.begin()+i);
				calc=-strct.theta;
				//calc=-calc;
				generateLaser(xit1,yit1,calc);
			}
			else
				lser[i]=strct;
		}
		// Update Spider's position
		l2=spidy.size();
		spider strct1;
		for(i=0;i<l2;i++)
		{
			strct1=spidy[i];
			if(strct1.spider_y>-0.875*box_len)
			{
				strct1.spider_y-=strct1.speed;
				spidy[i]=strct1;
			}
			else
			{
				if(strct1.flag==0)
					score-=5;
				strct1.flag=1;
				spidy[i]=strct1;
			}
		}
		int flg=1;
		for(i=0;i<l1;i++)
		{
			strct=lser[i];
			flg=1;
			for(j=0;j<l2;j++)
			{
				strct1=spidy[j];
				if(strct.x2>strct1.spider_x-rad_x-2*leg1_hei && strct.x2<strct1.spider_x+rad_x+2*leg1_hei && strct.y2<=strct1.spider_y+rad_y+2*leg1_hei && strct.y2>=strct1.spider_y-rad_y && strct1.y2>-0.75*box_len && strct1.flag==0)
				{
					if(strct1.flg==2)
						score++;
					else
						score--;
					lser.erase(lser.begin()+i);
					spidy.erase(spidy.begin()+j);
					flg=0;
					continue;
				}
			}
			if(flg==0)
				continue;
		}
		float rlx1,rlx2,ruy;
		float glx1,glx2,guy;
		float storeit1,storeit2;
		float trilimx1,trilimx2,trilimy;
		rlx1=rb_x-box_len/10.0;
		rlx2=rb_x+box_len/10.0;
		ruy=rb_y+box_len/10.0;
		glx1=gb_x-box_len/10.0;
		glx2=gb_x+box_len/10.0;
		guy=gb_y+box_len/10.0;
		for(i=0;i<l2;i++)
		{
			trilimx1=tri_x-0.5;
			trilimx2=tri_x+0.5;
			trilimy=-0.8*box_len;
			decide=0;
			strct1=spidy[i];
			storeit1=strct1.y1-ruy;
			storeit2=strct1.y1-guy;
			if((tri_x+box_len/10.0>strct1.spider_x) && (tri_x-box_len/10.0<strct1.spider_x) && (tri_y>strct1.spider_y-rad_y-leg1_hei) && (strct1.flag==0))
				exit_flag=1;
			if(strct1.flg==1)
			{
				if(strct1.spider_x>glx1 && strct1.spider_x<glx2 && strct1.spider_y-rad_y-2*leg1_hei<-0.9*box_len && strct1.flag==0)
				{
					score++;
					spidy.erase(spidy.begin()+i);
					continue;
				}
				else if(strct1.spider_x>rlx1 && strct1.spider_x<rlx2 && strct1.spider_y-rad_y-2*leg1_hei<-0.9*box_len && strct1.flag==0)
				{
					score--;
					spidy.erase(spidy.begin()+i);
					continue;
				}
			}
			else if(strct1.flg==0)
			{
				if(strct1.spider_x>rlx1 && strct1.spider_x<rlx2 && strct1.spider_y-rad_y-2*leg1_hei<-0.9*box_len && strct1.flag==0)
				{
					score++;
					spidy.erase(spidy.begin()+i);
					continue;
				}
				else if(strct1.spider_x>glx1 && strct1.spider_x<glx2 && strct1.spider_y-rad_y-2*leg1_hei<-0.9*box_len && strct1.flag==0)
				{
					score--;
					spidy.erase(spidy.begin()+i);
					continue;
				}
			}
			else
			{
				if(((strct1.spider_x>rlx1 && strct1.spider_x<rlx2 && strct1.spider_y-rad_y-2*leg1_hei<-0.9*box_len) || (strct1.spider_x>glx1 && strct1.spider_x<glx2 && strct1.spider_y-rad_y-2*leg1_hei<-0.9*box_len)) && (strct1.flag==0))
				{
					score--;
					spidy.erase(spidy.begin()+i);
					continue;
				}
			}
			if(strct1.flag==1 && strct1.check==0)
				decide=1;
			if(strct1.flag==1)
			{
				//if(tri_x-0.5<strct1.x1 && tri_x+0.5<strct1.x1)
				if(gb_x<strct1.spider_x)
				{
					if(gb_limx2+box_len/5.5>strct1.spider_x)
					{
						gb_limx2=strct1.spider_x-box_len/5.5;
					}
				}
				else if(gb_x>strct1.spider_x)
				{
					if(gb_limx1-box_len/5.5<strct1.spider_x)
					{
						gb_limx1=strct1.spider_x+box_len/5.5;
					}
				}
				if(rb_x<strct1.spider_x)
				{
					if(rb_limx2+box_len/5.5>strct1.spider_x)
						rb_limx2=strct1.spider_x-box_len/5.5;
				}
				else if(rb_x-box_len/5.5>strct1.spider_x)
				{
					if(rb_limx1<strct1.spider_x)
						rb_limx1=strct1.spider_x+box_len/5.5;
				}
				if(tri_x<strct1.spider_x-box_len/6)
				{
					if(tri_limx2>strct1.spider_x-box_len/6)
						tri_limx2=strct1.spider_x-box_len/6;
				}
				//else if(tri_x-0.5>strct1.x2 && tri_x+0.5>strct1.x2)
				else if(tri_x>strct1.spider_x)
				{
					if(tri_limx1<strct1.spider_x+box_len/6)
					{
						tri_limx1=strct1.spider_x+box_len/6;
					}
				}
				spidy[i].check=1;
			}
		}
	}
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
		glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-len / 2, -len / 2);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(len / 2, -len / 2);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(len / 2, len / 2);
	if(flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(flag==2)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-len / 2, len / 2); glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void generateLaser(float x1,float y1,float theta1)
{
	laser str;
	str.x1=x1;
	str.y1=y1;
	float val=90-theta1;
	str.x2=laser_len*cos(DEG2RAD(val))+x1;
	str.y2=laser_len*sin(DEG2RAD(val))+y1;
	str.theta=theta1;
	//printf("%f %f %f %f %lf %lf\n",str.x1,str.y1,str.x2,str.y2,val,cos(DEG2RAD(val)));
	lser.push_back(str);
}
void drawLaser()
{
	int i,l=lser.size();
	laser strct;
	for(i=0;i<l;i++)
	{
		strct=lser[i];
		//glLineWidth(1.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(strct.x1,strct.y1,-5.0f);
		glVertex3f(strct.x2,strct.y2,-5.0f);
		glEnd();
		//glPushMatrix();
	}
}

void drawBall(float rad) 
{
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawTriangle() {

	glBegin(GL_TRIANGLES);
	if(tri_flag==1)
		glColor3f(0.0f, 0.0f, 1.0f);
	else
		glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	if(tri_flag==1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	if(tri_flag==1)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
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

void handleKeypress1(unsigned char key, int x, int y) 
{
	if (key == 27) {
		exit(0);     // escape key is pressed
	}
}

void handleKeypress2(unsigned char key, int x, int y)
{
	if(update_flag || start_flag)
	{
		if(key=='r' || key=='G')
		{
			turn=0;
			green_flag=0;
			red_flag=1;
			default_flag=0;
			space_flag=0;
			glutSpecialFunc(basketmove_red);
		}
		else if(key=='g' || key=='G')
		{
			turn=0;
			green_flag=1;
			red_flag=0;
			default_flag=0;
			space_flag=0;
			glutSpecialFunc(basketmove_green);
		}
		else if(key==' ' && space_flag==1)
		{
			default_flag=0;
			if(tri_flag)
			{
				system("aplay beep7.wav&");
				tri_flag=0;
				generateLaser(tri_x,tri_y,theta);
				glutTimerFunc(1000,changeit,0);
			}
		}
		else if(key=='b' || key=='B' || default_flag==1)
		{
			turn=1;
			default_flag=0;
			space_flag=1;
			glutSpecialFunc(lasermove);
		}
	}
	if(key=='p' || key=='P')
	{
		start_flag=0;
		update_flag=1-update_flag;
	}
	else if(key==27)
	{
		default_flag=0;
		exit_flag=1;
		//exit(0);
	}
}
void basketmove_green(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if(gb_x >=gb_limx1)
			gb_x -= 0.1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if(gb_x<=gb_limx2)
			gb_x += 0.1;
	}
	else if(key==GLUT_KEY_END)
		gb_x=gb_limx2+box_len/10.0;
	else if(key==GLUT_KEY_HOME)
		gb_x=gb_limx1-box_len/10.0;
	/*else if (key == GLUT_KEY_UP)
	  gb_y += 0.1;
	  else if (key == GLUT_KEY_DOWN)
	  gb_y -= 0.1;*/
}
void basketmove_red(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if(rb_x >=rb_limx1)
			rb_x -= 0.1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if(rb_x <= rb_limx2)
			rb_x += 0.1;
	}
	else if(key==GLUT_KEY_END)
		rb_x=rb_limx2+box_len/10.0;
	else if(key==GLUT_KEY_HOME)
		rb_x=rb_limx1-box_len/10.0;
	/*else if (key == GLUT_KEY_UP)
	  {
	  rb_y += 0.1;
	  }
	  else if (key == GLUT_KEY_DOWN)
	  {
	  rb_y -= 0.1;
	  }*/
}
void lasermove(int key, int x, int y)
{
	if(update_flag || start_flag)
	{
		if (key == GLUT_KEY_LEFT)
		{
			if(tri_x>=tri_limx1)
				tri_x -= 0.1;
		}
		else if (key == GLUT_KEY_RIGHT)
		{
			if(tri_x<=tri_limx2)
				tri_x += 0.1;
		}
		else if (key == GLUT_KEY_UP)
			theta+=15;
		else if (key == GLUT_KEY_DOWN)
			theta-=15;
		else if(key==GLUT_KEY_END)
			tri_x=tri_limx2;
		else if(key==GLUT_KEY_HOME)
			tri_x=tri_limx1;
		else
		{
			glutKeyboardFunc(handleKeypress1);
			glutKeyboardFunc(handleKeypress2);	
		}
	}
}
void handleMouseDrag(int x,int y) 
{ 
	GetOGLPos(x,y);
	if(selectit=='b' && mouseposx<tri_limx2 && mouseposx>tri_limx1)
	{
		if(mouseposx*box_len/2.0<tri_limx2 && mouseposx*box_len/2.0>tri_limx1)
			tri_x=mouseposx*box_len/2.0;
	}
	else if(selectit=='r' && mouseposx<rb_limx2 && mouseposx>rb_limx1) 
	{
		if(mouseposx*box_len/2.0<rb_limx2+box_len/10.0 && mouseposx*box_len/2.0>rb_limx1-box_len/10.0)
			rb_x=mouseposx*box_len/2.0;
	}
	else if(selectit=='g' && mouseposx<gb_limx2 && mouseposx>gb_limx1)
	{
		if(mouseposx*box_len/2.0<gb_limx2+box_len/10.0 && mouseposx*box_len/2.0>gb_limx1-box_len/10.0)
			gb_x=mouseposx*box_len/2.0; 
	}
	else if(selectit=='c') 
	{ 
		float side1=2*mouseposx-tri_x; 
		float side2=2*mouseposy-tri_y;
		side1*=2;
		side2*=2;
		theta=atan(float(side1)/side2)*180/PI; 
	} 
}

void handleMouseclick(int button, int state, int x, int y) 
{
	if ((update_flag || start_flag ) && (state==GLUT_DOWN && button==GLUT_LEFT_BUTTON))
	{
		GetOGLPos(x, y);
		float calcit1,calcit2,calcit3;
		calcit1=tri_x-box_len/10.0;
		calcit2=tri_x+box_len/10.0;
		calcit3=-0.375*box_len;
		if(mouseposx>=calcit1 && mouseposx<=calcit2 && mouseposy<=calcit3)
		{
			selectit='b';
			turn=1;
			red_flag=0;
			green_flag=0;
		}
		else
		{
			float rlx1,rlx2,ruy,glx1,glx2,guy;
			rlx1=rb_x-box_len/10.0;
			rlx2=rb_x+box_len/10.0;
			ruy=-0.35*box_len;
			glx1=gb_x-box_len/10.0;
			glx2=gb_x+box_len/10.0;
			guy=-0.35*box_len;
			rlx1/=2;
			rlx2/=2;
			glx1/=2;
			glx2/=2;
			if(mouseposx>=rlx1 && mouseposx<=rlx2 && mouseposy<=ruy)
			{
				selectit='r';
				turn=0;
				red_flag=1;
				green_flag=0;
			}
			else if(mouseposx>=glx1 && mouseposx<=glx2 && mouseposy<=guy)
			{
				selectit='g';
				turn=0;
				green_flag=1;
				red_flag=0;
			}
		}
		//printf("%c\n",selectit);
	}
	else if ((update_flag || start_flag ) && (state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON))
	{
		selectit='c';
	}

}




