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
 
#include <pspkernel.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pspmoduleinfo.h>
#include <psputility.h>
#include <pspgu.h>
#include <pspgum.h>

#include "../../include/luaplayer.h"
#include "../graphics/graphics.h"
#include "msgDialog.h"

pspUtilityMsgDialogParams dialog;

static void ConfigureDialog(pspUtilityMsgDialogParams *dialog, size_t dialog_size)
{
    memset(dialog, 0, dialog_size);

    dialog->base.size = dialog_size;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,
				&dialog->base.language); // Prompt language
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,
				&dialog->base.buttonSwap); // X/O button swap

    dialog->base.graphicsThread = 0x11;
    dialog->base.accessThread = 0x13;
    dialog->base.fontThread = 0x12;
    dialog->base.soundThread = 0x10;
}

int errDone = 0;

void ShowErrorDialog(const char *message)
{
	ConfigureDialog(&dialog, sizeof(dialog));
    dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_ERROR;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_ERROR;
    dialog.errorValue = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

    strcpy(dialog.message, message);
    sceUtilityMsgDialogInitStart(&dialog);

   while(!errDone) 
	{
		guStart();
		clearScreen(0xff554433);
		sceGuFinish();
    	sceGuSync(0,0);

		switch(sceUtilityMsgDialogGetStatus()) 
		{	    
			case PSP_UTILITY_DIALOG_VISIBLE:
	    		sceUtilityMsgDialogUpdate(1);
	    	break;
	    
			case PSP_UTILITY_DIALOG_QUIT:
	    		sceUtilityMsgDialogShutdownStart();
	    		errDone = 1;
	    	break;
	    
			case PSP_UTILITY_DIALOG_NONE:
	    	return;
	    }
		sceDisplayWaitVblankStart();	
		flipScreen();
	}
	sceUtilityMsgDialogShutdownStart();
}

int dDone = 0;

void ShowMessageDialog(const char *message, unsigned int enableYesno)
{
	ConfigureDialog(&dialog, sizeof(dialog));
    dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;
	
	if(enableYesno)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS|PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;		
	
    strcpy(dialog.message, message);
    sceUtilityMsgDialogInitStart(&dialog);
           
	while(!dDone) 
	{
		guStart();
		clearScreen(0xff554433);
		sceGuFinish();
    	sceGuSync(0,0);

		switch(sceUtilityMsgDialogGetStatus()) 
		{	    
			case PSP_UTILITY_DIALOG_VISIBLE:
	    		sceUtilityMsgDialogUpdate(1);
	    	break;
	    
			case PSP_UTILITY_DIALOG_QUIT:
	    		sceUtilityMsgDialogShutdownStart();
	    		dDone = 1;
	    	break;
	    
			case PSP_UTILITY_DIALOG_NONE:
	    	return;
	    }
		sceDisplayWaitVblankStart();	
		flipScreen();
	}
	sceUtilityMsgDialogShutdownStart();
}
