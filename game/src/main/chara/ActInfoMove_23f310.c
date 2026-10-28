/* rgp:protos */
#define RGP_SELF_ActInfoMove_23f310 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*//*rgp*//*rgp*//*rgp*/extern u8 D_0044C6A0[],D_004BCE20[];
s32 ActInfoMove_23f310(s32 a,s32 n){f32*p;if(n!=4)return 0;p=((f32*)ActCfgTableFindMoveById_223080(D_004BCE20,LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(a),D_0044C6A0,0)));if(!p)return 1;p[1]=ScriptArgGetFloat_23fbc0(a+8);p[2]=ScriptArgGetFloat_23fbc0(a+16);p[3]=ScriptArgGetFloat_23fbc0(a+24);return 1;}
