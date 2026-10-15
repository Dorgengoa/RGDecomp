#include "types.h"
#pragma optimize_for_size on

typedef struct SNode003D9E70 SNode003D9E70;
struct SNode003D9E70 {
    u8 pad0[0x30];
    s16 unk30;
    u8 f0 : 1;
    u8 rest : 7;
};

typedef struct {
    u8 pad0[0xE08];
    s16 unkE08;
    s16 unkE0A;
} Obj003D9E70;

s16 VariantFireGetCallbackOnce_36e4c0(SNode003D9E70 *, s32, s32);

s32 VariantPoolFireScopeCalls_3d9e70(Obj003D9E70 *arg0, s32 arg1) {
    s32 var_18;
    s32 var_17;
    SNode003D9E70 *temp_16;

    var_17 = arg0->unkE08;
    var_18 = 0;
    while (var_17 >= 0) {
        temp_16 = (SNode003D9E70 *)((u8 *)arg0 + (var_17 * 0x38) + 8);
        if (((arg1 == 0) || (arg0->unkE0A == temp_16->unk30)) && !temp_16->f0) {
            if ((u8)VariantFireGetCallbackOnce_36e4c0(temp_16, 0, 0)) {
                var_18 += 1;
            }
            var_17 -= 1;
            temp_16->f0 = 1;
        } else {
            break;
        }
    }
    return var_18;
}
