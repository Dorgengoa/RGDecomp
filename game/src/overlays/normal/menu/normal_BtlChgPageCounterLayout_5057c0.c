/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageCounterLayout_5057c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005057C0 -- lays out one two-row confirm popup and hands its record
 * the caller's two ids.  Pass-33 LIST rank: 260 bytes, 65 instructions, FOUR
 * conditional branches, 2 calls.
 *
 * Same {x,y,w,h} row geometry as normal_FUN_004F87C0, and the same source
 * store ORDER: within a row A.x A.y B.x B.y then the two widths and the two
 * heights B-first.  Measured there, transferred here unchanged.
 *
 * Four `if (x == 0) return 0;` guards, each of which mwcc turns into a `bnel`
 * over a `b <epilogue>` with the next block's first instruction in the likely
 * slot -- that is why `sh $0,0x0($8)` sits in the third guard's slot.
 *
 * `dsll32 .. 0 / dsra32 .. 0` on both record stores is an s32 argument widened
 * into an `s64` FIELD, not a cast in the source.  `return 1` costs nothing:
 * mwcc reuses the `addiu $7,$0,0x1` the row-1 A.y store already materialised. */

typedef struct Box  { s16 x; s16 y; s16 w; s16 h; } Box;
typedef struct Row  { Box a; Box b; u8 pad10[0x10]; } Row;
typedef struct Rec  { u8 pad00[8]; s64 f08; u8 pad10[0x28 - 0x10]; s64 f28; } Rec;
typedef struct Hold { u8 pad000[0x20]; Row *f020; Rec *f024; } Hold;

/*rgp*/
/*rgp*/

extern s32 normal_BtlChgPageCounterLayout_5057c0(void *a, u16 id, s32 c, s32 d);

s32 normal_BtlChgPageCounterLayout_5057c0(void *a, u16 id, s32 c, s32 d)
{
    void *w;
    Hold *h;
    Row  *r;
    Rec  *m;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    h = ((Hold *)UiFindWidget_290460(w, id));
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    r[0].a.x = 0;
    r[0].a.y = 0;
    r[0].b.x = 0xD8;
    r[0].b.y = 0xC4;
    r[0].b.w = 0x14;
    r[0].a.w = 0x14;
    r[0].b.h = 0x10;
    r[0].a.h = 0x10;

    r[1].a.x = 0x31;
    r[1].a.y = 1;
    r[1].b.x = 0x64;
    r[1].b.y = 0x62;
    r[1].b.w = 8;
    r[1].a.w = 8;
    r[1].b.h = 0xC;
    r[1].a.h = 0xC;

    m = h->f024;
    if (m == 0) {
        return 0;
    }
    m->f08 = d;
    m->f28 = c;
    return 1;
}
