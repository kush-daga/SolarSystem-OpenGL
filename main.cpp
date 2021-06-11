#include <iostream>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "planetInit.h"

using namespace std;

int isAnimate = 0;
int bigOrbitActive = 1;
int changeCamera = 0;
int labelsActive = 0;
int logoScene = 1;



void setup(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (changeCamera == 0)gluLookAt(0.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 1)gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 2)gluLookAt(0.0, 50.0, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (bigOrbitActive == 1) orbitalTrails();

	glEnable(GL_COLOR_MATERIAL);

	createPlanets();

	glutSwapBuffers();
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



void keyInput(unsigned char key, int x, int y){
	switch (key){
	case 27: exit(0); break;
	case ' ': if (isAnimate) isAnimate = 0; else{ isAnimate = 1; animate(1); } break;
	
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
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();
	glutMainLoop();
}