#include "types.h"
void TextColorApplyEffectMaybe_26da30(u8*p,s32 type,s64 value){switch((u8)type){
case 1:p[0]>>=1;p[1]>>=1;p[2]>>=1;break;
case 2:p[3]=((s16)value*255)/128;break;
case 3:p[0]=0;p[1]=0;p[2]=0;p[3]=((s16)value<<6)/128;break;
case 4:p[3]=0;break;
}}
