#include "types.h"

extern s32 D_004838E8;

typedef struct InnerCfa70 {
    u8 pad0[0xC];
    s32 vals[5];
} InnerCfa70;

typedef struct ObjCfa70 {
    u8 pad0[0x18];
    InnerCfa70 *unk18;
} ObjCfa70;

s32 InsectRecSlotIndexOf_3cfa70(ObjCfa70 *arg0, s32 val)
{
    s32 i;

    if (val == 0) {
        return -1;
    }
    if (D_004838E8 == 0) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (arg0->unk18->vals[i] == val) {
            return i;
        }
    }
    return -1;
}
