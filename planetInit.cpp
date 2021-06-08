#include "planetInit.h"




Planet::Planet (float _radius, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni) {	radius = _radius;
		distance = _distance;
		orbit = _orbit;
		orbitSpeed = _orbitSpeed;
		axisTilt = _axisTilt;
		axisAni = _axisAni;
}




//Sun, Planets and Stars

Planet sun(5.0, 0, 0, 0, 0, 0);				//Sun
Planet mer(1.0, 7, 0, 4.74, 02.11, 0);		//Mercury
Planet ven(1.5, 11, 0, 3.50, 177.0, 0);		//Venus
Planet ear(2.0, 16, 0, 2.98, 23.44, 0);		//Earth
Planet mar(1.2, 21, 0, 2.41, 25.00, 0);		//Mars
Planet jup(3.5, 28, 0, 1.31, 03.13, 0);		//Jupiter
Planet sat(3.0, 37, 0, 0.97, 26.70, 0);		//Saturn
Planet ura(2.5, 45.5, 0, 0.68, 97.77, 0);	//Uranus
Planet nep(2.3, 53.6, 0, 0.54, 28.32, 0);	//Neptune
Planet plu(0.3, 59, 0, 0.47, 119.6, 0);		//Pluto

void createPlanets () {
	GLUquadric *quadric;
	quadric = gluNewQuadric();
	//Sun
	glPushMatrix();
	glRotatef(sun.orbit, 0.0, 1.0, 0.0);
	glTranslatef(sun.distance, 0.0, 0.0);
	
	glRasterPos3f(-1.2, 7.0, 0.0);
	glColor3ub(255, 255, 255);
		// writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sun");
	
	glPushMatrix();
	glRotatef(sun.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(sun.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluSphere(quadric, sun.radius, 20.0, 20.0);
	glPopMatrix();
	glPopMatrix();

	//Mercury
	addPlanet(mer, 255, 0, 0);
	addPlanet(ven, 255, 0, 0);
	addPlanet(ear, 255, 0, 0);
	addPlanet(mar, 255, 0, 0);
	addPlanet(jup, 255, 0, 0);
	addPlanet(sat, 255, 0, 0);
	addPlanet(ura, 255, 0, 0);
	addPlanet(nep, 255, 0, 0);
	addPlanet(plu, 255, 0, 0);

}

void addPlanet (Planet p, int r = 255, int g = 255, int b = 255) {
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	glColor3ub(r,g,b);
	glPushMatrix();
	glRotatef(p.orbit, 0.0, 1.0, 0.0);
	glTranslatef(p.distance, 0.0, 0.0);
	gluSphere(quadric, p.radius, 20.0, 20.0);
	glPopMatrix();
}