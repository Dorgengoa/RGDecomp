#include "types.h"
#include "vec.h"
struct Obj {u8 pad[0x190];VC_VPTR_MEMBER;u8 * get() { return VCM0(u8 *, 0x18); }};
extern "C" {
extern void EffectInstanceSetRot_2dd560(Obj *,f32 *);
extern f32 ScriptSlotGetFloat_334890(s64 *);
extern s32 ScriptSlotGetInt_3348b0(s64 *);
extern Obj *D_004826E0;
s32 ScriptCmdEffectSetRotY_332140(s64 *arg0,s32 arg1) {
 union {f32 f[4];u128 q;} sp;f32 f;u8 *p;u32 n;u8 *t;
 if(arg1!=2)return 0;
 ScriptSlotGetInt_3348b0(arg0++);
 f=ScriptSlotGetFloat_334890(arg0);
 p=(u8 *)&sp;n=16;
 if(p) {do {*p=0;n--;p++;}while(n);}
 if(!D_004826E0)return 0;
 t=D_004826E0->get();
 if(t)sp.q=*(u128 *)(t+0x190);
 sp.f[3]=1.0f;sp.f[1]=f;
 EffectInstanceSetRot_2dd560(D_004826E0,sp.f);
 return 1;
}
}
