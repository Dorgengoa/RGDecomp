#include "types.h"
extern u8*D_004812DC;extern s32 VariantGetInt_15f780(s64*);extern f32 VariantGetFloat_15f740(s64*);extern void VariantReadVec3_15f6c0(void*,s64*);
s32 MapCfgFuncSoundData_18a6e0(s64*s){u8*p;if(!D_004812DC)return 0;p=D_004812DC+0x60;*(s32*)p=VariantGetInt_15f780(s++);*(f32*)(p+4)=VariantGetFloat_15f740(s++);*(f32*)(p+8)=VariantGetFloat_15f740(s++);*(f32*)(p+12)=(f32)VariantGetInt_15f780(s++);*(s32*)(p+16)=VariantGetInt_15f780(s++);VariantReadVec3_15f6c0(p+32,s);VariantReadVec3_15f6c0(p+48,s+3);*(s32*)(p+60)=0x3f800000;*(s32*)(p+44)=0x3f800000;return 1;}
