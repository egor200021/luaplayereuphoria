/*
*************************************************************************
//Name : Euphoria Engine V0.1.
//Programmer : Zack (Danny Glover) : danny86@live.ie .
//Licence : Undecided.
//Platforms : PSP & PC. More to follow.
//Usage Rights : I currently do not permit any of this source code to be used without my permission.
**************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspsdk.h>
#include <psprtc.h>

#include "../graphics/graphics.h"
#include "../../include/luaplayer.h"
#include "map.h"

//#define USEOLDMAP

static int tid,tid2,tid3,tid4,tx,tx2,tx3,tx4,ty,ty2,ty3,ty4;

//#Load a Tile Map
void loadMap(int sizeX, int sizeY, const char *layer1, const char *layer2, const char *layer3)

{
	int x, y;
	
	
	FILE *fp, *fp2, *fp3;


	fp = fopen(layer1, "rb");  //Layer 1
	
	fp2 = fopen(layer2, "rb"); //Layer 2
	
	fp3 = fopen(layer3, "rb"); //Layer 3

	
	
	/* Read the data from the file into the map */
	
	
	map.maxX = map.maxY = 0;

	
	for (y = 0; y < sizeY; y++){
		for (x = 0; x < sizeX; x++){
			
			fscanf(fp, "%d ", &map.tile[y][x]);   //Layer 1
			
			fscanf(fp2, "%d ", &map.tile2[y][x]); //Layer 2
			
			fscanf(fp3, "%d ", &map.tile3[y][x]); //Layer 3
			
			
			if (map.tile[y][x] != BLANK_TILE)
			{
				
				if (x > map.maxX)
				{
					
					map.maxX = x;
				
				}
				
				
				if (y > map.maxY)
				{
					
					map.maxY = y;
				
				}
			
			}
		
		}
	
	}
	
	
	
	map.maxX += 1;

	map.maxY += 1;
	
	
	
	/* Set the start coordinates */
	
	
	
	map.startX = map.startY = 0;
	
	
	
	/* Set the maximum scroll position of the map */
	
	
	map.maxX = sizeX * TILE_SIZE;
	
	map.maxY = sizeY * TILE_SIZE;
	
	
	
	/* Set the fileName */
	
	
	map.layer1 = layer1; //Layer 1
	
	map.layer2 = layer2; //Layer 2
	
	map.layer3 = layer3; //Layer 3
	
	/* Close the files afterwards */

	
	fclose(fp);
	
	fclose(fp2);
	
	fclose(fp3);

}

//## Draw a Tile Map
void drawMap(int tilesAcross, Image *tileSheet, Image *backGround)
{

	int mapX, mx, my, x1, x2, mapY, y1, y2;

	mapX = map.startX / TILE_SIZE;
	x1 = (map.startX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
	
	mapY = map.startY / TILE_SIZE;
	y1 = (map.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	/* Draw the map starting at the startX and startY */
	blitAlphaImageToScreen(0, 0, 480, 272, backGround, 0, 0, 255);

		for (my = y1; my < y2; my += TILE_SIZE)
		
		{
			mapX = map.startX / TILE_SIZE;
					
			for (mx = x1; mx < x2; mx += TILE_SIZE)
			
			{      
				if (map.tile[mapY][mapX] != BLANK_TILE)
				{        
					tid = map.tile[mapY][mapX];
					tx = tid % tilesAcross, ty = tid /tilesAcross;
					blitAlphaImageToScreen(tx * TILE_SIZE, ty * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileSheet, mx, my, 255);
				}
			
				if (map.tile2[mapY][mapX] != BLANK_TILE)
			
				{
               		tid2 = map.tile2[mapY][mapX];
					tx2 = tid2 % tilesAcross, ty2 = tid2 / tilesAcross;
					blitAlphaImageToScreen(tx2 * TILE_SIZE, ty2 * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileSheet, mx, my, 255);
				}	
            
				if (map.tile3[mapY][mapX] != BLANK_TILE)
			
				{
               		tid3 = map.tile3[mapY][mapX];
					tx3 = tid3 % tilesAcross, ty3 = tid3 / tilesAcross;
					blitAlphaImageToScreen(tx3 * TILE_SIZE, ty3 * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileSheet, mx, my, 255);
				}                    
				mapX++;
			}		
			mapY++;
		}
}
