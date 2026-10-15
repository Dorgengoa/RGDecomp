#include "types.h"

typedef struct Obj003eff20A {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0x10 - 0x8];
    s16 *unk10;
} Obj003eff20A;

typedef struct Obj003eff20B {
    u8 pad0[0x4];
    s32 unk4;
} Obj003eff20B;

s32 ZoneDataSelectNameMaybe_3eff20(Obj003eff20A *arg0, Obj003eff20B *arg1)
{
    s16 *ptr;

    if (arg0 == NULL) {
        if (arg1 != NULL) {
            return arg1->unk4;
        }
        return 0;
    }
    ptr = arg0->unk10;
    if (ptr == NULL) {
        return 0;
    }
    if (*ptr == 0xA) {
        return arg0->unk4;
    }
    if (arg1 != NULL) {
        return arg1->unk4;
    }
    return 0;
}
