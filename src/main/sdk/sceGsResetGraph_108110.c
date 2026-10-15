/* GS reset and CRT setup. State layout follows the retail halfword/word accesses. */
typedef unsigned long long u64;
typedef struct { short interlace, mode, field; unsigned short version; int active; int handler; } GsState;
extern GsState *sceGsGetGParam_1082a0(void);
extern u64 GsPutIMR(u64);
extern void DisableIntc_117080(int);
extern void RemoveIntcHandler(int,int);
extern void SetGsCrt(int,int,int);
void sceGsResetGraph_108110(short reset, short interlace, short mode, short field)
{
 GsState *p;
 switch(reset) {
 case 0:
  p=sceGsGetGParam_1082a0();
  *(volatile u64*)0x12001000=0x200;
  p->interlace=interlace;
  p->mode=mode;
  p->version=(*(volatile u64*)0x12001000 >> 16)&255;
  GsPutIMR(0xff00);
  p->field=field!=0;
  if(p->active) {
   DisableIntc_117080(2);
   RemoveIntcHandler(2,p->handler);
   p->active=0;p->handler=0;
  }
  SetGsCrt(interlace&1,mode&255,field&1);
  break;
 case 1:
  *(volatile u64*)0x12001000=0x100;
  break;
 case 5:
  p=sceGsGetGParam_1082a0();
  p->interlace=interlace;
  p->mode=mode;
  p->field=field!=0;
  p->version=(*(volatile u64*)0x12001000 >> 16)&255;
  SetGsCrt(interlace&1,mode&255,field&1);
  break;
 }
}
