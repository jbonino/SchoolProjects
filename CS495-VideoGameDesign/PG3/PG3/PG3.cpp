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
#include "PG3.h"
#include "picinfo.h"

using namespace std;

int main (int argc, char **argv) {
	init(); //initialize SDL/openGL
	LoadTextures();
	yrot = xrot = 0; //if degrees is rotating
	x=y=z=0; //holds current x,y,z degree
	SDL_Event e;
	while (true) {
		if (SDL_PollEvent (&e)){
			if (e.type==SDL_QUIT) break;
			if(e.type==SDL_KEYDOWN)
				switch (e.key.keysym.sym){
					case SDLK_RSHIFT:	counter=true;break;
					case SDLK_LSHIFT:	counter=true;break;
					case SDLK_LEFT:		yrot=1;break;
					case SDLK_RIGHT:	yrot=-1;break;
					case SDLK_UP:		xrot=1;break;
					case SDLK_DOWN:		xrot=-1;break;
					case SDLK_a:		zrot=1;break;
					case SDLK_z:		zrot=-1;break;
					case SDLK_SPACE:	xrot=0; yrot=0; zrot=0; break; //stop all rotations

					case SDLK_1: rotate(0);break;
					case SDLK_2: rotate(1);break;
					case SDLK_3: rotate(2);break;
					case SDLK_4: rotate(3);break;
					case SDLK_5: rotate(4);break;
					case SDLK_6: rotate(5);break;
					case SDLK_p:
						sticker[0][0][0]=sticker[1][0][0];
						sticker[1][0][0]=sticker[2][0][0];
						sticker[2][0][0]=sticker[1][0][0];
						sticker[3][0][0]=sticker[1][0][0];
						sticker[4][0][0]=sticker[1][0][0];
						sticker[5][0][0]=sticker[1][0][0];
						sticker[0][0][1]=sticker[1][0][0];
						sticker[1][0][1]=sticker[2][0][0];
						sticker[2][0][1]=sticker[1][0][0];
						sticker[3][0][1]=sticker[1][0][0];
						sticker[4][0][1]=sticker[1][0][0];
						sticker[5][0][1]=sticker[1][0][0];
						break;
				}
			if(e.type==SDL_KEYUP)
				switch (e.key.keysym.sym){
					case SDLK_LSHIFT: counter=false;
					case SDLK_RSHIFT: counter=false;
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
	glTranslatef (0,0,-6);
	glQuaternion q1, q2, q3, q4;
	q1.CreateFromAxisAngle (1,0,0,x+=xrot); //rotate xrot degrees around x-axis
	q2.CreateFromAxisAngle (0,1,0,y+=yrot); //rotate yrot degrees around the y-axis
	q3.CreateFromAxisAngle(0,0,1,z+=zrot);
	q4.CreateFromAxisAngle(0,0,0,0);
	GLfloat pm[16];
	q4 = q1*q2*q3*q4;
	q4.Normalize(); //make the absolute value one
	q4.CreateMatrix (pm);
	glMultMatrixf (pm);

	drawBlackCube();
	for(int s=0;s<6;s++){
		if(s>0&&s<4) glRotatef(90,0,1,0);
		if(s==4){ glRotatef(90,0,1,0);glRotatef(90,1,0,0);}
		if(s==5) glRotatef(180,1,0,0);
		for(int r=0;r<3;r++)
			for(int c=0;c<3;c++)
				drawsquare(sticker[s][r][c],r,c);
			
			
	}
	SDL_GL_SwapWindow (w);
}
void drawsquare (picinfo *p, int row, int col){
	glPushMatrix();
	glTranslatef((row*0.666)-0.666,(col*0.666)-0.666,0);
	glRotatef(p->a,0,0,1);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,texture[p->tx]);
	glBegin (GL_QUADS);
		glTexCoord2f((p->row*0.333),(p->col*0.333));				glVertex3f (-0.3,-0.3,1.001);
		glTexCoord2f((p->row*0.333)+0.333,(p->col*0.333));			glVertex3f (0.3,-0.3,1.001);
		glTexCoord2f((p->row*0.333)+0.333,(p->col*0.333)+0.333);	glVertex3f (0.3,0.3,1.001);
		glTexCoord2f((p->row*0.333),(p->col*0.333)+0.333);			glVertex3f (-0.3,0.3,1.001);
	glEnd ();
	glPopMatrix();
}

void rotateFront(int s){
	//swap front!
	picinfo *temp = new picinfo(0,0,0,0,0);
	picinfo *temp2 = new picinfo(0,0,0,0,0);

	if(counter){
		temp=sticker[s][0][0];
		temp2=sticker[s][0][1];

		sticker[s][0][0]=sticker[s][0][2];
		sticker[s][0][1]=sticker[s][1][2];
		sticker[s][0][2]=sticker[s][2][2];
		sticker[s][1][2]=sticker[s][2][1];
		sticker[s][2][2]=sticker[s][2][0];
		sticker[s][2][1]=sticker[s][1][0];
		sticker[s][2][0]=temp;
		sticker[s][1][0]=temp2;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				sticker[s][i][j]->rotate(90);
	}
	else{
		temp=sticker[s][0][2];
		temp2=sticker[s][1][2];

		sticker[s][1][2]=sticker[s][0][1];
		sticker[s][0][2]=sticker[s][0][0];
		sticker[s][0][1]=sticker[s][1][0];
		sticker[s][0][0]=sticker[s][2][0];
	
		sticker[s][1][0]=sticker[s][2][1];
		sticker[s][2][0]=sticker[s][2][2];
		sticker[s][2][1]=temp2;
		sticker[s][2][2]=temp;
	
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				sticker[s][i][j]->rotate(-90);
	}

}
void rotate (int s){
	angle=90;
	rotatingside=s;
	rotateFront(s);
	rot=true;
	if(s==0){
		int b[7] = {0,2,1,2,2,2,4}; //4
		int l[7] = {2,2,2,1,2,0,3}; //3
		int t[7] = {2,0,1,0,0,0,5}; //5
		int r[7] = {0,0,0,1,0,2,1}; //1
		if(counter){
			swapOutsideCounter(b,r,t,l);
			//rotate
			spin(b,90);
			spin(l,90);
			spin(t,90);
			spin(r,90);
		}else{
			swapOutside(b,r,t,l);
			//rotate
			spin(b,-90);
			spin(l,-90);
			spin(t,-90);
			spin(r,-90);
		}
	}
	else if(s==1){
		int b[7] = {2,2,2,1,2,0,4}; //4
		int l[7] = {2,2,2,1,2,0,0}; //0
		int t[7] = {2,2,2,1,2,0,5}; //5
		int r[7] = {0,0,0,1,0,2,2}; //2
		if(counter){
			swapOutsideCounter(b,r,t,l);
			//rotate
			spin(r,180);
			spin(t,180);
		}else{
		swapOutside(b,r,t,l);
		//rotate
		spin(b,180);
		spin(r,180);
		}
	}

	else if(s==2){
		int b[7] = {2,0,1,0,0,0,4}; //4
		int r[7] = {0,0,0,1,0,2,3}; //3
		int t[7] = {0,2,1,2,2,2,5}; //5
		int l[7] = {2,2,2,1,2,0,1}; //1

		if(counter){
			swapOutsideCounter(b,r,t,l);
			//rotate
			spin(t,-90);
			spin(b,-90);
			spin(r,-90);
			spin(l,-90);
		}else{
			swapOutside(b,r,t,l);
			//rotate
			spin(b,90);
			spin(r,90);
			spin(t,90);
			spin(l,90);
		}
	}

	else if(s==3){
		int b[7] = {0,0,0,1,0,2,4}; //4
		int r[7] = {0,0,0,1,0,2,0}; //0
		int t[7] = {0,0,0,1,0,2,5}; //5
		int l[7] = {2,2,2,1,2,0,2}; //2
		if(counter){
			swapOutsideCounter(b,r,t,l);
			//rotate
			spin(b,180);
			spin(l,180);
		}else{
			swapOutside(b,r,t,l);		
			//rotate
			spin(t,180);
			spin(l,180);
		}
	}

	else if(s==4){
		int b[7] = {2,0,1,0,0,0,2}; //
		int r[7] = {2,0,1,0,0,0,1}; //
		int t[7] = {2,0,1,0,0,0,0}; //
		int l[7] = {2,0,1,0,0,0,3}; //

		if(counter) swapOutsideCounter(b,r,t,l);
		else swapOutside(b,r,t,l);
		
	}

	else if(s==5){
		int b[7] = {0,2,1,2,2,2,0}; //
		int r[7] = {0,2,1,2,2,2,1}; //
		int t[7] = {0,2,1,2,2,2,2}; //
		int l[7] = {0,2,1,2,2,2,3}; //
		if(counter) swapOutsideCounter(b,r,t,l);
		else swapOutside(b,r,t,l);
	}

}
void spin(int s[], int angle){
	sticker[s[6]] [ s[0] ][ s[1] ]->rotate(angle);
	sticker[s[6]] [ s[2] ][ s[3] ]->rotate(angle);
	sticker[s[6]] [ s[4] ][ s[5] ]->rotate(angle);
}

void swapOutside(int b[], int r[], int t[], int l[]){
	
	temp= sticker[b[6]] [ b[4] ][ b[5] ];
	temp2=sticker[b[6]] [ b[2] ][ b[3] ];
	temp3=sticker[b[6]] [ b[0] ][ b[1] ];

	sticker[b[6]][b[4]][b[5]]=sticker[r[6]][r[4]][r[5]];
	sticker[b[6]][b[2]][b[3]]=sticker[r[6]][r[2]][r[3]];
	sticker[b[6]][b[0]][b[1]]=sticker[r[6]][r[0]][r[1]];

	sticker[r[6]][r[4]][r[5]]=sticker[t[6]][t[4]][t[5]];
	sticker[r[6]][r[2]][r[3]]=sticker[t[6]][t[2]][t[3]];
	sticker[r[6]][r[0]][r[1]]=sticker[t[6]][t[0]][t[1]];

	sticker[t[6]][t[4]][t[5]]=sticker[l[6]][l[4]][l[5]];
	sticker[t[6]][t[2]][t[3]]=sticker[l[6]][l[2]][l[3]];
	sticker[t[6]][t[0]][t[1]]=sticker[l[6]][l[0]][l[1]];

	sticker[l[6]][l[4]][l[5]]=temp;
	sticker[l[6]][l[2]][l[3]]=temp2;
	sticker[l[6]][l[0]][l[1]]=temp3;
	
}
void swapOutsideCounter(int b[], int r[], int t[], int l[]){
	
	temp= sticker[b[6]] [ b[4] ][ b[5] ];
	temp2=sticker[b[6]] [ b[2] ][ b[3] ];
	temp3=sticker[b[6]] [ b[0] ][ b[1] ];

	sticker[b[6]][b[4]][b[5]]=sticker[l[6]][l[4]][l[5]];
	sticker[b[6]][b[2]][b[3]]=sticker[l[6]][l[2]][l[3]];
	sticker[b[6]][b[0]][b[1]]=sticker[l[6]][l[0]][l[1]];

	sticker[l[6]][l[4]][l[5]]=sticker[t[6]][t[4]][t[5]];
	sticker[l[6]][l[2]][l[3]]=sticker[t[6]][t[2]][t[3]];
	sticker[l[6]][l[0]][l[1]]=sticker[t[6]][t[0]][t[1]];

	sticker[t[6]][t[4]][t[5]]=sticker[r[6]][r[4]][r[5]];
	sticker[t[6]][t[2]][t[3]]=sticker[r[6]][r[2]][r[3]];
	sticker[t[6]][t[0]][t[1]]=sticker[r[6]][r[0]][r[1]];

	sticker[r[6]][r[4]][r[5]]=temp;
	sticker[r[6]][r[2]][r[3]]=temp2;
	sticker[r[6]][r[0]][r[1]]=temp3;
	
}

void drawBlackCube(){
	glBindTexture (GL_TEXTURE_2D,NULL);
	glColor3f(0,0,0);
	glBegin (GL_QUADS);
		glTexCoord2f(0,1);glVertex3f (-1,-1,1);
		glTexCoord2f(1,1);glVertex3f (1,-1,1);
		glTexCoord2f(1,0);glVertex3f (1,1,1);
		glTexCoord2f(0,0);glVertex3f (-1,1,1);
	glEnd ();
	//back
	glBegin (GL_QUADS);
		glTexCoord2f(1,1);glVertex3f (-1,-1,-1);
		glTexCoord2f(0,1);glVertex3f (1,-1,-1);
		glTexCoord2f(0,0);glVertex3f (1,1,-1);
		glTexCoord2f(1,0);glVertex3f (-1,1,-1);
	glEnd ();
	//left
	glBegin (GL_QUADS);
		glTexCoord2f(0,1);glVertex3f (-1,-1,-1);
		glTexCoord2f(1,1);glVertex3f (-1,-1,1);
		glTexCoord2f(1,0);glVertex3f (-1,1,1);
		glTexCoord2f(0,0);glVertex3f (-1,1,-1);
	glEnd ();
	//right
	glBegin (GL_QUADS);
		glTexCoord2f(1,1);glVertex3f (1,-1,-1);
		glTexCoord2f(0,1);glVertex3f (1,-1,1);
		glTexCoord2f(0,0);glVertex3f (1,1,1);
		glTexCoord2f(1,0);glVertex3f (1,1,-1);
	glEnd ();
	//top
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,-1,-1);
		glTexCoord2f(1,0);glVertex3f (1,-1,-1);
		glTexCoord2f(1,1);glVertex3f (1,-1,1);
		glTexCoord2f(0,1);glVertex3f (-1,-1,1);
	glEnd ();
	//bottom
	glBegin (GL_QUADS);
		glTexCoord2f(0,0);glVertex3f (-1,1,-1);
		glTexCoord2f(1,0);glVertex3f (1,1,-1);
		glTexCoord2f(1,1);glVertex3f (1,1,1);
		glTexCoord2f(0,1);glVertex3f (-1,1,1);
	glEnd ();
}
void init(){
	//initialize SDL wrapper for openGL
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

	//give texture to picinfo object called sticker
	//init sticker 3d array
	for(int i=0;i<6;i++)
		for(int r=0;r<3;r++)
			for(int c=0;c<3;c++)
				sticker[i][r][c] = new picinfo(i,r,c,0,i);

	
	
	picinfo *temp6 = new picinfo(0,0,0,0,0);
}
void LoadTextures(){
	album = new SDL_Surface *[6];
	texture = new GLuint[6];

	album[0] = IMG_Load ("res//An_Awesome_Wave.jpg");
	album[1] = IMG_Load ("res//Ellington_At_Newport.jpg");
	album[2] = IMG_Load ("res//Mothers_Milk.jpg");
	album[3] = IMG_Load ("res//Pet_Sounds.jpg");
	album[4] = IMG_Load ("res//Rearviewmirror.jpg");
	album[5] = IMG_Load ("res//To_Pimp_A_Butterfly.jpg");
	
	for(int i=0;i<6;i++){
		glGenTextures (3,&texture[i]);
		glBindTexture (GL_TEXTURE_2D,texture[i]);
		glTexImage2D(GL_TEXTURE_2D,0,3,album[i]->w,album[i]->h,0,GL_RGB,GL_UNSIGNED_BYTE,album[i]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glBindTexture( GL_TEXTURE_2D, NULL );
		SDL_FreeSurface(album[i]);
	}
}
void close(){
	//rid of memory leaks
	delete[] album;
	delete temp,temp2,temp3,temp4,temp5,temp6;
	SDL_DestroyWindow (w);
	SDL_Quit ();
}
