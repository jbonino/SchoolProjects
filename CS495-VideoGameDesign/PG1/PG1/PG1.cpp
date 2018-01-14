/*
Joe Bonino - CS495 Video Game Programming
This program implements SDL so create a pacman
like game. Arrow keys are required to move pacman
around and you must eat all the steak to win.

*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <SDL.h>
#include "PG1.h"
#include <time.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	//draw steak at random intervals that fit on the screen and dont lie on pacman
	for(int i=0;i<10;i++){
		steakArray[i].x=rand()%570+50; 
		steakArray[i].y=rand()%410+50;
		steakArray[i].w=22;
		steakArray[i].h=22;
	}
	//create window and surfaces
	init ();
	//load images and sounds to surfaces/audio
	draw ();
	//play startup pacman sound
	Mix_PlayChannel (-1,starter,0);
	//start pacman at cordinates 0,0
	pacx = pacy = 0;
	/*r = NULL;*/
	bool quit = false;
	start=(int)SDL_GetTicks()/100;
	SDL_Event e; //This is an event that we discover
	while (true) {
		 if (SDL_PollEvent (&e)) { //true if there's an event, false if there's no event pending
			 if (e.type==SDL_QUIT) break; //Someone clicked the close box (that X in the upper right corner)
			 if (e.type==SDL_KEYDOWN) {
				 switch (e.key.keysym.sym) {
					 case SDLK_UP: direction=1; break;
					 case SDLK_DOWN: direction=3; break;
					 case SDLK_LEFT: direction=0; break;					 
					 case SDLK_RIGHT: direction=2; break;
				 }
				 Mix_PlayChannel (-1,effect,0); //play pacman moving sound
			 }
		 }
		 redraw (); //redraw after event or keep redrawing
	}
	close (); //close everything so no memory leaks
	return 0;

}

void init () {
	//initialize window
	SDL_Init (SDL_INIT_VIDEO);
	mw = SDL_CreateWindow ("Event Loop",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
	ms = SDL_GetWindowSurface (mw);
	Mix_OpenAudio (44100,MIX_DEFAULT_FORMAT,2,2048);
}

void draw () {
	//load images and sounds for project
	pacman = IMG_Load ("res/pacman_open_r.png");
	plo = IMG_Load ("res/pacman_open_l.png");
	plc = IMG_Load ("res/pacman_closed_l.png");
	pro = IMG_Load ("res/pacman_open_r.png");
	prc = IMG_Load ("res/pacman_closed_r.png");
	puo = IMG_Load ("res/pacman_open_u.png");
	puc = IMG_Load ("res/pacman_closed_u.png");
	pdo = IMG_Load ("res/pacman_open_d.png");
	pdc = IMG_Load ("res/pacman_closed_d.png");
	steak = IMG_Load ("res/steak.png");
	effect = Mix_LoadWAV ("res/pacman_chomp.wav");
	starter = Mix_LoadWAV ("res/pacman_beginning.wav");
}

void close () {
	//close everything so there are no memory leaks
	SDL_FreeSurface (steak);
	SDL_FreeSurface (pacman);
	SDL_FreeSurface (plc);
	SDL_FreeSurface (plo);
	SDL_FreeSurface (prc);
	SDL_FreeSurface (pro);
	SDL_FreeSurface (puo);
	SDL_FreeSurface (puc);
	SDL_FreeSurface (pdo);
	SDL_FreeSurface (pdc);
	SDL_DestroyWindow (mw);
	Mix_Quit ();
	SDL_Quit ();
}

void redraw () {
	int start = SDL_GetTicks()/100;

	//swap open/close every second
	//if right key was pressed, pacman moving right
	if(direction==2){
		pacx+=.5; //move pacman right by one 
		if(start%2==1) pacman=prc;
		else pacman=pro;
	}
	//if left arrow key was pressed, pacman moving left
	if(direction==0){
		 pacx-=.5; //move pacman left by one
		if(start%2==1) pacman=plc;
		else pacman=plo;
	}
	//if up arrow key was pressed, pacman moving up
	if(direction==1){
		pacy-=.5; //move pacman up by one
		if(start%2==1) pacman=puc;
		else pacman=puo;
	}
	//if down arrow key was pressed, pacman moving down
	if(direction==3){
		pacy+=.5; //move pacman down by one
		if(start%2==1) pacman=pdc;
		else pacman=pdo;
	}
	
	//fill mainSurface (ms) with a rectangle and color it black
	SDL_FillRect (ms,NULL,SDL_MapRGB (ms->format,0,0,0));

	//boundries for pacman to stay in. Screen ratio is 640 x 480. 
	//pacman is 50
	if (pacx < 10) pacx = 10;
	if (pacx >= 580) pacx = 580;
	if (pacy < 10) pacy = 10;
	if (pacy >= 420) pacy = 420;

	//pacmans rect to draw pacman
	pcman.x = (int) pacx;
	pcman.y = (int) pacy;
	pcman.w = 50;
	pcman.h = 50;
	//detect collisions between pacman and steak.
	//set steaks x cordinate to 0 if it had a collision with pacman, or was eaten
	for(int i=0;i<10;i++)
		if(pacx<steakArray[i].x&&pacx+50>steakArray[i].x)
			if(pacy<steakArray[i].y&&pacy+40>steakArray[i].y)
				steakArray[i].x=0;
	
	//redraw the steak inless it is eaten. If steak is eaten, its x cordinate is set to 0.
	//No steak will randomly spawn to have their x cordinate 0.
	isEmp=true;
	for(int i=0;i<10;i++)
		if(steakArray[i].x!=0){
			SDL_BlitScaled(steak,NULL,ms,&steakArray[i]);
			isEmp=false;
		}
		
	//draw pacman surface in pcman rect 
	/*cout<<"Pacx: "<<pacx<<"	pacy: "<<pacy<<" Time: "<<start<<endl;*/
	SDL_BlitScaled(pacman, NULL, ms, &pcman );

	SDL_UpdateWindowSurface (mw); //redraw window
}

