/*
Joe Bonino - CS495 Video Game Programming
This program implements SDL so create a pacman
like game. Arrow keys are required to move pacman
around and you must eat all the steak to win.

*/
#ifndef _PG1_
#define _PG1_

#include <iostream>
#include <string>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <time.h>
#include <stdlib.h>
using namespace std;


//declare global variables
SDL_Window *mw;
SDL_Surface *ms, *steak, *pacman, *plo,*plc,*pro,*prc,*puo,*puc,*pdo,*pdc;
SDL_Rect *r;
Mix_Chunk *effect,*starter;
SDL_Rect steakArray[10];
SDL_Rect pcman; //pacman rect
int start; //timer

int direction;
bool isEmp=true;
double pacx, pacy;

int main (int argc, char **argv);
void init (); //initialize window
void draw (); //get images to surfaces
void close (); //close surfaces/ destroy windows for memory leaks
void redraw (); //redraw constantly for animation

#endif