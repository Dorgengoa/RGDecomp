/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (85w vs retail 81w, ours LONGER). Fixed a VT40*** vs VT40** arity/deref bug that blocked compilation. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT40 {
    u8 pad[0x40];
    s32 (*unk40)(void *);
    s32 (*unk48)(void *);
} VT40;

s32 CharaSysGetEncounterIdMaybe_3a36d0(void *);
s32 CharaSysGetEncounterEntryIdMaybe_3a36f0(void *);
void ActionPacketClear_3e3e90(...);
extern u8 *D_00483990;

class VC_0 {
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
    virtual s32 f();
};
class VC_1 {
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
    virtual s32 f();
};
void *ActionPacketInitBattleGuard_3e3290(u8 *arg0, s32 arg1, s32 arg2, VT40 **arg3, s32 arg4) {
    s32 temp_19;
    s32 temp_30;
    s32 var_20;
    s32 var_21;
    u8 *temp_2;
    u8 *temp_4;

    ActionPacketClear_3e3e90();
    if (D_00483990 == NULL) {
        return NULL;
    }
    temp_4 = *(u8 **)(D_00483990 + 0x20);
    temp_2 = *(u8 **)(temp_4 + 0x238);
    if (temp_2 != NULL) {
        var_20 = *(s16 *)(temp_2 + 0xC);
    } else {
        var_20 = -1;
    }
    temp_30 = CharaSysGetEncounterEntryIdMaybe_3a36f0(temp_4);
    temp_19 = CharaSysGetEncounterIdMaybe_3a36d0(*(u8 **)(D_00483990 + 0x20));
    *(s8 *)(arg0 + 2) = 6;
    var_21 = -1;
    *(u16 *)(arg0 + 0) = 1;
    if (arg3 != NULL) {
        if (((VC_0 *)(arg3))->f() != 0) {
            var_21 = 0x22;
        } else {
            if (((VC_1 *)(arg3))->f() != 0) {
                var_21 = 0x21;
            }
        }
    }
    if (var_21 < 0) {
        return NULL;
    }
    *(s8 *)(arg0 + 3) = var_21;
    *(s8 *)(arg0 + 4) = 0x36;
    *(u16 *)(arg0 + 0) = 3;
    *(s32 *)(arg0 + 0xC) = arg1;
    *(s16 *)(arg0 + 0x1C) = var_20;
    *(s16 *)(arg0 + 0x1E) = temp_30;
    *(s16 *)(arg0 + 0x20) = temp_19;
    *(s32 *)(arg0 + 0x10) = arg2;
    *(VT40 ***)(arg0 + 0x14) = arg3;
    *(s32 *)(arg0 + 0x18) = arg4;
    return arg0;
}

}
