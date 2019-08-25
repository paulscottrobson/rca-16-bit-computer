case 0x00: // *** $00 idl ***
	(*pP)--;break;
case 0x10: // *** $10 inc r0 ***
	R0++;break;
case 0x11: // *** $11 inc r1 ***
	R1++;break;
case 0x12: // *** $12 inc r2 ***
	R2++;break;
case 0x13: // *** $13 inc r3 ***
	R3++;break;
case 0x14: // *** $14 inc r4 ***
	R4++;break;
case 0x15: // *** $15 inc r5 ***
	R5++;break;
case 0x16: // *** $16 inc r6 ***
	R6++;break;
case 0x17: // *** $17 inc r7 ***
	R7++;break;
case 0x18: // *** $18 inc r8 ***
	R8++;break;
case 0x19: // *** $19 inc r9 ***
	R9++;break;
case 0x1a: // *** $1a inc ra ***
	RA++;break;
case 0x1b: // *** $1b inc rb ***
	RB++;break;
case 0x1c: // *** $1c inc rc ***
	RC++;break;
case 0x1d: // *** $1d inc rd ***
	RD++;break;
case 0x1e: // *** $1e inc re ***
	RE++;break;
case 0x1f: // *** $1f inc rf ***
	RF++;break;
case 0x20: // *** $20 dec r0 ***
	R0--;break;
case 0x21: // *** $21 dec r1 ***
	R1--;break;
case 0x22: // *** $22 dec r2 ***
	R2--;break;
case 0x23: // *** $23 dec r3 ***
	R3--;break;
case 0x24: // *** $24 dec r4 ***
	R4--;break;
case 0x25: // *** $25 dec r5 ***
	R5--;break;
case 0x26: // *** $26 dec r6 ***
	R6--;break;
case 0x27: // *** $27 dec r7 ***
	R7--;break;
case 0x28: // *** $28 dec r8 ***
	R8--;break;
case 0x29: // *** $29 dec r9 ***
	R9--;break;
case 0x2a: // *** $2a dec ra ***
	RA--;break;
case 0x2b: // *** $2b dec rb ***
	RB--;break;
case 0x2c: // *** $2c dec rc ***
	RC--;break;
case 0x2d: // *** $2d dec rd ***
	RD--;break;
case 0x2e: // *** $2e dec re ***
	RE--;break;
case 0x2f: // *** $2f dec rf ***
	RF--;break;
case 0x30: // *** $30 br # ***
	BRANCH(1);break;
case 0x32: // *** $32 bz # ***
	BRANCH(D == 0);break;
case 0x33: // *** $33 bdf # ***
	BRANCH(DF != 0);break;
case 0x34: // *** $34 b1 # ***
	BRANCH(EFLAG1());break;
case 0x35: // *** $35 b2 # ***
	BRANCH(EFLAG2());break;
case 0x36: // *** $36 b3 # ***
	BRANCH(EFLAG3());break;
case 0x37: // *** $37 b4 # ***
	BRANCH(EFLAG4());break;
case 0x38: // *** $38 skp ***
	BRANCH(0);break;
case 0x3a: // *** $3a bnz # ***
	BRANCH(D != 0);break;
case 0x3b: // *** $3b bnf # ***
	BRANCH(DF == 0);break;
case 0x3c: // *** $3c bn1 # ***
	BRANCH(EFLAG1() == 0);break;
case 0x3d: // *** $3d bn2 # ***
	BRANCH(EFLAG2() == 0);break;
case 0x3e: // *** $3e bn3 # ***
	BRANCH(EFLAG3() == 0);break;
case 0x3f: // *** $3f bn4 # ***
	BRANCH(EFLAG4() == 0);break;
case 0x40: // *** $40 lda r0 ***
	MA = R0;R0 += 2;READ16();D = MB;break;
case 0x41: // *** $41 lda r1 ***
	MA = R1;R1 += 2;READ16();D = MB;break;
case 0x42: // *** $42 lda r2 ***
	MA = R2;R2 += 2;READ16();D = MB;break;
