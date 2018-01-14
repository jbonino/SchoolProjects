#include "picinfo.h"

picinfo::picinfo (int face, int r, int c, int a, int tx) {

	this->face = face;
	this->row = r;
	this->col = c;
	this->a = a;
	this->tx = tx;
	flag = false;
}

void picinfo::rotate (int angle) { //this method gets called on 21 stickers  The angle is 0, 90, -90.
	a = (a+360+angle)%360;
	flag = true;
}
