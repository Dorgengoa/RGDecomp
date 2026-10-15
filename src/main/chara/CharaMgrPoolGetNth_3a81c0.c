#include "types.h"

extern s32 PoolGetUsedElem_36acb0(s32, s32);
extern const s32 D_004659B8;

struct S003A81C0 {
    u8 pad0[8];
    s32 unk8;
};

s32 CharaMgrPoolGetNth_3a81c0(struct S003A81C0 *arg0, s32 arg1)
{
    s32 var_17;
    s32 var_16;
    s32 temp_20;
    s32 temp_2;

    if (arg0->unk8 == 0) {
        return 0;
    }
    var_17 = 0;
    var_16 = 0;
    temp_20 = D_004659B8;
    while (var_16 < temp_20) {
        temp_2 = PoolGetUsedElem_36acb0(arg0->unk8, var_16);
        if (temp_2 != 0) {
            if (var_17 == arg1) {
                return temp_2;
            }
            var_17 += 1;
            goto incr;
        }
        var_16 += 1;
        continue;
    incr:
        var_16 += 1;
    }
    return 0;
}
