// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		processor.h
//		Purpose:	Processor Emulation (header)
//		Created:	24th August 2019
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _SYS_PROCESSOR_H
#define _SYS_PROCESSOR_H

typedef unsigned int   LONG32; 														// 32 bit types
typedef unsigned short WORD16;														// 8 and 16 bit types.
typedef unsigned char  BYTE8;

#define RAMSIZE	(0x80000)															// RAM

#define DEFAULT_BUS_VALUE (0xFF)													// What's on the bus if it's not memory.

void CPUReset(void);																// CPU methods
void CPUEndRun(void);
LONG32 CPU18016GetPC(void);
BYTE8 CPUExecuteInstruction(void);													// Execute one instruction (multi phases)

void HWIReset(void);																// Reset hardware.
void HWIEndFrame(void);																// End of frame function

typedef struct _CPUStatus {
	WORD16 d;
	WORD16 df,ie;       
	LONG32 **regs;       
	WORD16 x,p,t;       
	LONG32 cycles;
} CPUSTATUS;

#define PCTR 	(*pP)

CPUSTATUS *CPUGetStatus(void);														// Access CPU State
void CPULoadBinary(char *fileName);													// Load Binary in.
BYTE8 CPURead(LONG32 address);														// Access RAM
BYTE8 CPUExecute(LONG32 break1,LONG32 break2);										// Run to break point(s)
LONG32 CPUGetStepOverBreakpoint(void);												// Get step over breakpoint
int CPUKeyHandler(int key,int inRunMode);

#endif