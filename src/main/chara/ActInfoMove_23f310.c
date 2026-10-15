#include "types.h"
extern s32 ScriptArgGetStr_23fba0(s32);extern f32 ScriptArgGetFloat_23fbc0(s32);extern s32 LookupNameValueNoCase_1cab50(s32,void*,s32);extern f32*ActCfgTableFindMoveById_223080(void*,s32);extern u8 D_0044C6A0[],D_004BCE20[];
s32 ActInfoMove_23f310(s32 a,s32 n){f32*p;if(n!=4)return 0;p=ActCfgTableFindMoveById_223080(D_004BCE20,LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(a),D_0044C6A0,0));if(!p)return 1;p[1]=ScriptArgGetFloat_23fbc0(a+8);p[2]=ScriptArgGetFloat_23fbc0(a+16);p[3]=ScriptArgGetFloat_23fbc0(a+24);return 1;}
