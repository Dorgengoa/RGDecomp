/* ScriptCmdEffectElemSetSize_3314c0 -- shape-identical to merged ScriptCmdEffectElemSetScaleAccel_330560 (63 instructions); the donor's
   source with the symbol renamed, 0 call target(s) and 2 immediate(s) substituted:
     imm 84 -> 56
     imm 88 -> 60
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* lane N4 family: ScriptCmdEffectElemSetSize_3314c0 / ScriptCmdEffectElemSetScaleVel_330660 (252 B each).
   C++: the dispatch is `jalr $25` through a vptr at 0x190, slot 0x60,
   i.e. the 23rd declared virtual (0x60 = 8 + 4*22). */

typedef struct { s32 a; s32 b; } Arg;

class VE {
public:
    u8 pad000[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v22() { return VCM0(void *, 0x60); }
};

extern "C" VE *D_004826E0;

extern "C" s32 ScriptSlotGetInt_3348b0(Arg *);
extern "C" f32 ScriptSlotGetFloat_334890(Arg *);

extern "C" s32 ScriptCmdEffectElemSetSize_3314c0(Arg *p, s32 kind)
{
    s32 n;
    s32 i;
    f32 v1;
    f32 v2;
    void *r;

    if (kind != 3 && kind != 4) {
        return 0;
    }
    i = ScriptSlotGetInt_3348b0(p++);
    v1 = ScriptSlotGetFloat_334890(p++);
    v2 = ScriptSlotGetFloat_334890(p++);
    n = 1;
    if (kind == 4) {
        n = ScriptSlotGetInt_3348b0(p);
    }
    r = D_004826E0->v22();
    if (r == 0) {
        return 1;
    }
    {
        s32 lim = n + i;
        for (; i < lim; i++) {
            *(f32 *)((u8 *)r + i * 0xC0 + 0x38) = v1;
            *(f32 *)((u8 *)r + i * 0xC0 + 0x3C) = v2;
        }
    }
    return 1;
}
