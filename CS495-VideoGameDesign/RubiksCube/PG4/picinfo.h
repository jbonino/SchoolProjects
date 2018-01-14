#ifndef PICINFO_H
#define PICINFO_H

//This stores "sticker information" I have 54 of these floating around
class picinfo {
public:
 int face, row, col, a, tx; //tx is which of the six images.  r and c are 0-2 to indicate which 9th of the image.  a is 0, 90, 180, or 270, to indicate which way the sticker is oriented.
 int rot;
 int b,t,l,r;
 bool flag; //true if this sticker is in the process of being animated

 picinfo (int side, int row, int col, int a, int tx);
 void rotate (int angle);
};

#endif