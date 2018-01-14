/*
Joe Bonino - CS495 Video Game Programming
This program implements SDL/openGL to create a rubiks
cube. Arrow keys and A/Z are required to rotate cube
around. Spacebar stops cube from rotating
*/
#ifndef _PG2_
#define _PG2_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <SDL.h>
#include <SDL_opengl.h>
using namespace std;

#define PI 3.1415926535897932384626433832795

#define WIDTH 640
#define HEIGHT 480

SDL_Window *w;
SDL_Surface **album;
GLuint *texture;
double xrot, yrot, zrot,x,y,z;

int main (int argc, char **argv);
void redraw(); //draw cube and images on cube
void bindImage(int index); //bind image to surface
void close(); //stop memory leaks
void init(); //initialize SDL/openGL

#endif
