/* rgp:protos */
#define RGP_SELF_EffectMgrHeapInit_2e3170 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
extern u32 strlen(const char *);
extern char *strcpy(char *,const char *);
/*rgp*/
extern void *memset(void *,s32,u32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_004617B8[];
void EffectMgrHeapInit_2e3170(u8 *o,s32 n) {
 struct {void *a,*b;s32 c,d;} s;
 MemStackClear_14dff0(o);MemStackHeapInit_14dee0(o,MemStackAllocAligned64_14da10(n,0xC800),0xC800);
 if(strlen(D_004617B8)<16)strcpy((char *)o,D_004617B8);
 MemStackHeapReinit_14de90(o);memset(&s,0,16);
 s.c=0x2AB;s.a=o;s.d=0x30;s.b=o;
 EffTableInit_1a10f0(o+0x58,&s);MemStackHeapAlloc_14db10(o,1,0,0x40);
 DamagePopupListInit_2d3180(GetDamagePopupList_2d9020(),o);MemStackReturnToOwnerMaybe_14dad0(o);EffectEntriesBindHeap_2dfef0(o+0x1674,o);
 *(s16 *)(o+0x4078)=1;*(s32 *)(o+0x407C)=0;
}
