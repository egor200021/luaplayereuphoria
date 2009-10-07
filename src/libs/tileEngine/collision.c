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
#include "collision.h"
#include "map.h"

struct Entity entity;

//##Position the player relative to the map
void centerEntityOnMap(int x, int y)
{
    map.startX = x - (SCREEN_WIDTH / 2);
    
    if (map.startX < 0)
    {
        map.startX = 0;
    }
    
    else if (map.startX + SCREEN_WIDTH >= map.maxX)
    {
        map.startX = map.maxX - SCREEN_WIDTH;
    }
    
    map.startY = y - (SCREEN_HEIGHT / 2) ; //To stop the map scrolling down unnessacarily
    
    if (map.startY < 0)
    {
        map.startY = 0;
    }
    
    else if (map.startY + SCREEN_HEIGHT >= map.maxY) 
    {
        map.startY = map.maxY - SCREEN_HEIGHT;
    }
}


void checkToMap(int x, int y, int dirX, int dirY, int w, int h, int onGround, int thinkTime, int sizeX, int sizeY)
{
	int i, x1, x2, y1, y2;

	//Remove the user from the ground 
	
	onGround = 0;
	
	//Test the horizontal movement first
	
	i = h > TILE_SIZE ? TILE_SIZE : h;
	
	for (;;){
		x1 = (x + dirX) / TILE_SIZE;
		x2 = (x + dirX + w - 1) / TILE_SIZE;
	
		y1 = (y) / TILE_SIZE;
		y2 = (y + i - 1) / TILE_SIZE;
		
		if (x1 >= 0 && x2 < sizeX && y1 >= 0 && y2 < sizeY){
			if (dirX > 0){
				//Trying to move right
		
		//just check layer 3 (the collision layer
				if ((map.tile3[y1][x2] != BLANK_TILE) || (map.tile3[y2][x2] != BLANK_TILE))
				{
					//Place the player as close to the solid tile as possible
					x = x2 * TILE_SIZE - 1;
		            x -= w;
					dirX = 0;
				}  
			}
		
			else if (dirX < 0){
				//Trying to move left
		
				if ((map.tile3[y1][x1] != BLANK_TILE) || (map.tile3[y2][x1] != BLANK_TILE))
				{
					//Place the player as close to the solid tile as possible
					
					x = (x1 + 1) * TILE_SIZE;		
					dirX = 0;
				}
			 } 
		}
		
		//Exit this loop if we have tested all of the body
		
		if (i == h){
			break;
		}
		
		//Test the next block 
		
		i += TILE_SIZE;
		
		if (i > h){
			i = h;
		}
	}

	//Now test the vertical movement
	
	i = w > TILE_SIZE ? TILE_SIZE : w;
	
	for (;;){
		x1 = (x) / TILE_SIZE;
		x2 = (x + i) / TILE_SIZE;
	
		y1 = (y + dirY) / TILE_SIZE;
		y2 = (y + dirY + h) / TILE_SIZE;
		
		if (x1 >= 0 && x2 < sizeX && y1 >= 0 && y2 < sizeY){
			if (dirY > 0){
				//Trying to move down 
				
				if ((map.tile3[y2][x1] != BLANK_TILE) || (map.tile3[y2][x2] != BLANK_TILE))
				{
					//Place the player as close to the solid tile as possible
					
					y = y2 * TILE_SIZE;
					y -= h;		
					dirY = 0;					
					onGround = 1;
				}
		    }
		
			else if (dirY < 0){
				//Trying to move up
		
				if ((map.tile3[y1][x1] != BLANK_TILE) || (map.tile3[y1][x2] != BLANK_TILE))
				{
					//Place the player as close to the solid tile as possible
		
					y = (y1 + 1) * TILE_SIZE;		
					dirY = 0;
				}
			} 
		}
		
		if (i == w){
			break;
		}
		
		i += TILE_SIZE;
		
		if (i > w){
			i = w;
		}
	}

	//Now apply the movement

	x += dirX;
	y += dirY;
	
	if (x < 0)
	{
		x = 0;
	}
	
	else if (x + w >= map.maxX)
	{
		x = map.maxX - w - 1;
	}
//}
	
	if (y > map.maxY)
	{
		thinkTime = 60;
	}
	
}

/*
//##Initialize our player
void activatePlayer(struct entity *p)
{
	player.thinkTime = 0;    
}

//##Move our player along the TileMap
void movePlayer(struct entity *p)
{
	if (doOnce){
		//playerImg = loadImage("data/img/sprites/player/mario_luigi.png");
		p->thinkTime = 1;
	    //map.startY = map.maxY - 272;
	    p->x = 10;
	    p->y = 6300;
		doOnce = 0;
	}

	if (player.thinkTime == 0)
	{
		player.dirX = 0;
	
		//Gravity always pulls the player down 
	    
		player.dirY += GRAVITY_SPEED;
		
		if (player.dirY >= MAX_FALL_SPEED)
		{
			player.dirY = MAX_FALL_SPEED;
		}
		
	
		if (button.leftHeld)
		{
			player.dirX -= PLAYER_SPEED;
		}
		
		else if (button.rightHeld)
		{
			player.dirX += PLAYER_SPEED;
		}
		
		if (button.crossHeld)
		{
			if (player.onGround == 1)
			{
				player.dirY -= JUMP_SPEED;
			}
			
			button.crossHeld = 0;
		}
		
		centerEntityOnMap(&player);	
		checkToMap(&player);
    }
		
		if (player.thinkTime > 0)
		{
		  player.thinkTime--;
		  
		  if (p->thinkTime == 1){
		       p->x = 10;
	           p->y = 6300;
            }
		
		  if (player.thinkTime == 0)
		  { 
            activatePlayer(&player);
		  }
       }
}

//##Blit our player to the screen
void blitPlayer(struct entity *p)
{
    blitAlphaImageToScreen(p->frameX, p->frameY, p->w, p->h, playerImg, p->x - map.startX, p->y - map.startY, 255 );
}

//Initialize the player
void initPlayer()
{
	movePlayer(&player); //Initialize our player	
	blitPlayer(&player); //Draw the player
}
*/
