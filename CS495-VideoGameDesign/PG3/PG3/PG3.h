/*
Joe Bonino - CS495 Video Game Programming
This program implements SDL/openGL to create a rubiks
cube. Arrow keys and A/Z are required to rotate cube
around. Spacebar stops cube from rotating
*/
#ifndef _PG3_
#define _PG3_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <SDL.h>
#include <SDL_opengl.h>
#include "picinfo.h"
#include "glQuaternion.h"
using namespace std;

#define PI 3.1415926535897932384626433832795

#define WIDTH 640
#define HEIGHT 480

int angle=0;
bool rot=false;
int rotatingside;

SDL_Window *w;
SDL_Surface **album;
GLuint *texture;
double xrot, yrot, zrot,x,y,z;
picinfo *sticker [6][3][3];
picinfo *temp;
picinfo *temp2;
picinfo *temp3;
picinfo *temp4;
picinfo *temp5;
picinfo *temp6;

bool counter=false;

int main (int argc, char **argv);
void redraw(); //draw cube and images on cube
void close(); //stop memory leaks
void init(); //initialize SDL/openGL

void LoadTextures();
void drawsquare (picinfo *p, int row, int col);
void rotate (int s);
void drawBlackCube ();
void rotateFront(int s);
void swapOutside(int b[], int l[], int t[], int r[]);
void swapOutsideCounter(int b[], int r[], int t[], int l[]);
void spin(int s[], int angle);
void control(const Uint8* keyState);

#endif
