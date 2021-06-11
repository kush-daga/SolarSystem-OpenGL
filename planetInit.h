#ifndef PLANETINIT_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PLANETINIT_H

#include <iostream>
#include <GL/freeglut.h>
#include <GL/glext.h>

void createPlanets();

class Planet
{
  public:
  float radius, distance, orbit, orbitSpeed, axisTilt, axisAni;
  Planet(float _radius, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni);
};

void addPlanet(Planet p, int r, int g, int b);

extern Planet sun, mer, ven, ear, mar, jup, sat, ura, nep, plu;

#endif