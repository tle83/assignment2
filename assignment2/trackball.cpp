#include <stdafx.h>
#include <iostream>
#include <fstream>
using namespace std;

#include <stdlib.h>
#include <math.h>

#include <sys/types.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "objLoader.h"


#define KEY_LEFT 100
#define KEY_UP 101
#define KEY_RIGHT 102
#define KEY_DOWN 103

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

int winWidth = 1024;
int winHeight = 1024;
bool firstTime = true;

//the 3D object
WavefrontObj *obj_data;

// Trackball parameters initialization 
float angle = 0.0, axis[3], trans[3];

bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;

float lastPos[3] = { 0.0, 0.0, 0.0 };
int curx, cury;
int startX, startY;


// Translation & Rotation
float x_trans = 0.0f; // translate object in x direction
float y_trans = 0.0f; // translate object in y direction
float zoom = 1.0f; // zoom for scaling



void Init(int w, int h)
{
	glViewport(0, 0, w, h);
	glShadeModel(GL_SMOOTH);								// Set Smooth Shading 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			    	// Background Color 
	glClearDepth(1.0f);										// Depth buffer setup 
	glEnable(GL_DEPTH_TEST);								// Enables Depth Testing 
	glDepthFunc(GL_LEQUAL);									// The Type Of Depth Test To Do 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// Use perspective correct interpolation if available

	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix
	double aspect = (double)h / w;
	glFrustum(-5, 5, -5 * aspect, 5 * aspect, 10, 500);          // Define perspective projection frustum
																 //gluPerspective(30, w/h, 10, 74);
	glTranslated(0.0, 0.0, -24);                          // Viewing transformation

	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix

	if (firstTime)
	{
		glEnable(GL_LIGHTING);
		float frontColor[] = { 0.2f, 0.7f, 0.7f, 1.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, frontColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, frontColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, frontColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 100);

		float lightDirection[] = { 2.0f, 0.0f, 1.0f, 0 };
		float ambientIntensity[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		float lightIntensity[] = { 0.9f, 0.9f, 0.9f, 1.0f };
		float lightSpec[] = { 1.0f, 1.0f, 1.0f, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
		glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
		glEnable(GL_LIGHT0);
		firstTime = false;
	}
}


void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer

															// Insert your own code here (Hint:Translation Rotation & Scaling)
	//Translation

	//Rotation
	if (trackballMove) {
		glRotatef(angle, axis[0], axis[1], axis[2]);
	}
	//Scaling

	


	if (obj_data != NULL)
		obj_data->Draw();
	else
		glutSolidTeapot(1.0);	//draw a teapot when no argument is provided

	glFlush();
	glutSwapBuffers();

}

void trackmapping(int x, int y, int width, int height, float v[3]) {
	float d, a;
	v[0] = (2.0 * x - width) / width;
	v[1] = (height - 2.0F * y) / height;
	d = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[2] = cos((M_PI / 2.0) * ((d < 1.0) ? d : 1.0));
	a = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;
}


//
// GLUT keypress function
// 


void onKeyPress(unsigned char key, int x, int y)
{

	if (key == 'w')
	{
		obj_data->mode = GL_LINE_LOOP;
	}
	else if (key == 'p')
	{
		obj_data->mode = GL_POINTS;
	}
	else if (key == 's')
	{
		glShadeModel(GL_SMOOTH);								// Set Smooth Shading 
		obj_data->mode = GL_POLYGON;
	}
	else if (key == 'f')
	{
		glShadeModel(GL_FLAT);								// Set Smooth Shading 
		obj_data->mode = GL_POLYGON;
	}
	else if (key == 'q')
	{
		delete obj_data;
		exit(0);
	}

	// Insert your own code here (Hint: Use keyboard to control translations)

	if (key == 'q') {
		
	}
	else if (key == 'a') {

	}
	else if (key == 's') {

	}
	else if (key == 'd') {

	}

	glutPostRedisplay();
}


/*void Specialkey(int key, int x, int y)
{
(Hint: Use this function if you would like to use up/down/left/right arrow (#define as KEY_UP/KEY_DOWN/KEY_LEFT/KEY_RIGHT) for controlling translation)

glutPostRedisplay();
}*/




void MouseWheel(int wheel, int direction, int x, int y)
{
	// Insert your own code here (Hint: set zoom in/out for scrolling mouse wheel)
	
	if (direction > 0) {
		// Zoom in
		
	}
	else{
		// Zoom out

	}
	glutPostRedisplay();

}



void mouseMotion(int x, int y)
{
	// Insert your own code here (Hint: track the motion of mouse point)
	float curPos[3], dx, dy, dz;
	if (trackingMouse) {
		//calculate the change in poition
		dx = curPos[0] - lastPos[0];
		dy = curPos[1] - lastPos[1];
		dz = curPos[2] - lastPos[2];
	
		if (dx || dy || dz) {
			//calculate theta
			angle = 90.0 * sqrt(dx*dx + dy*dy + dz*dz);
			//calculate the cross product
			axis[0] = lastPos[1] * curPos[2] - lastPos[2] * curPos[1];
			axis[1] = lastPos[2] * curPos[0] - lastPos[0] * curPos[2];
			axis[1] = lastPos[0] * curPos[1] - lastPos[1] * curPos[0];
			//update the positions
			lastPos[0] = curPos[0];
			lastPos[1] = curPos[1];
			lastPos[2] = curPos[2];
		}
	}

	glutPostRedisplay();
}




void mouseButton(int button, int state, int x, int y)
{
	// Insert your own code here (Hint:click down the left button to allow rotation)
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		trackingMouse = true;
		obj_data->mode = GL_LINE_LOOP;
	}
	else {
		trackingMouse = false;
	}
}





int main(int argc, char *argv[])
{



	// glut initialization functions:
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ImageViewer");

	Init(winWidth, winHeight);

	// display, onMouseButton, mouse_motion, onKeyPress, and resize are functions defined above
	glutDisplayFunc(Draw);
	glutKeyboardFunc(onKeyPress);
	//glutSpecialFunc(Specialkey);  //use this function if you would like to use arrow buttons on your keyboard to control translation
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(MouseWheel);
	glutReshapeFunc(Init);

	if (argc >= 2)
		obj_data = new WavefrontObj(argv[1]);
	else
		obj_data = NULL;

	// start glutMainLoop -- infinite loop
	glutMainLoop();

	return 0;
}
