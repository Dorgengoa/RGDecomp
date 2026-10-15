#include "eekernel.h"
typedef unsigned long u64 __attribute__((mode(DI)));
register int gp asm("$28");
typedef struct { unsigned short t, t2; int id; int handler, arg, gp; } A;
extern int D_80076700;
extern u64 D_80076708;
extern A D_80076740[];
extern void func_076460(unsigned short);
extern void func_076680(int, int, int, unsigned short, int);
void KernelAlarmIntrHandler_447588(void)
{
 int i, saved;
 A a;
 for(i=0;i<D_80076700;i++) {
  if(D_80076740[0].t != D_80076740[i].t) {
   func_076460(D_80076740[i].t);
   break;
  }
 }
 do {
  a=D_80076740[0];
  D_80076700--;
  for(i=0;i<D_80076700;i++) D_80076740[i]=D_80076740[i+1];
  {int newgp=a.gp; GetGlobalPointer(saved); if(newgp) newgp=newgp; gp=newgp; if(gp) {gp=gp ^ i ^ i;}}
  D_80076708 &= ~((u64)1 << a.id);
  func_076680(0x82000,a.handler,a.id,a.t,a.arg);
  gp=saved; if(gp) { gp=gp ^ saved ^ saved; } if(a.t) a.t=a.t;
 } while(D_80076700>0 && a.t==D_80076740[0].t);
 if(D_80076700>0) func_076460(D_80076740[0].t);
 else *(volatile int*)0xB0001810=0x483;
 ExitHandler();
}
