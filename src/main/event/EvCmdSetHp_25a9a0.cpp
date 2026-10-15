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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void v59(s32 a);
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
