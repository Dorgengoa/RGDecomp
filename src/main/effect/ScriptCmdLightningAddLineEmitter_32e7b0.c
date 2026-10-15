#include "types.h"
typedef struct {s32 a,b;} Arg;
extern void LightningMgrAddLineEmitter_2d6bd0(void*,void*,void*,s32,s32,s32,f32);
extern void ScriptSlotsToVec4_334810(void*,Arg*);
extern f32 ScriptSlotGetFloat_334890(Arg*);
extern s32 ScriptSlotGetInt_3348b0(Arg*);
extern u8 D_004E6110[];
s32 ScriptCmdLightningAddLineEmitter_32e7b0(Arg*p,s32 n){
 u8 a[16],b[16];s32 x,y,z;f32 f;
 if(n<9||n>10)return 0;
 ScriptSlotsToVec4_334810(a,p);ScriptSlotsToVec4_334810(b,p+3);p+=6;
 x=ScriptSlotGetInt_3348b0(p++);y=ScriptSlotGetInt_3348b0(p++);f=ScriptSlotGetFloat_334890(p++);z=0;
 if(n==10)z=ScriptSlotGetInt_3348b0(p);
 LightningMgrAddLineEmitter_2d6bd0(D_004E6110,a,b,x,y,z,f);return 1;
}
