/* rg-override: replaces game/src/main/chara/UnitOnAppearStartStatusFx_3bce00.c sha256 4d88de67640aa2dc42e340789898922bba773de7caf9e22ed20712c7484677a5
 * why: BF's aligned(4) made clang pad the 1-byte bitfield struct to 4, shifting the members
 *      after it (mwcc keeps 1); tools/census/aligned_layout_census.py, BRINGUP 2026-10-31 (menu) */
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
} BF;   /* port: no aligned(4) (mwcc lays BF out at 1 byte; clang padded it to 4) */

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x409 - 0x10];
    BF f;
} O;
_Static_assert(__builtin_offsetof(O, f) == 0x409, "mwcc layout");

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
