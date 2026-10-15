#include "types.h"

extern s32 CharaHasLandedMaybe_20fdb0(u8 *);

s16 CharaSelectDeathState_217ca0(u8 *arg0)
{
    s16 sel;

    sel = *(s16 *)(arg0 + 0xA34);
    switch (sel) {
    case 10:
        if (*(u64 *)(arg0 + 0x570) & ((u64)0x1000 << 32)) {
            return 20;
        }
    case 0:
    case 1:
    case 3:
    case 4:
    case 20:
        return sel;
    case 2:
        if (CharaHasLandedMaybe_20fdb0(arg0) != 0) {
            return 3;
        }
        return 2;
    default:
        return (*(u64 *)(arg0 + 0x3D0) & ((u64)0x80000 << 32)) != 0;
    }
}
