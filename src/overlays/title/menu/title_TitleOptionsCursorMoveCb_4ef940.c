#include "types.h"

/* title.bin overlay, 0x004EF940-0x004EFB8C -- the option-page cursor tick.
 *
 * ⚠⚠ THIS ONE SOURCE IS ELEVEN OF GHIDRA'S "FUNCTIONS".  It is a single
 * multi-entry function: one prologue at 0x004EF940, a dense `switch` on
 * `o->f12` through `jtbl_004F1600`, ten case bodies that Ghidra listed as
 * `title_FUN_004ef990` .. `title_FUN_004efb24` because each is a jump-table
 * target, and ONE shared tail and epilogue at 0x004EFB4C.  Every case `b`s to
 * that tail; none of them has a prologue or a `jr $31` of its own.
 *
 * ★ The `beql $1,$0,.L004EFB50` with `lh $3,0x12($16)` in its delay slot is
 * the recorded branch-likely identity -- the slot is a COPY of the merge's
 * first instruction and the branch aims one past it -- so it is a plain
 * `default:` exit and not a construct of its own.
 *
 * ★ The ten cases are three sub-shapes, and which of the two guards comes
 * FIRST is read off the compare chain, not guessed:
 *     f22/f26/f28/f2A/f2C/f20 and (f1A & 1)   test `== 1` first, then `== 0`
 *     f12                                     tests `== 0` first, then `== 1`
 *     (f1A & 2), (f1A & 4)                    test `== 0` first, then the MASK
 * The masked pair keeps the mask value in the compare register, which is why
 * retail materialises the stored `1` separately there and shares it everywhere
 * else.
 */

typedef struct Page {
    u8 pad000[0x10];
    s16 f10;           /* +0x10  the chosen row */
    s16 f12;           /* +0x12  the page id, 0..9 */
} Page;

typedef struct Flags {
    u8 pad000[0x12];
    s16 f12;
    u8 pad014[0x6];
    s16 f1A;
    u8 pad01C[0x4];
    s16 f20;
    s16 f22;
    u8 pad024[0x2];
    s16 f26;
    s16 f28;
    s16 f2A;
    s16 f2C;
} Flags;

typedef struct Sys {
    u8 pad000[0xC];
    Flags *f0C;
} Sys;

extern void *D_00484254;
extern s16 D_00484260;
extern s16 D_00484262;

extern Sys *func_1FEDE0(void);
extern void func_290F60(void *w, s32 id, s32 a, s32 b);

s32 title_TitleOptionsCursorMoveCb_4ef940(Page *o)
{
    Sys *p;
    s32 x;

    if (o->f12 != D_00484262) {
        p = func_1FEDE0();
        switch (o->f12) {
        case 0:
            x = p->f0C->f1A & 1;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        case 1:
            x = p->f0C->f22;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        case 2:
            x = p->f0C->f12;
            if (x == 0) { o->f10 = 0; } else if (x == 1) { o->f10 = 1; }
            break;
        case 3:
            x = p->f0C->f26;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        case 4:
            x = p->f0C->f2A;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        case 5:
            x = p->f0C->f28;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        case 6:
            x = p->f0C->f1A & 2;
            if (x == 0) { o->f10 = 0; } else if (x == 2) { o->f10 = 1; }
            break;
        case 7:
            x = p->f0C->f1A & 4;
            if (x == 0) { o->f10 = 0; } else if (x == 4) { o->f10 = 1; }
            break;
        case 8:
            x = p->f0C->f2C;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        case 9:
            x = p->f0C->f20;
            if (x == 1) { o->f10 = 0; } else if (x == 0) { o->f10 = 1; }
            break;
        }
    }
    func_290F60(D_00484254, 0x4A, 0, o->f12 * 30);
    D_00484260 = o->f10;
    D_00484262 = o->f12;
    return 1;
}
