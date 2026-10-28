#include "types.h"

/* PARK, C++ VIRTUAL (vptr +0, slot 0xF4 = virtual #59): the language switch is
   right -- every word of the body lines up -- but we are ONE INSTRUCTION
   SHORT. Retail reuses `$s0` for THREE values (arg0+8, temp_16, temp_16_2)
   and gets a second `daddu $16,$2,$0`; ours colours one of them elsewhere.
   Measured: `arg0 += 8` before/after the 2nd call, an s32* walker, and four
   exit shapes (early return, goto-to-join, `if (p)`) -- all 29 words.
   [[levers.d/jalr-is-cpp-virtual]]. */

class VE25A9A0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v59(s32 a) { VCM(void, (void *, s32), 0xF4, a); }
};
extern "C" {
s32 GetGameData_1fede0(void);
s32 ScriptGetInt_26a2a0(s32 arg0);
VE25A9A0 *ActorFindById_3eb870(s32 arg0, s32 arg1);
}

extern "C" s32 EvCmdSetHp_25a9a0(s64 *arg0)
{
    VE25A9A0 *temp_2;
    s32 temp_17;
    s32 temp_16_2;
    s32 temp_16;

    temp_17 = GetGameData_1fede0();
    temp_16 = ScriptGetInt_26a2a0((s32)arg0++);
    temp_16_2 = ScriptGetInt_26a2a0((s32)arg0);
    temp_2 = ActorFindById_3eb870(temp_17, temp_16);
    if (temp_2 != NULL) {
        temp_2->v59(temp_16_2);
    }
    return 1;
}
