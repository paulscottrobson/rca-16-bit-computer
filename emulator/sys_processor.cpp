// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		processor.cpp
//		Purpose:	Processor Emulation.
//		Created:	17th April 2019
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include "sys_processor.h"
#include "gfx.h"

// *******************************************************************************************************************************
//															Timing
// *******************************************************************************************************************************
	
//
//		I am unreliably informed that a 65816 operates at about 32 MIPS at 8Mhz. So this emulator
//		times on that assumption.
//	
#define CYCLES_PER_SECOND	(2000000)												// 2.0 MIPS
#define FRAME_RATE			(60)													// Frame rate
#define CYCLES_PER_FRAME	(CYCLES_PER_SECOND/FRAME_RATE)							// T-States per second.

static LONG32 R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,RA,RB,RC,RD,RE,RF;
static WORD16 D;
static BYTE8  DF,IE,X,P,T;

static LONG32 MA,Cycles = 0,temp32;
static WORD16 MB;

static LONG32 *pX,*pP;
static LONG32 *regAddr[16] = { &R0,&R1,&R2,&R3,&R4,&R5,&R6,&R7,&R8,&R9,&RA,&RB,&RC,&RD,&RE,&RF };

// *******************************************************************************************************************************
//														Main Memory
// *******************************************************************************************************************************

static BYTE8 ramMemory[RAMSIZE];													// RAM memory
#define RAMMASK (RAMSIZE-1)

// *******************************************************************************************************************************
//													Memory read and write macros.
// *******************************************************************************************************************************

#define READ16() 	MB = ramMemory[MA & RAMMASK] + (ramMemory[(MA+1) & RAMMASK] << 8)
#define WRITE16() 	ramMemory[MA & RAMMASK] = MB & 0xFF;ramMemory[(MA+1) & RAMMASK] = MB >> 8

#define FETCH8() 	MA = *(pP)++;MB = ramMemory[MA & RAMMASK]
#define FETCH16() 	MA = *pP;READ16();(*pP) += 2

// *******************************************************************************************************************************
//													Port/EFLAG Definitions here
// *******************************************************************************************************************************


// *******************************************************************************************************************************
//														Support code
// *******************************************************************************************************************************

#include "generated/18016_code.h"
#include "generated/18016_ports.h"

// *******************************************************************************************************************************
//														Reset the CPU
// *******************************************************************************************************************************

void CPUReset(void) {
	Reset18016();
	Cycles = 0;	
}

// *******************************************************************************************************************************
//														Get PC
// *******************************************************************************************************************************

LONG32 CPU18016GetPC(void) {
	return *pP;
}

// *******************************************************************************************************************************
//													 Execute a single phase.
// *******************************************************************************************************************************

#include "stdio.h"

BYTE8 CPUExecuteInstruction(void) {
	Cycles++;
	FETCH8();																		// Fetch instruction
	switch(MB) {
		#include "generated/18016_switch.h"
	}
	if (Cycles < CYCLES_PER_FRAME) return 0;										// Frame in progress, return 0.
	Cycles -= CYCLES_PER_FRAME;														// Adjust cycle counter
	return FRAME_RATE;																// Return the frame rate for sync speed.
}

#ifdef INCLUDE_DEBUGGING_SUPPORT

// *******************************************************************************************************************************
//												Handle keypress
// *******************************************************************************************************************************

int CPUKeyHandler(int key,int inRunMode) {
	if (inRunMode) {
		// ramMemory[0xF8010 & RAMMASK] = GFXToASCII(key,-1);
	}	
	return key;
}

// *******************************************************************************************************************************
//												Read a byte
// *******************************************************************************************************************************

BYTE8 CPURead(LONG32 address) {
	return ramMemory[address & RAMMASK];
}

// *******************************************************************************************************************************
//										 Get the step over breakpoint value
// *******************************************************************************************************************************

LONG32 CPUGetStepOverBreakpoint(void) {
	BYTE8 opcode = CPURead(PCTR);												// Read opcode.
	if (opcode >= 0xD0 && opcode < 0xE0) return PCTR+1;							// Skip over SEP Rx
	return 0;
}

// *******************************************************************************************************************************
//										Run continuously till breakpoints / Halt.
// *******************************************************************************************************************************

BYTE8 CPUExecute(LONG32 break1,LONG32 break2) {
	BYTE8 rate = 0;
	while(1) {
		rate = CPUExecuteInstruction();												// Execute one instruction phase.
		if (rate != 0) {															// If end of frame, return rate.
			return rate;													
		}
//		if (CPURead(PCTR) == 0xEA) return 0;										// stop on NOP.
//		if (CPURead(PCTR) == 0x02) { 												// stop on COP.
//			GFXCloseOnDebug();
//		}
		if (PCTR == break1 || PCTR == break2) return 0;
	} 																				// Until hit a breakpoint or HLT.
}

// *******************************************************************************************************************************
//												Load a binary file into RAM
// *******************************************************************************************************************************

#include <stdio.h>

void CPULoadBinary(char *fileName) {
	FILE *f = fopen(fileName,"rb");
	int n = 0;
	while (!feof(f)) {
		ramMemory[n++] = fgetc(f);
	}
	CPUReset();
	fclose(f);
}

// *******************************************************************************************************************************
//													Called on Program end
// *******************************************************************************************************************************

void CPUEndRun(void) {
//	FILE *f = fopen("memory.dump","wb");
//	for (LONG32 l = 0x0000;l < 0x10000;l += 1024) {
//		fwrite(ramMemory+l,1,1024,f);
//	}
//	fclose(f);
}

// *******************************************************************************************************************************
//											Retrieve a snapshot of the processor
// *******************************************************************************************************************************

CPUSTATUS cpu;

CPUSTATUS *CPUGetStatus(void) {
	cpu.d = D;cpu.df = DF;cpu.ie = IE;
	cpu.x = X;cpu.p = P;cpu.t = T;
	cpu.regs = regAddr;
	return &cpu;
}
#endif
