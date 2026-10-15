#include "types.h"
#pragma divbyzerocheck on
typedef struct {u8 a[20];} E;
extern E *D_004BCE58[4]; extern s16 D_004BCE88[8]; extern u8 D_004BCE20[16];
extern s32 D_00481E90,D_00481E94,D_00481E98,D_00481E9C;
extern s32 ActInfoClsnGetPntList_230980(E*); extern s32 ActInfoClsnGetLinList_230970(E*);
extern void ActInfoClsnSetPntCount_230940(E*,s32);extern void ActInfoClsnSetLinCount_230930(E*,s32);extern void ActCfgTableSetClsnCount_223c40(void*,s32);
s32 ActInfoClsnEnd_23e8a0(s32 a,s32 b){E*p;s32 n,t;
 if(b!=0)return 0;
 if(!D_004BCE58[0]||D_004BCE88[0]>=64)return 1;
 p=D_004BCE58[0]+D_004BCE88[0];
 t=D_00481E90-ActInfoClsnGetPntList_230980(p);n=t/16;ActInfoClsnSetPntCount_230940(p,D_00481E94+n);
 n=(D_00481E98-ActInfoClsnGetLinList_230970(p))/24;ActInfoClsnSetLinCount_230930(p,D_00481E9C+n);
 ActCfgTableSetClsnCount_223c40(D_004BCE20,D_004BCE88[0]+1);return 1;}
