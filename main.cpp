#include <iostream>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "planetInit.h"

using namespace std;

int isAnimate = 0;
int bigOrbitActive = 1;
int smallOrbitActive = 1;
int moonsActive = 1;
int changeCamera = 0;
int frameCount = 0;
int labelsActive = 0;
int zoom = 50;
int logoScene = 1;

float lightPos[] = { 0.0, 0.0, -75.0, 1.0 }; // Spotlight position.
static float spotAngle = 40; // Spotlight cone half-angle.
float spotDirection[] = { 1.0, 0.0, 0.0 }; // Spotlight direction.
static float spotExponent = 1.0; // Spotlight exponent = attenuation factor.


void setup(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);


	//LIGHTING SETUP
	glEnable(GL_LIGHTING);
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float globAmb[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
}

void orbitalTrails(void){
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutWireTorus(0.001, mer.distance, 100.0, 100.0);
	glutWireTorus(0.001, ven.distance, 100.0, 100.0);
	glutWireTorus(0.001, ear.distance, 100.0, 100.0);
	glutWireTorus(0.001, mar.distance, 100.0, 100.0);
	glutWireTorus(0.001, jup.distance, 100.0, 100.0);
	glutWireTorus(0.001, sat.distance, 100.0, 100.0);
	glutWireTorus(0.001, ura.distance, 100.0, 100.0);
	glutWireTorus(0.001, nep.distance, 100.0, 100.0);
	glutWireTorus(0.001, plu.distance, 100.0, 100.0);
	glPopMatrix();
}



void drawScene(void){
	frameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (changeCamera == 0)gluLookAt(0.0, zoom, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 1)gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 2)gluLookAt(0.0, zoom, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (bigOrbitActive == 1) orbitalTrails();

	glEnable(GL_COLOR_MATERIAL);

	createPlanets();

	glutSwapBuffers();
}

void drawScenesInOrder(void){
	
		drawScene();

}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void animate(int n){
	if (isAnimate){
		mer.orbit += mer.orbitSpeed;
		ven.orbit += ven.orbitSpeed;
		ear.orbit += ear.orbitSpeed;
		mar.orbit += mar.orbitSpeed;
		jup.orbit += jup.orbitSpeed;
		sat.orbit += sat.orbitSpeed;
		ura.orbit += ura.orbitSpeed;
		nep.orbit += nep.orbitSpeed;
		plu.orbit += plu.orbitSpeed;

		glutPostRedisplay();
		glutTimerFunc(30, animate, 1);
	}
}

void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if (logoScene) logoScene = 0;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);
	glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	if (direction > 0 && zoom < 100) zoom++;
	if (direction < 0 && zoom > -75) zoom--;
	glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y){
	switch (key){
	case 27: exit(0); break;
	case ' ': if (isAnimate) isAnimate = 0; else{ isAnimate = 1; animate(1); } break;
	case 'o': if (smallOrbitActive) smallOrbitActive = 0; else smallOrbitActive = 1; glutPostRedisplay(); break;
	case 'O': if (bigOrbitActive) bigOrbitActive = 0; else bigOrbitActive = 1; glutPostRedisplay(); break;
	case 'm': if (moonsActive) moonsActive = 0; else moonsActive = 1; glutPostRedisplay(); break;
	case 'M': if (moonsActive) moonsActive = 0; else moonsActive = 1; glutPostRedisplay(); break;
	case 'l': if (labelsActive) labelsActive = 0; else labelsActive = 1; glutPostRedisplay(); break;
	case 'L': if (labelsActive) labelsActive = 0; else labelsActive = 1; glutPostRedisplay(); break;
	case '1': changeCamera = 0; glutPostRedisplay(); break;
	case '2': changeCamera = 1; glutPostRedisplay(); break;
	case '3': changeCamera = 2; glutPostRedisplay(); break;
	}
}

void intructions(void){
	cout << "SPACE to play/pause the simulation." << endl;
	cout << "ESC to exit the simulation." << endl;
	cout << "O to show/hide Big Orbital Trails." << endl;
	cout << "o to show/hide Small Orbital Trails." << endl;
	cout << "M/m to show/hide Moons." << endl;
	cout << "L/l to show/hide labels" << endl;
	cout << "1, 2 and 3 to change camera angles." << endl;
	cout << "Scroll to change camera movement" << endl;
}

int main(int argc, char **argv){
	intructions();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Solar System");
	glutDisplayFunc(drawScenesInOrder);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseControl);
	glutKeyboardFunc(keyInput);
	glutMouseWheelFunc(mouseWheel);

	setup();
	glutMainLoop();
}