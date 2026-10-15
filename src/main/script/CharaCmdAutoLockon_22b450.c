#pragma opt_propagation off
#include "types.h"
extern void *GetGameData_1fede0(void);extern void TargetRefCtor_2e71f0(void*);extern s32 ScriptArgGetInt_302d70(void*);extern void TargetRefSetAttachPoint_2e65f0(void*,s32,s32,s32);extern s32 TargetRefResolve_2e5ed0(void*,s32);extern void TargetMngSetTarget_313ad0(void*);
static inline s32 equal(s32 l,s32 r){return l==r;}
s32 CharaCmdAutoLockon_22b450(s32*p,u8*arg,s32 mode){u8 obj[0x30];s32 a,b;void*ctx;
 if(mode!=2)return 0;
 ctx=*(void**)((u8*)GetGameData_1fede0()+0x18);
 if(!equal(*p,*(s16*)((u8*)ctx+0x18e)))return 1;
 TargetRefCtor_2e71f0(obj);a=ScriptArgGetInt_302d70(arg);b=ScriptArgGetInt_302d70(arg+5);TargetRefSetAttachPoint_2e65f0(obj,a,130,b);
 if(!TargetRefResolve_2e5ed0(obj,0))return 1;TargetMngSetTarget_313ad0(obj);return 1;}
