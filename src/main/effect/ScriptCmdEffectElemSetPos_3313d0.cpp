#include "types.h"

#undef NULL
#define NULL 0
extern "C" {

void ScriptSlotsToVec4_334810(void *, s32);
s32 ScriptSlotGetInt_3348b0(s32);
void sceVu0CopyVector(s32, void *);

class VC_0 {
public:
    u8 pad[0x190];
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
    virtual s32 f();
};
typedef struct Obj4826E0 {
    u8 pad[0x190];
} Obj4826E0;
extern Obj4826E0 *D_004826E0;

s32 ScriptCmdEffectElemSetPos_3313d0(s64 *arg0, s32 arg1) {
    u8 sp50[16];
    s32 temp_16;
    s32 temp_2;
    s32 var_18;
    s32 var_19;
    s32 t;
    if ((arg1 != 4) & (arg1 != 5)) {
        return 0;
    }
    var_18 = ScriptSlotGetInt_3348b0((s32)arg0++);
    ScriptSlotsToVec4_334810(&sp50, (s32)arg0);
    t = (s32)arg0 + 0x18;
    var_19 = 1;
    if (arg1 == 5) {
        var_19 = ScriptSlotGetInt_3348b0(t);
    }
    temp_2 = ((VC_0 *)D_004826E0)->f();
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = var_19 + var_18;
    while (var_18 < temp_16) {
        sceVu0CopyVector(temp_2 + (var_18 * 0xC0) + 0xA0, &sp50);
        var_18 += 1;
    }
    return 1;
}

}
