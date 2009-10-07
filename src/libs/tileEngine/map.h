/*
*************************************************************************
//Name : Euphoria Engine V0.1.
//Programmer : Zack (Danny Glover) : danny86@live.ie .
//Licence : Undecided.
//Platforms : PSP & PC. More to follow.
//Usage Rights : I currently do not permit any of this source code to be used without my permission.
**************************************************************************
*/

#ifndef MAP_H
#define MAP_H

#define MAX_MAP_X 800 //CANT BE A DEFINE
#define MAX_MAP_Y 800 //CANT BE A DEFINE
#define TILE_SIZE 16
#define BLANK_TILE 0
#define MAX_TILES 270 //CANT BE A DEFINE
//#define TILES_ACROSS 30
//CANT BE A DEFINE

struct Map{
	char *fileName;
	char *map;
	char *layer1, *layer2, *layer3, *layer4;
	int startX, startY;
	int maxX, maxY;
	int tile[MAX_MAP_Y][MAX_MAP_X];  //Layer 1 - No collision.
	int tile2[MAX_MAP_Y][MAX_MAP_X]; //Layer 2 - No collision.
	int tile3[MAX_MAP_Y][MAX_MAP_X]; //Layer 3 - Collision layer.
	//int tile4[MAX_MAP_Y][MAX_MAP_X]; //Layer 4 - Object interaction layer (ie indicate if you can go down a pipe etc).
};

struct Map map;

void loadMap(int sizeX, int sizeY, const char *layer1, const char *layer2, const char *layer3);

void drawMap(int tilesAcross, Image *tileSheet, Image *backGround);

#endif
