/* !! PARKED at 11 bad words of 202.  RIGHT LENGTH (0x328).  NOT under src/.
 * 191 of 202 words match, including all seventeen func_13Exxx calls, both
 * `lhu 0x1C` flag tests, the three 4-iteration float loops, the
 * `div.s $f7/$f6` halving, the four corner adds and both func_13F060 pairs.
 * The ENTIRE residue is the register pair used by the inlined 16-byte
 * zeroing loop at 0x004F35B4-0x004F3610:
 *     retail  lh $5,0x4($16) / lh $4,0x6($16) / addiu $3,$29,0x70 /
 *             addiu $2,$0,0x10 ... beqz $3 / sb $0,0($3) / addiu $2,$2,-1 /
 *             addiu $3,$3,1 / bnez $2
 *     ours    the two lh land in $3/$2 and the loop pointer/counter in
 *             $4/$5 -- the two pairs are SWAPPED, 11 words.
 * ARMS MEASURED:
 *  A  `static void clr(u8*,s32)` helper, inlined by mwcc: compiles, but the
 *     static's own text confuses pk_obytecheck (bytecheck.relocate raises
 *     `buffer of at least 112 bytes ... actual 44`).  Do not ship a static
 *     helper in an overlay unit -- it makes the unit UNSCOREABLE.
 *  B  the loop written inline after the hw/hh divides -> 11 bad (above).
 *  C  the loop written BEFORE the hw/hh divides -> 0x31C, three words
 *     SHORT: moving it lets mwcc fold part of the halving.  Rejected.
 *  D  declaration order `u8 *cp; s32 n;` vs `s32 n; u8 *cp;` -> still 11
 *     bad, with cp/n swapping between $4 and $5: LATER-DECLARED TAKES THE
 *     LOWER register is re-confirmed, but both cells leave the pair at
 *     $4/$5 and never reach $3/$2.
 *  E  naming the two `lh` values in locals (`s32 w2; s32 h2;`) declared
 *     BEFORE cp/n -> INERT, still 11 bad, the lh still lands in $3/$2.
 * The two `nop`s inside retail's loop body and the never-true `beqz $3` on a
 * stack address say this block is an INLINED HELPER in retail, so the
 * register pair is probably fixed before inlining and no source-level
 * spelling of the loop will reach it. */
#include "types.h"
/* normal 0x004F33F0 -- draw one panel cell: scale the four channel weights by
 * the cell's own tint and the 0x25 master alpha, set every sprite flag, then
 * emit the two corners of the box. */

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x1C - 0x10];
    u16 f1C;
} Box;

typedef struct Cell {
    u8   pad000[2];
    u16  f02;
    u8   pad004[0x1C - 4];
    s16  f1C;
    Box *f20;
    u8   pad024[0x30 - 0x24];
    f32  f30[4];
} Cell;

typedef struct Rect {
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
} Rect;

extern f32 *func_2904B0(void *p, u16 id);
extern f32  func_290770(void *p, u16 id);
extern void func_13E4F0(void *g, s32 a);
extern void func_13E500(void *g, s32 a);
extern void func_13E390(void *g, s32 a);
extern void func_13E4D0(void *g, s32 a);
extern void func_13E460(void *g, s32 a);
extern void func_13E400(void *g, s32 a);
extern void func_13E3E0(void *g, s32 a);
extern void func_13E2F0(void *g, s32 a);
extern void func_13E3D0(void *g, s32 a);
extern void func_13E430(void *g, s32 a);
extern void func_13E3B0(void *g, s32 a);
extern void func_13F730(void *g, s32 a);
extern void func_13EC00(void *g, s32 a);
extern void func_13EE40(void *g, s32 r, s32 gr, s32 b, s32 a);
extern void func_13ED60(void *g, s32 u, s32 v);
extern void func_13F060(void *g, f32 x, f32 y, f32 z);
extern void func_13F5B0(void *g);

void normal_FieldHudRadarDrawBlip_4f33f0(void *p, void *g, Cell *c, s32 ox, s32 oy, s32 fl)
{
    f32   tmp[4];
    s32   iv[4];
    Box  *bx;
    f32  *w;
    f32   al;
    f32   hw;
    f32   hh;
    s32   i;
    s32   w2;
    s32   h2;

    bx = c->f20;
    if ((c->f1C & 1) != 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        tmp[i] = c->f30[i];
    }
    w = func_2904B0(p, c->f02);
    if (w != NULL) {
        for (i = 0; i < 4; i++) {
            tmp[i] = tmp[i] * *w;
            w++;
        }
    }
    al = func_290770(p, 0x25);
    for (i = 0; i < 4; i++) {
        iv[i] = (s32)(al * (128.0f * tmp[i]));
    }
    func_13E4F0(g, 1);
    if ((bx->f1C & 1) != 0) {
        func_13E4F0(g, 2);
    }
    func_13E500(g, 1);
    func_13E390(g, 0);
    func_13E4D0(g, 1);
    func_13E460(g, 0);
    func_13E400(g, 1);
    func_13E3E0(g, 1);
    func_13E2F0(g, 0);
    if ((bx->f1C & 2) != 0) {
        func_13E3D0(g, 1);
    } else {
        func_13E3D0(g, 0);
    }
    func_13E430(g, 1);
    func_13E3B0(g, 0);
    func_13F730(g, 6);
    func_13EC00(g, fl);
    w2 = bx->f04;
    h2 = bx->f06;
    hw = (f32)w2 / 2.0f;
    hh = (f32)h2 / 2.0f;
    {
        Rect r = {0};

        r.x0 = (f32)ox + ((f32)bx->f00 - hw);
        r.x1 = (f32)ox + ((f32)bx->f00 + hw);
        r.y0 = (f32)oy + ((f32)bx->f02 - hh);
        r.y1 = (f32)oy + ((f32)bx->f02 + hh);
        func_13EE40(g, iv[0], iv[1], iv[2], iv[3]);
        func_13ED60(g, bx->f08, bx->f0A);
        func_13F060(g, r.x0, r.y0, 0.0f);
        func_13ED60(g, bx->f08 + bx->f0C, bx->f0A + bx->f0E);
        func_13F060(g, r.x1, r.y1, 0.0f);
        func_13F5B0(g);
    }
}
