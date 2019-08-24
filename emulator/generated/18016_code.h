#define SETP(n)   P = (n);pP = regAddr[n]
#define SETX(n)   X = (n);pX = regAddr[n]

 static void Reset18016(void) {
  SETP(0);
  R0 = 0;
  IE = 1;
  DF &= 1;D &= 0xFFFF;
  SETX(X & 0x0F);
 }


 static void Interrupt18016(void) {
  if (IE != 0) {
   T = (X << 4 | P);
   SETX(2);
   SETP(1);
   IE = 0;
  }
 }

#define ADD(n1,n2,n3) temp32 = (n1)+(n2)+(n3);D = temp32 & 0xFFFF;DF = (temp32 >> 16) & 1
#define BRANCH(t)   FETCH16();if (t) { *pP = ((*pP) & 0xFFFF0000) | MB; }
 static void Return18016() {
  MA = *pX;READ16();(*pX) += 2;
  SETX(MB >> 4);
  SETP(MB & 0x0F);
 }