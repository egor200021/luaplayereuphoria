/*
 * LuaPlayer Euphoria
 * ------------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE for details.
 *
 * Copyright (c) 2005 Frank Buss <fb@frank-buss.de> (aka Shine)
 * Copyright (c) 2009 Danny Glover <danny86@live.ie> (aka Zack) 
 *
 * Official Forum : http://www.retroemu.com/forum/forumdisplay.php?f=148
 * For help using LuaPlayer, code help, tutorials etc please visit the official site : http://www.retroemu.com/forum/forumdisplay.php?f=148
 *
 * Credits:
 * 
 * (from Shine/Zack) 
 *
 *   many thanks to the authors of the PSPSDK from http://forums.ps2dev.org
 *   and to the hints and discussions from #pspdev on freenode.net
 *
 * (from Zack Only)
 *
 * Thanks to Brunni for the Swizzle/UnSwizzle code (taken from oslib). 
 * Thanks to Arshia001 for AALIB. It is the sound engine used in LuaPlayer Euphoria. 
 * Thanks to HardHat for being a supportive friend and advisor.
 * Thanks to Benhur for IntraFont.
 * Thanks to Jono for the moveToVram code.
 * Thanks to Raphael for the Vram manager code.
 * Thanks to Osgeld, Dan369 & Cmbeke for testing LuaPlayer Euphoria for me and coming up with some neat ideas for it.
 * Thanks to the entire LuaPlayer Euphoria userbase, for using it and for supporting it's development. You guys rock!
 *
 *
 */
 
 //Below code is a mix of code from the SDK sample and code from LuaPlayer HM V5 (Thanks to both!)
 
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <string.h>
#include <psputility.h>

#include "../graphics/graphics.h"
#include "osk.h"
 
 
int getOskText(char *input, unsigned short *intext, unsigned short *desc)
{
	int done = 0;
	unsigned short outtext[128] = { 0 };
	
	SceUtilityOskData data;
	memset(&data, 0, sizeof(SceUtilityOskData));
	data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT; // Use system default for text input
	data.lines = 1;
	data.unk_24 = 1;
	data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL; // Allow all input types
	data.desc = desc;
	data.intext = intext;
	data.outtextlength = 128;
	data.outtextlimit = 50; // Limit input to 50 characters
	data.outtext = (unsigned short*)outtext;
		
	SceUtilityOskParams params;
	memset(&params, 0, sizeof(params));
	params.base.size = sizeof(params);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
	params.base.graphicsThread = 17;
	params.base.accessThread = 19;
	params.base.fontThread = 18;
	params.base.soundThread = 16;
	params.datacount = 1;
	params.data = &data;

	sceUtilityOskInitStart(&params);

	while(!done)
	{
		guStart();
		clearScreen(0xff554433);
		sceGuFinish();
    	sceGuSync(0,0);

		switch(sceUtilityOskGetStatus())
		{
			case PSP_UTILITY_DIALOG_VISIBLE:
	    		sceUtilityOskUpdate(1);
	    	break;
	    
			case PSP_UTILITY_DIALOG_QUIT:
	    		sceUtilityOskShutdownStart();
	    		done = 1;
	    	break;
	    
			case PSP_UTILITY_DIALOG_NONE:
	    	return;
		}
		
		int i, j;		
		for(i = 0; data.outtext[i]; i++)
			if (data.outtext[i]!='\0' && data.outtext[i]!='\n' && data.outtext[i]!='\r'){
				input[j] = data.outtext[i];
				j++;
			}
		input[j] = 0;
		
		sceDisplayWaitVblankStart();	
		flipScreen();
	}
	sceUtilityOskShutdownStart();
	
	return 0;
}

char *requestString(char *descStr, char *initialStr)
{
	
	int ok, i;
	static char str[64];
	unsigned short intext[128]  = { 0 }; // text already in the edit box on start
	unsigned short desc[128]  = { 0 };

	if (initialStr[0] != 0)
		for (i=0; i<=strlen(initialStr); i++)
			intext[i] = (unsigned short)initialStr[i];

	if (descStr[0] != 0)
		for (i=0; i<=strlen(descStr); i++)
			desc[i] = (unsigned short)descStr[i];

	ok = getOskText(str, intext, desc);

	if (ok)
		return str;

	return 1;
}
