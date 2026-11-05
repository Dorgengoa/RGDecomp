/* rg-override: replaces game/src/main/chara/HunterBountyRefreshProgress_3fdb80.c sha256 1e1b74d44e0bdfd590f7ea4f25375a682e13a12e0435f136cd189398cbc2444f
 * why: BF's aligned(4) made clang pad the 1-byte bitfield struct to 4, shifting the members
 *      after it (mwcc keeps 1); tools/census/aligned_layout_census.py, BRINGUP 2026-10-31 (menu) */
/* rgp:protos */
#define RGP_SELF_HunterBountyRefreshProgress_3fdb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 4;
} BF;   /* port: no aligned(4) (mwcc lays BF out at 1 byte; clang padded it to 4) */

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
_Static_assert(__builtin_offsetof(O, x1E) == 0x1E, "mwcc layout");

/*rgp*/
/*rgp*/
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
    r = ((u8 *)BestiaryCountFindMaybe_3c3440(*(s32 *)(D_00483B28 + 0x18), arg0->x8));
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
