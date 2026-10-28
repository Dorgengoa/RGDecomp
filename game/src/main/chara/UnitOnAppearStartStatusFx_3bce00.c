/* rgp:protos */
#define RGP_SELF_UnitOnAppearStartStatusFx_3bce00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
} __attribute__((aligned(4))) BF;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x409 - 0x10];
    BF f;
} O;

/*rgp*/
/*rgp*/

s32 UnitOnAppearStartStatusFx_3bce00(O *arg0) {
    s32 r;

    if (arg0->f.b6) {
        return 0;
    }
    arg0->f.b6 = 1;
    r = ((s32)GetStatusEffect_2d9010());
    if (arg0->f.b2) {
        if (r != 0) {
            StatusEffectStart_33c240(r, 0xB, arg0->unkC, -1);
        }
    }
    if (arg0->f.b3) {
        if (r != 0) {
            StatusEffectStart_33c240(r, 0xA, arg0->unkC, -1);
        }
    }
    return 1;
}