case 0x43: // *** $43 lda r3 ***
	MA = R3;R3 += 2;READ16();D = MB;break;
case 0x44: // *** $44 lda r4 ***
	MA = R4;R4 += 2;READ16();D = MB;break;
case 0x45: // *** $45 lda r5 ***
	MA = R5;R5 += 2;READ16();D = MB;break;
case 0x46: // *** $46 lda r6 ***
	MA = R6;R6 += 2;READ16();D = MB;break;
case 0x47: // *** $47 lda r7 ***
	MA = R7;R7 += 2;READ16();D = MB;break;
case 0x48: // *** $48 lda r8 ***
	MA = R8;R8 += 2;READ16();D = MB;break;
case 0x49: // *** $49 lda r9 ***
	MA = R9;R9 += 2;READ16();D = MB;break;
case 0x4a: // *** $4a lda ra ***
	MA = RA;RA += 2;READ16();D = MB;break;
case 0x4b: // *** $4b lda rb ***
	MA = RB;RB += 2;READ16();D = MB;break;
case 0x4c: // *** $4c lda rc ***
	MA = RC;RC += 2;READ16();D = MB;break;
case 0x4d: // *** $4d lda rd ***
	MA = RD;RD += 2;READ16();D = MB;break;
case 0x4e: // *** $4e lda re ***
	MA = RE;RE += 2;READ16();D = MB;break;
case 0x4f: // *** $4f lda rf ***
	MA = RF;RF += 2;READ16();D = MB;break;
case 0x50: // *** $50 sta r0 ***
	MA = R0;MB = D;WRITE16();break;
case 0x51: // *** $51 sta r1 ***
	MA = R1;MB = D;WRITE16();break;
case 0x52: // *** $52 sta r2 ***
	MA = R2;MB = D;WRITE16();break;
case 0x53: // *** $53 sta r3 ***
	MA = R3;MB = D;WRITE16();break;
case 0x54: // *** $54 sta r4 ***
	MA = R4;MB = D;WRITE16();break;
case 0x55: // *** $55 sta r5 ***
	MA = R5;MB = D;WRITE16();break;
case 0x56: // *** $56 sta r6 ***
	MA = R6;MB = D;WRITE16();break;
case 0x57: // *** $57 sta r7 ***
	MA = R7;MB = D;WRITE16();break;
case 0x58: // *** $58 sta r8 ***
	MA = R8;MB = D;WRITE16();break;
case 0x59: // *** $59 sta r9 ***
	MA = R9;MB = D;WRITE16();break;
case 0x5a: // *** $5a sta ra ***
	MA = RA;MB = D;WRITE16();break;
case 0x5b: // *** $5b sta rb ***
	MA = RB;MB = D;WRITE16();break;
case 0x5c: // *** $5c sta rc ***
	MA = RC;MB = D;WRITE16();break;
case 0x5d: // *** $5d sta rd ***
	MA = RD;MB = D;WRITE16();break;
case 0x5e: // *** $5e sta re ***
	MA = RE;MB = D;WRITE16();break;
case 0x5f: // *** $5f sta rf ***
	MA = RF;MB = D;WRITE16();break;
case 0x61: // *** $61 out 1 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT1(MB);break;
case 0x62: // *** $62 out 2 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT2(MB);break;
case 0x63: // *** $63 out 3 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT3(MB);break;
case 0x64: // *** $64 out 4 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT4(MB);break;
case 0x65: // *** $65 out 5 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT5(MB);break;
case 0x66: // *** $66 out 6 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT6(MB);break;
case 0x67: // *** $67 out 7 ***
	MA = *pX;(*pX) += 2;READ16();OUTPUT7(MB);break;
case 0x69: // *** $69 inp 1 ***
	MA = *pX;MB = INPUT1();WRITE16();break;
case 0x6a: // *** $6a inp 2 ***
	MA = *pX;MB = INPUT2();WRITE16();break;
