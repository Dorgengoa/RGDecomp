#include "types.h"

struct Obj {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[2];
    s32 unk20;
    s32 unk24;
};

s32 ExecInfoGetEffObjMaybe_3a70b0(struct Obj *arg0, s32 arg1)
{
    s16 temp_3;
    s32 temp_2;

    temp_3 = arg0->unk1C;
    switch (temp_3) {
    case 1:
        if (arg1 != 0) {
            temp_2 = arg0->unk24;
            if (temp_2 != 0) {
                return temp_2;
            }
        }
        return arg0->unk20;
    case 2:
        if (arg1 == 0) {
            return arg0->unk20;
        }
        goto ret0;
    case 3:
        if (arg1 == 0) {
            return arg0->unk20;
        }
        goto ret0;
    case 4:
        if (arg1 == 0) {
            return arg0->unk20;
        }
        goto ret0;
    case 5:
        if (arg1 == 0) {
            return arg0->unk20;
        }
        goto ret0;
    default:
    ret0:
        return 0;
    }
}
