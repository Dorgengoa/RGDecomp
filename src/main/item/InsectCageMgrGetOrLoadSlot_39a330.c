#include "types.h"

struct Obj {
    u8 pad0[0x90];
    s32 unk90;
};

extern void Sprintf_1343b8(void *, void *, s32);
extern s32 InsectCageMgrIsEnabled_39b190(void);
extern s32 InsectCageSlotGetId_39b460(void *);
extern void InsectCageSlotRequestLoad_39ba30(void *, s32, void *, s32, s32);
extern const u8 D_004643B0;

void *InsectCageMgrGetOrLoadSlot_39a330(struct Obj *arg0, s32 arg1)
{
    u8 sp50[0x40];
    u8 *var_19;
    u8 *var_19_2;
    s32 var_18;
    s32 var_18_2;

    if (InsectCageMgrIsEnabled_39b190() == 0) {
        return NULL;
    }
    var_19 = (u8 *) arg0;
    var_18 = 0;
    while (var_18 < 3) {
        if (arg1 == InsectCageSlotGetId_39b460(var_19)) {
            return var_19;
        }
        var_18 += 1;
        var_19 += 0x30;
    }
    var_19_2 = (u8 *) arg0;
    var_18_2 = 0;
    while (var_18_2 < 3) {
        if (InsectCageSlotGetId_39b460(var_19_2) < 0) {
            Sprintf_1343b8(sp50, (void *) &D_004643B0, arg1 + 1);
            InsectCageSlotRequestLoad_39ba30(var_19_2, arg1, sp50, var_18_2 + 0x29F, arg0->unk90);
            return var_19_2;
        }
        var_18_2 += 1;
        var_19_2 += 0x30;
    }
    return NULL;
}
