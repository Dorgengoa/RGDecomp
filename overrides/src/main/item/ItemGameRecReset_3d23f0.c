/* rg-override: replaces game/src/main/item/ItemGameRecReset_3d23f0.c sha256 cc7dd75cb433fa3a792fa21b798889df45f2589689d60bd185272b685587dde2
 * why: BF's aligned(4) made clang pad the 1-byte bitfield struct to 4, shifting the members
 *      after it (mwcc keeps 1); tools/census/aligned_layout_census.py, BRINGUP 2026-10-31 (menu) */
/* rgp:protos */
#define RGP_SELF_ItemGameRecReset_3d23f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
} BF;   /* port: no aligned(4) (mwcc lays BF out at 1 byte; clang padded it to 4) */

typedef struct {
    u8 pad0[0x12];
    s16 x12;
    s16 x14;
    s16 x16;
    u8 x18;
    u8 x19;
    u8 x1A;
    u8 pad1B;
    s16 x1C;
    s16 x1E;
    u8 x20[6];
    u8 x26;
    u8 x27;
    BF x28;
    u8 pad29[7];
    s32 x30;
} Q;
_Static_assert(__builtin_offsetof(Q, x30) == 0x30, "mwcc layout");

typedef struct {
    u8 pad0[0x18];
    Q *x18;
} O;

/*rgp*/

void ItemGameRecReset_3d23f0(O *arg0)
{
    s32 i;
    s32 z;

    ItemReset_3d50d0((void *)arg0);
    if (arg0->x18 == NULL) {
        return;
    }
    arg0->x18->x19 = 0;
    arg0->x18->x1A = 0;
    arg0->x18->x14 = 0;
    arg0->x18->x16 = 0;
    arg0->x18->x30 = 0;
    arg0->x18->x18 = 0;
    arg0->x18->x1C = 0;
    arg0->x18->x1E = 0;
    i = 0;
    do {
        arg0->x18->x20[i] = 0;
        i++;
    } while (i < 6);
    arg0->x18->x26 = 1;
    arg0->x18->x27 = 0;
    arg0->x18->x12 = 0;
    arg0->x18->x28.b0 = 0;
    arg0->x18->x28.b1 = 0;
}
