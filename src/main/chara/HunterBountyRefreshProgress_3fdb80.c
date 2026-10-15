#include "types.h"

typedef struct {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 4;
} BF;

typedef struct {
    u8 pad0[8];
    s16 x8;
    u8 padA[2];
    s16 xC;
    s16 xE;
    u8 pad10[2];
    s16 x12;
    u8 pad14[8];
    BF f;
    u8 pad1D;
    s16 x1E;
} O;

extern u8 *BestiaryCountFindMaybe_3c3440(s32, s16);
extern s32 StateFlagTest_3ccd70(s32, s16);
extern u8 *D_00483B28;

s32 HunterBountyRefreshProgress_3fdb80(O *arg0) {
    s32 z;
    u8 *r;

    if (D_00483B28 == NULL) {
        return 0;
    }
    arg0->x1E = 0;
    z = 0;
    arg0->f.b1 = z;
    arg0->f.b2 = z;
    arg0->f.b3 = z;
    r = BestiaryCountFindMaybe_3c3440(*(s32 *)(D_00483B28 + 0x18), arg0->x8);
    if (r != NULL) {
        arg0->x1E = *(s16 *)(r + 2);
    }
    if (arg0->x1E >= arg0->xC) {
        arg0->f.b1 = 1;
    }
    if (arg0->x1E >= arg0->xE) {
        arg0->f.b2 = 1;
    }
    arg0->f.b3 = StateFlagTest_3ccd70(*(s32 *)(D_00483B28 + 0x10), arg0->x12);
    return 1;
}
