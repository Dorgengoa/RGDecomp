#include "types.h"
extern void MemStackClear_14dff0(void *);
extern void *MemStackAllocAligned64_14da10(s32,s32);
extern void MemStackHeapInit_14dee0(void *,void *,u32);
extern u32 strlen(const char *);
extern char *strcpy(char *,const char *);
extern void MemStackHeapReinit_14de90(void *);
extern void *memset(void *,s32,u32);
extern void EffTableInit_1a10f0(void *,void *);
extern void MemStackHeapAlloc_14db10(void *,s32,s32,s32);
extern void *GetDamagePopupList_2d9020(void);
extern void DamagePopupListInit_2d3180(void *,void *);
extern void MemStackReturnToOwnerMaybe_14dad0(void *);
extern void EffectEntriesBindHeap_2dfef0(void *,void *);
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
