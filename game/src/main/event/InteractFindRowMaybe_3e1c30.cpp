#include "types.h"

extern "C" {
s32 CharaMgrPoolFindById_3a8c60(s32, s16);                         /* extern */
s32 InteractRunObjectRowMaybe_3e1d20(s32, s32, s16, s16, s32, u64, u64, u8 *); /* extern */
s32 PtalkFindPairRowMaybe_3e2160(s32, s32, s16, s16, u8 *);       /* extern */
extern u8 *D_00483990;
extern s32 D_00483994;
}

extern "C" bool InteractFindRowMaybe_3e1c30(s32 arg0, s32 arg1, u8 *arg2) {
    bool r;
    u8 t;

    if (arg2 == 0) {
        return 0;
    }
    if (D_00483990 == 0 || D_00483994 == 0) {
        return 0;
    }
    r = false;
    if (CharaMgrPoolFindById_3a8c60(*(s32 *)(D_00483990 + 0x14), *(s16 *)(arg2 + 0x2)) != 0) {
        if (PtalkFindPairRowMaybe_3e2160(arg0, arg1, *(s16 *)(arg2 + 0x0), *(s16 *)(arg2 + 0x2), arg2) != 0) {
            r = true;
        }
    } else {
        t = *(u8 *)(arg2 + 0xA);
        if (InteractRunObjectRowMaybe_3e1d20(arg0, arg1, *(s16 *)(arg2 + 0x0), *(s16 *)(arg2 + 0x2), t & 1, (u64)((s64)t << 0x3E) >> 0x3F, (u64)((s64)t << 0x3D) >> 0x3F, arg2) != 0) {
            r = true;
        }
    }
    return r;
}