case 0x6b: // *** $6b inp 3 ***
	MA = *pX;MB = INPUT3();WRITE16();break;
case 0x6c: // *** $6c inp 4 ***
	MA = *pX;MB = INPUT4();WRITE16();break;
case 0x6d: // *** $6d inp 5 ***
	MA = *pX;MB = INPUT5();WRITE16();break;
case 0x6e: // *** $6e inp 6 ***
	MA = *pX;MB = INPUT6();WRITE16();break;
case 0x6f: // *** $6f inp 7 ***
	MA = *pX;MB = INPUT7();WRITE16();break;
case 0x70: // *** $70 ret ***
	Return18016();IE = 1;break;
case 0x71: // *** $71 dis ***
	Return18016();IE = 0;break;
case 0x78: // *** $78 sav ***
	MA = *pX;MB = T;WRITE16();break;
case 0x80: // *** $80 glo r0 ***
	D = R0 & 0xFFFF;break;
case 0x81: // *** $81 glo r1 ***
	D = R1 & 0xFFFF;break;
case 0x82: // *** $82 glo r2 ***
	D = R2 & 0xFFFF;break;
case 0x83: // *** $83 glo r3 ***
	D = R3 & 0xFFFF;break;
case 0x84: // *** $84 glo r4 ***
	D = R4 & 0xFFFF;break;
case 0x85: // *** $85 glo r5 ***
	D = R5 & 0xFFFF;break;
case 0x86: // *** $86 glo r6 ***
	D = R6 & 0xFFFF;break;
case 0x87: // *** $87 glo r7 ***
	D = R7 & 0xFFFF;break;
case 0x88: // *** $88 glo r8 ***
	D = R8 & 0xFFFF;break;
case 0x89: // *** $89 glo r9 ***
	D = R9 & 0xFFFF;break;
case 0x8a: // *** $8a glo ra ***
	D = RA & 0xFFFF;break;
case 0x8b: // *** $8b glo rb ***
	D = RB & 0xFFFF;break;
case 0x8c: // *** $8c glo rc ***
	D = RC & 0xFFFF;break;
case 0x8d: // *** $8d glo rd ***
	D = RD & 0xFFFF;break;
case 0x8e: // *** $8e glo re ***
	D = RE & 0xFFFF;break;
case 0x8f: // *** $8f glo rf ***
	D = RF & 0xFFFF;break;
case 0x90: // *** $90 ghi r0 ***
	D = (R0 >> 16);break;
case 0x91: // *** $91 ghi r1 ***
	D = (R1 >> 16);break;
case 0x92: // *** $92 ghi r2 ***
	D = (R2 >> 16);break;
case 0x93: // *** $93 ghi r3 ***
	D = (R3 >> 16);break;
case 0x94: // *** $94 ghi r4 ***
	D = (R4 >> 16);break;
case 0x95: // *** $95 ghi r5 ***
	D = (R5 >> 16);break;
case 0x96: // *** $96 ghi r6 ***
	D = (R6 >> 16);break;
case 0x97: // *** $97 ghi r7 ***
	D = (R7 >> 16);break;
case 0x98: // *** $98 ghi r8 ***
	D = (R8 >> 16);break;
case 0x99: // *** $99 ghi r9 ***
	D = (R9 >> 16);break;
case 0x9a: // *** $9a ghi ra ***
	D = (RA >> 16);break;
case 0x9b: // *** $9b ghi rb ***
	D = (RB >> 16);break;
case 0x9c: // *** $9c ghi rc ***
	D = (RC >> 16);break;
case 0x9d: // *** $9d ghi rd ***
	D = (RD >> 16);break;
case 0x9e: // *** $9e ghi re ***
	D = (RE >> 16);break;
case 0x9f: // *** $9f ghi rf ***
	D = (RF >> 16);break;
case 0xa0: // *** $a0 plo r0 ***
	R0 = (R0 & 0xFFFF0000) | D;break;
case 0xa1: // *** $a1 plo r1 ***
	R1 = (R1 & 0xFFFF0000) | D;break;
