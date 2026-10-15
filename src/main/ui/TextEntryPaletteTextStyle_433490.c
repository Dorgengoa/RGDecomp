#include "types.h"

typedef struct S00433490 {
    s32 unk0;
    u8 pad4[0xE0];
    s16 unkE4;
} S00433490;

typedef struct SDB150 {
    u8 pad0[0x18];
    u8 unk18;
} SDB150;

extern void TextStyleSetFixedCell_26f0e0(SDB150 *arg0, s32 arg1, s32 arg2);
extern void TextStyleSetFixedPitch_26f140(SDB150 *arg0, s32 arg1);
extern SDB150 D_004DB150;

s32 TextEntryPaletteTextStyle_433490(S00433490 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    SDB150 *p;

    if (arg5 != 0) {
        if (arg0->unk0 == 0) {
            return 1;
        }
        p = &D_004DB150;
        if (p != NULL) {
            TextStyleSetFixedCell_26f0e0(p, 0x15, 0x19);
            if (arg0->unkE4 == 0) {
                p->unk18 = 1;
            }
        }
    } else {
        if (arg0->unk0 == 0) {
            return 1;
        }
        p = &D_004DB150;
        if (p != NULL) {
            TextStyleSetFixedPitch_26f140(p, 0);
            if (arg0->unkE4 == 0) {
                p->unk18 = 0;
            }
        }
    }
    return 1;
}
