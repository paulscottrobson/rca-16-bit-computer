// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_debug_18016.cpp
//		Purpose:	Debugger Code (System Dependent)
//		Created:	24th August 2019
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gfx.h"
#include "sys_processor.h"
#include "sys_debug_system.h"
#include "debugger.h"

#include "generated/18016_mnemonics.h"

#define DBGC_ADDRESS 	(0x0F0)														// Colour scheme.
#define DBGC_DATA 		(0x0FF)														// (Background is in main.c)
#define DBGC_HIGHLIGHT 	(0xFF0)

int renderCount = 0;

// *******************************************************************************************************************************
//												Reset the 8008
// *******************************************************************************************************************************

void DBGXReset(void) {
	CPUReset();
}

// *******************************************************************************************************************************
//											This renders the debug screen
// *******************************************************************************************************************************

void DBGXRender(int *address,int showDisplay) {
	int n,x;
	char buffer[32];
	GFXSetCharacterSize(44,28);

	CPUSTATUS *s = CPUGetStatus();													// Get the CPU Status

	const char *labels[] = { "P","X","RP","RX","MX","D","DF","IE","T",NULL	 };
	n = 0;
	while (labels[n] != NULL) {
		GFXString(GRID(20,n),labels[n],GRIDSIZE,DBGC_ADDRESS,-1);
	 	n++;
	}

	n = 0;x = 23;
	GFXNumber(GRID(x,n++),s->p,16,1,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),s->x,16,1,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),*(s->regs[s->p]),16,8,GRIDSIZE,DBGC_DATA,-1);		
	int rx = *(s->regs[s->x]);
	GFXNumber(GRID(x,n++),rx,16,8,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x+3,n),CPURead(rx+1),16,2,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),CPURead(rx),16,2,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),s->d,16,4,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),s->df,16,1,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),s->ie,16,1,GRIDSIZE,DBGC_DATA,-1);		
	GFXNumber(GRID(x,n++),s->t,16,2,GRIDSIZE,DBGC_DATA,-1);		

	for (n = 0;n < 16;n++) {
		sprintf(buffer,"R%X",n);
	 	GFXString(GRID(32,n),buffer,GRIDSIZE,DBGC_ADDRESS,-1);
		GFXNumber(GRID(35,n),*(s->regs[n]),16,8,GRIDSIZE,DBGC_DATA,-1);		
	}
	int pc = address[0];
	for (int y = 0;y < 18;y++) {
		int isBrk = (pc == address[3]);
	 	GFXNumber(GRID(1,y),pc >> 16,16,2,GRIDSIZE,DBGC_ADDRESS,-1);		
	 	GFXString(GRID(3,y),":",GRIDSIZE,DBGC_ADDRESS,-1);
	 	GFXNumber(GRID(4,y),pc & 0xFFFF,16,4,GRIDSIZE,DBGC_ADDRESS,-1);		
	 	char buffer[64];
	 	strcpy(buffer,(char *)_mnemonics[CPURead(pc++)]);
		GFXString(GRID(9,y),buffer,GRIDSIZE,isBrk ? DBGC_HIGHLIGHT:DBGC_DATA,-1);
	}

	for (int y = 20;y < 28;y++) {
	 	int base = address[1] + (y - 20) * 8;		
	 	int x = 1;
	 	GFXNumber(GRID(x,y),base >> 16,16,2,GRIDSIZE,DBGC_ADDRESS,-1);		
	 	GFXString(GRID(x+2,y),":",GRIDSIZE,DBGC_ADDRESS,-1);
	 	GFXNumber(GRID(x+3,y),base & 0xFFFF,16,4,GRIDSIZE,DBGC_ADDRESS,-1);		
	 	for (int n = 0;n < 8;n++) {
	 		int b = CPURead(base+n);
	 		GFXNumber(GRID(x+9+n*3,y),b,16,2,GRIDSIZE,DBGC_DATA,-1);		
	 		b = ((b & 0x7F) < 32) ? '.' : (b & 0x7F);
	 		GFXCharacter(GRID(x+34+n,y),b,GRIDSIZE,DBGC_DATA,-1);
	 	}
	}

	// int xs = 64;
	// int ys = 32;
	// renderCount++;
	// if (showDisplay) {
	// 	int size = 2;
	// 	int x1 = WIN_WIDTH/2-xs*size*8/2;
	// 	int y1 = WIN_HEIGHT/2-ys*size*8/2;
	// 	SDL_Rect r;
	// 	int b = 16;
	// 	r.x = x1-b;r.y = y1-b;r.w = xs*size*8+b*2;r.h=ys*size*8+b*2;
	// 	GFXRectangle(&r,0xFFFF);
	// 	b = b - 4;
	// 	r.x = x1-b;r.y = y1-b;r.w = xs*size*8+b*2;r.h=ys*size*8+b*2;
	// 	GFXRectangle(&r,0);
	// 	for (int x = 0;x < xs;x++) 
	// 	{
	// 		for (int y = 0;y < ys;y++)
	// 		{
	// 			int ch = CPURead(0xF0000+x+y*xs);
	// 			int rvs = (ch & 0x80) ? 0xFF:0x00;
	// 			ch = ch & 0x7F;
	// 			int xc = x1 + x * 8 * size;
	// 			int yc = y1 + y * 8 * size;
	// 			//if (renderCount & 32) rvs = 0;
	// 			SDL_Rect rc;
	// 			int cp = ch * 8;
	// 			rc.w = rc.h = size;																// Width and Height of pixel.
	// 			for (int x = 0;x < 8;x++) {														// 5 Across
	// 				rc.x = xc + x * size;
	// 				for (int y = 0;y < 8;y++) {													// 7 Down
	// 					int f = font[cp+y] ^ rvs;
	// 					rc.y = yc + y * size;
	// 					if (f & (0x01 << x)) {		
	// 						GFXRectangle(&rc,rvs ? 0x0FF:0x0F0);			
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
}	
