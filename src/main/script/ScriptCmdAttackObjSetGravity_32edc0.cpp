/* main s27m: CLOSED -- C++ virtual (vptr 0xB0, slot 23) and the GetScaledGravity_23b170() result
   NAMED before `t * temp_f20` (inline, mwcc normalises the call into rt). */
#include "types.h"

class C_32EDC0 {
public:
    u8 pad[0xB0];
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
    virtual void v23(f32);
};

extern "C" f32 GetScaledGravity_23b170(void);
extern "C" s32 GetObjRefTable_313de0(void);
extern "C" C_32EDC0 *HandleRegistryLookup_314aa0(s32, s32);
extern "C" f32 ScriptSlotGetFloat_334890(s32);
extern "C" s32 ScriptSlotGetInt_3348b0(s32);

extern "C" s32 ScriptCmdAttackObjSetGravity_32edc0(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_16;
    C_32EDC0 *temp_2;

    if (arg1 != 2) {
        return 0;
    }
    temp_16 = GetObjRefTable_313de0();
    temp_2 = HandleRegistryLookup_314aa0(temp_16, ScriptSlotGetInt_3348b0(arg0));
    if (temp_2 == NULL) {
        return 1;
    }
    temp_f20 = ScriptSlotGetFloat_334890(arg0 + 8);
    temp_f21 = GetScaledGravity_23b170();
    temp_2->v23(temp_f21 * temp_f20);
    return 1;
}
