/*
*************************************************************************
//Name : Euphoria Engine V0.1.
//Programmer : Zack (Danny Glover) : danny86@live.ie .
//Licence : Undecided.
//Platforms : PSP & PC. More to follow.
//Usage Rights : I currently do not permit any of this source code to be used without my permission.
**************************************************************************
*/

#ifndef PLAYER_H
#define PLAYER_H

#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 6.6
#define PLAYER_SPEED 2.2
#define JUMP_SPEED 8.2

struct Entity {
    int w, h, onGround;
    float x, y, dirX, dirY;
	int startX, startY;
	int maxX, maxY;
	int sizeX, sizeY;
	int thinkTime;
};

void centerEntityOnMap(int x, int y);
void checkToMap(int x, int y, int dirX, int dirY, int w, int h, int onGround, int thinkTime, int sizeX, int sizeY);

#endif