case 0xa2: // *** $a2 plo r2 ***
	R2 = (R2 & 0xFFFF0000) | D;break;
case 0xa3: // *** $a3 plo r3 ***
	R3 = (R3 & 0xFFFF0000) | D;break;
case 0xa4: // *** $a4 plo r4 ***
	R4 = (R4 & 0xFFFF0000) | D;break;
case 0xa5: // *** $a5 plo r5 ***
	R5 = (R5 & 0xFFFF0000) | D;break;
case 0xa6: // *** $a6 plo r6 ***
	R6 = (R6 & 0xFFFF0000) | D;break;
case 0xa7: // *** $a7 plo r7 ***
	R7 = (R7 & 0xFFFF0000) | D;break;
case 0xa8: // *** $a8 plo r8 ***
	R8 = (R8 & 0xFFFF0000) | D;break;
case 0xa9: // *** $a9 plo r9 ***
	R9 = (R9 & 0xFFFF0000) | D;break;
case 0xaa: // *** $aa plo ra ***
	RA = (RA & 0xFFFF0000) | D;break;
case 0xab: // *** $ab plo rb ***
	RB = (RB & 0xFFFF0000) | D;break;
case 0xac: // *** $ac plo rc ***
	RC = (RC & 0xFFFF0000) | D;break;
case 0xad: // *** $ad plo rd ***
	RD = (RD & 0xFFFF0000) | D;break;
case 0xae: // *** $ae plo re ***
	RE = (RE & 0xFFFF0000) | D;break;
case 0xaf: // *** $af plo rf ***
	RF = (RF & 0xFFFF0000) | D;break;
case 0xb0: // *** $b0 phi r0 ***
	R0 = (R0 & 0x0000FFFF) | (D << 16);break;
case 0xb1: // *** $b1 phi r1 ***
	R1 = (R1 & 0x0000FFFF) | (D << 16);break;
case 0xb2: // *** $b2 phi r2 ***
	R2 = (R2 & 0x0000FFFF) | (D << 16);break;
case 0xb3: // *** $b3 phi r3 ***
	R3 = (R3 & 0x0000FFFF) | (D << 16);break;
case 0xb4: // *** $b4 phi r4 ***
	R4 = (R4 & 0x0000FFFF) | (D << 16);break;
case 0xb5: // *** $b5 phi r5 ***
	R5 = (R5 & 0x0000FFFF) | (D << 16);break;
case 0xb6: // *** $b6 phi r6 ***
	R6 = (R6 & 0x0000FFFF) | (D << 16);break;
case 0xb7: // *** $b7 phi r7 ***
	R7 = (R7 & 0x0000FFFF) | (D << 16);break;
case 0xb8: // *** $b8 phi r8 ***
	R8 = (R8 & 0x0000FFFF) | (D << 16);break;
case 0xb9: // *** $b9 phi r9 ***
	R9 = (R9 & 0x0000FFFF) | (D << 16);break;
case 0xba: // *** $ba phi ra ***
	RA = (RA & 0x0000FFFF) | (D << 16);break;
case 0xbb: // *** $bb phi rb ***
	RB = (RB & 0x0000FFFF) | (D << 16);break;
case 0xbc: // *** $bc phi rc ***
	RC = (RC & 0x0000FFFF) | (D << 16);break;
case 0xbd: // *** $bd phi rd ***
	RD = (RD & 0x0000FFFF) | (D << 16);break;
case 0xbe: // *** $be phi re ***
	RE = (RE & 0x0000FFFF) | (D << 16);break;
case 0xbf: // *** $bf phi rf ***
	RF = (RF & 0x0000FFFF) | (D << 16);break;
case 0xd0: // *** $d0 sep r0 ***
	SETP(0x0);break;
case 0xd1: // *** $d1 sep r1 ***
	SETP(0x1);break;
case 0xd2: // *** $d2 sep r2 ***
	SETP(0x2);break;
