/* rgp:protos */
#define RGP_SELF_CharaCmdAutoLockon_22b450 1
#define RGP_SELF_equal 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"
/*rgp*//*rgp*//*rgp*//*rgp*//*rgp*//*rgp*/
static inline s32 equal(s32 l,s32 r){return l==r;}
s32 CharaCmdAutoLockon_22b450(s32*p,u8*arg,s32 mode){u8 obj[0x30] __attribute__((aligned(16)));s32 a,b;void*ctx;
 if(mode!=2)return 0;
 ctx=*(void**)((u8*)GetGameData_1fede0()+0x18);
 if(!equal(*p,*(s16*)((u8*)ctx+0x18e)))return 1;
 TargetRefCtor_2e71f0(obj);a=ScriptArgGetInt_302d70(arg);b=ScriptArgGetInt_302d70(arg+5);TargetRefSetAttachPoint_2e65f0(obj,a,130,b);
 if(!TargetRefResolve_2e5ed0(obj,0))return 1;TargetMngSetTarget_313ad0(obj);return 1;}
