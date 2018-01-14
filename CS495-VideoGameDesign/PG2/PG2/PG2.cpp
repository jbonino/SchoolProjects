/*
Joe Bonino - CS495 Video Game Programming
This program implements SDL/openGL to create a rubiks
cube. Arrow keys and A/Z are required to rotate cube
around. Spacebar stops cube from rotating
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "PG2.h"
using namespace std;

int main (int argc, char **argv) {
	init(); //initialize SDL/openGL
	xrot = yrot, xrot = 0; //if degrees is rotating
	x=y=z=0; //holds current x,y,z degree
	SDL_Event e;
	while (true) {
		if (SDL_PollEvent (&e)){
			if (e.type==SDL_QUIT) break;
			if(e.type==SDL_KEYDOWN)
				switch (e.key.keysym.sym){
					case SDLK_LEFT: yrot=1; break;
					case SDLK_RIGHT: yrot=-1; break;
					case SDLK_UP: xrot=1; break;
					case SDLK_DOWN: xrot=-1; break;
					case SDLK_a: zrot=1; break;
					case SDLK_z: zrot=-1; break;
					case SDLK_SPACE: xrot=0; yrot=0; zrot=0; break; //stop all rotations
				}
			}
		redraw();
	}
	close();
	return 0;
}

void redraw(){
	//clear colors
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//reset to default identity
	glLoadIdentity ();
	//move into screen -5 on z axis
	glTranslatef (0,0,-5);
	//rotate
	glRotatef (x+=xrot,10,0,0);
	cout<<x<<endl;
	glRotatef (y+=yrot,0,10,0);
	glRotatef (z+=zrot,0,0,10);
	
	//front
	bindImage(0);
	glColor3f(1,1,1);
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,-1,1);
		glTexCoord2f(1,0);glVertex3f (1,-1,1);
		glTexCoord2f(1,1);glVertex3f (1,1,1);
		glTexCoord2f(0,1);glVertex3f (-1,1,1);
	glEnd ();
	//back
	bindImage(1);
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,-1,-1);
		glTexCoord2f(1,0);glVertex3f (1,-1,-1);
		glTexCoord2f(1,1);glVertex3f (1,1,-1);
		glTexCoord2f(0,1);glVertex3f (-1,1,-1);
	glEnd ();
	//left
	bindImage(2);
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,-1,-1);
		glTexCoord2f(1,0);glVertex3f (-1,-1,1);
		glTexCoord2f(1,1);glVertex3f (-1,1,1);
		glTexCoord2f(0,1);glVertex3f (-1,1,-1);
	glEnd ();
	//right
	bindImage(3);
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (1,-1,-1);
		glTexCoord2f(1,0);glVertex3f (1,-1,1);
		glTexCoord2f(1,1);glVertex3f (1,1,1);
		glTexCoord2f(0,1);glVertex3f (1,1,-1);
	glEnd ();
	//top
	bindImage(4);
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,-1,-1);
		glTexCoord2f(1,0);glVertex3f (1,-1,-1);
		glTexCoord2f(1,1);glVertex3f (1,-1,1);
		glTexCoord2f(0,1);glVertex3f (-1,-1,1);
	glEnd ();
	//bottom
	bindImage(5);
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,1,-1);
		glTexCoord2f(1,0);glVertex3f (1,1,-1);
		glTexCoord2f(1,1);glVertex3f (1,1,1);
		glTexCoord2f(0,1);glVertex3f (-1,1,1);
	glEnd ();
	SDL_GL_SwapWindow (w);
}

void bindImage(int index){
	//bind image to texture on surface
	glBindTexture (GL_TEXTURE_2D,texture[index]);
	glTexImage2D(GL_TEXTURE_2D,0,3,album[index]->w,album[index]->h,0,GL_RGB,GL_UNSIGNED_BYTE,album[index]->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void init(){
	//initialize SDL and openGL

	//grab images and apply to surfaces
	album = new SDL_Surface *[6];
	album[0] = IMG_Load ("res/An_Awesome_Wave.jpg");
	album[1] = IMG_Load ("res/Ellington_At_Newport.jpg");
	album[2] = IMG_Load ("res/Mothers_Milk.jpg");
	album[3] = IMG_Load ("res/Pet_Sounds.jpg");
	album[4] = IMG_Load ("res/Rearviewmirror.jpg");
	album[5] = IMG_Load ("res/To_Pimp_A_Butterfly.jpg");
	texture = new GLuint[6];
	for(int index=0;index<6;index++){
		glGenTextures (1,&texture[index]);
	}

	SDL_Init (SDL_INIT_VIDEO);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION,2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION,1);
	w = SDL_CreateWindow ("Shapes",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
	SDL_GL_CreateContext (w); //associates the OpenGL commands to window w.
	SDL_GL_SetSwapInterval (1);
	glShadeModel (GL_SMOOTH);
	glClearColor (0,0,0,0);
	glClearDepth (1);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	double ratio = ((double)WIDTH) / ((double)HEIGHT);
	glViewport (0,0,WIDTH,HEIGHT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-tan(45.0/360*PI)*0.1*ratio,tan(45.0/360*PI)*0.1*ratio,-tan(45.0/360*PI)*0.1,tan(45.0/360*PI)*0.1,0.1,100);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void close(){
	//rid of memory leaks
	for(int i=0;i<6;i++)
		SDL_FreeSurface(album[i]);
	delete[] album;
	SDL_DestroyWindow (w);
	SDL_Quit ();
}