case 0xd3: // *** $d3 sep r3 ***
	SETP(0x3);break;
case 0xd4: // *** $d4 sep r4 ***
	SETP(0x4);break;
case 0xd5: // *** $d5 sep r5 ***
	SETP(0x5);break;
case 0xd6: // *** $d6 sep r6 ***
	SETP(0x6);break;
case 0xd7: // *** $d7 sep r7 ***
	SETP(0x7);break;
case 0xd8: // *** $d8 sep r8 ***
	SETP(0x8);break;
case 0xd9: // *** $d9 sep r9 ***
	SETP(0x9);break;
case 0xda: // *** $da sep ra ***
	SETP(0xA);break;
case 0xdb: // *** $db sep rb ***
	SETP(0xB);break;
case 0xdc: // *** $dc sep rc ***
	SETP(0xC);break;
case 0xdd: // *** $dd sep rd ***
	SETP(0xD);break;
case 0xde: // *** $de sep re ***
	SETP(0xE);break;
case 0xdf: // *** $df sep rf ***
	SETP(0xF);break;
case 0xe0: // *** $e0 sex r0 ***
	SETX(0x0);break;
case 0xe1: // *** $e1 sex r1 ***
	SETX(0x1);break;
case 0xe2: // *** $e2 sex r2 ***
	SETX(0x2);break;
case 0xe3: // *** $e3 sex r3 ***
	SETX(0x3);break;
case 0xe4: // *** $e4 sex r4 ***
	SETX(0x4);break;
case 0xe5: // *** $e5 sex r5 ***
	SETX(0x5);break;
case 0xe6: // *** $e6 sex r6 ***
	SETX(0x6);break;
case 0xe7: // *** $e7 sex r7 ***
	SETX(0x7);break;
case 0xe8: // *** $e8 sex r8 ***
	SETX(0x8);break;
case 0xe9: // *** $e9 sex r9 ***
	SETX(0x9);break;
case 0xea: // *** $ea sex ra ***
	SETX(0xA);break;
case 0xeb: // *** $eb sex rb ***
	SETX(0xB);break;
case 0xec: // *** $ec sex rc ***
	SETX(0xC);break;
case 0xed: // *** $ed sex rd ***
	SETX(0xD);break;
case 0xee: // *** $ee sex re ***
	SETX(0xE);break;
case 0xef: // *** $ef sex rf ***
	SETX(0xF);break;
case 0xf0: // *** $f0 ldx ***
	MA = *pX;READ16();D = MB;break;
case 0xf1: // *** $f1 or ***
	MA = *pX;READ16();D |= MB;break;
case 0xf2: // *** $f2 and ***
	MA = *pX;READ16();D &= MB;break;
case 0xf3: // *** $f3 xor ***
	MA = *pX;READ16();D ^= MB;break;
case 0xf4: // *** $f4 add ***
	MA = *pX;READ16();ADD(D,MB,0);break;
case 0xf5: // *** $f5 sd ***
	MA = *pX;READ16();ADD(D ^ 0xFFFF,MB,1);break;
case 0xf6: // *** $f6 shr ***
	DF = D & 1;D = (D >> 1);break;
case 0xf7: // *** $f7 sm ***
	MA = *pX;READ16();ADD(D,MB ^ 0xFFFF,1);break;
case 0xf8: // *** $f8 ldi # ***
	FETCH16();D = MB;break;
case 0xf9: // *** $f9 ori # ***
	FETCH16();D |= MB;break;
case 0xfa: // *** $fa ani # ***
	FETCH16();D &= MB;break;
case 0xfb: // *** $fb xri # ***
	FETCH16();D ^= MB;break;
case 0xfc: // *** $fc adi # ***
	FETCH16();ADD(D,MB,0);break;
case 0xfd: // *** $fd sdi # ***
	FETCH16();ADD(D ^ 0xFFFF,MB,1);break;
case 0xff: // *** $ff smi # ***
	FETCH16();ADD(D,MB ^ 0xFFFF,1);break;
