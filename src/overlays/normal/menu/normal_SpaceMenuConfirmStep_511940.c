#include "types.h"
/* normal 0x00511940 -- the "swap page" entry/poll for the 0x25 sub-window.
 * Written FRESH in session 31 (lane n31e) from the retail listing plus the
 * merged sibling normal_SpaceMenuAnimStep_513000.c, which carries the same
 * D_00525AF0 9-entry key/val table walk, the same func_2910A0 / func_290460
 * (+0x20 -> f6) coordinate pair, and the same `s32 id16` / `(s16)(id16+1)`
 * four-call loop.  Notes carried over from that unit:
 *   - Pair is EIGHT bytes (retail indexes D_00525AF0 with `sll ..,3`).
 *   - id16 must be `s32` with an explicit `id16 & 0xFFFF` at the call and an
 *     explicit `(s16)` cast on the increment; a true s16 local narrows at the
 *     READ instead and costs 4 words per loop.
 *   - the +0x20 indirection is read THROUGH a pointer, not off pRes.
 * ss32 (lane nc32o): MATCH.  The `volatile` on `t[2][2]` is LOAD-BEARING and
 * is the whole residue: without it mwcc emits the four fills in REVERSE
 * source order and hoists the `p->f62` load above the store to t[0][0],
 * which costs 7 words (the C0/C4 loads+stores swap places and swap $2/$6).
 * Measured: statement ORDER alone cannot win -- the colour map follows
 * REVERSE source order while the schedule follows it FORWARD, so all 24
 * permutations trade one for the other (best two both read 7 bad on
 * different objects).  Array shape, index cast, pointer aliasing and
 * per-access volatile pins are all normalised onto the same object.
 * `extern volatile s16 D_004806C0..C6` is an equivalent spelling.
 * m2c type census: m2c dropped func_291110's first argument entirely (retail
 * leaves arg0 live in $a0 across the `sh $6,0x62($16)`), and typed the two
 * out-parameters of func_2910A0 as s32* -- both confirmed against 00513000.
 */

typedef struct Ent2 { u8 pad000[0x1A4]; u8 f1A4; } Ent2;
typedef struct Ent  { u8 pad00[0x18]; Ent2 *f18; } Ent;

typedef struct Obj {
    u8    pad00[0x14];
    u8    f14;
    u8    pad15[0x1C - 0x15];
    s32   f1C;
    u8    pad20[0x3C - 0x20];
    s16   f3C;
    s16   f3E;
    u8    pad40[0x48 - 0x40];
    s16   f48;
    s16   f4A[3][4];
    s16   f62;
    void *f64;
    u8    pad68[0x6C - 0x68];
    u8    f6C;
} Obj;

typedef struct { s16 key; s16 val; u8 pad04[4]; } Pair;

extern Pair     D_00525AF0[9];
extern const u8 D_004B2570[];

extern void *D_00481BBC;          /* gp - 0x35B4 */
extern void *D_004846AC;          /* gp - 0xAC4  */
extern s16   D_004846A8;          /* gp - 0xAC8  */
extern s32   D_00480678;          /* gp - 0x4AF8 */
extern u16   D_004806A0[4];       /* gp - 0x4AD0 */
extern u16   D_00480690[4];       /* gp - 0x4AE0 */
extern s16   D_004806C0;          /* gp - 0x4AB0 */
extern s16   D_004806C2;          /* gp - 0x4AAE */
extern s16   D_004806C4;          /* gp - 0x4AAC */
extern s16   D_004806C6;          /* gp - 0x4AAA */

extern s32   func_1839F0(const u8 *p, s32 mask);
extern void  func_1B9520(void *h, s32 a, s32 b, f32 t);
extern Ent  *func_1FEDE0(void);
extern s32   func_28AA30(void *p, s32 id);
extern void  func_28F510(void *p, s32 id, s32 h, s32 slot);
extern void  func_28F930(void *p, s32 id, s32 v, s32 slot);
extern void *func_290460(void *p, u16 id);
extern void  func_2904E0(void *p, s32 id, f32 r, f32 g, f32 b, f32 a, f32 t);
extern void  func_2905B0(void *p, s32 id, f32 r, f32 g, f32 b, f32 a);
extern void  func_290BD0(void *p, s32 id, s32 a, s32 b, s32 c, s32 d);
extern void  func_290F60(void *p, u16 id, s32 x, s32 y);
extern void  func_2910A0(void *p, u16 id, s32 *x, s32 *y);
extern void  func_291110(void *p, s32 id, s32 a, s32 b);

s32 normal_SpaceMenuConfirmStep_511940(Obj *p, s32 init)
{
    s32 spX;
    s32 spY;
    volatile s16 t[2][2];
    s32 x0;
    s32 id16;
    s32 n;
    s16 idKey;
    s16 val;
    s32 i;
    s32 lookup;
    void *pRes;
    void *q;
    s32 x;
    s32 y;

    if (init != 0) {
        p->f62 = 1;
        func_291110(p, 0x24, 1, 1);
        func_28F510(p, 0x25, func_28AA30(D_00481BBC, 0x52), 1);
        func_28F510(p, 0x25, func_28AA30(D_00481BBC, 0x53), 2);
        if (func_1FEDE0()->f18->f1A4 & 1) {
            func_28F510(p, 0x25, func_28AA30(D_004846AC, 1), 0);
        } else {
            func_28F510(p, 0x25, func_28AA30(D_004846AC, p->f1C + 8), 0);
        }
        func_290F60(p, 0x24, 0x6A, 0xAD);
        x0 = p->f62 * 90 + 0xA0;
        id16 = 0x28;
        n = 0;
        do {
            func_290F60(p, id16 & 0xFFFF, x0, 0xE5);
            n++;
            id16 = (s16)(id16 + 1);
        } while (n < 4);
    }

    if (func_1839F0(D_004B2570, 0x8000) != 0) {
        if (p->f62 == 1) {
            func_1B9520(p->f64, 4, 0, 1.0f);
            p->f62 = 0;
        }
    }
    if (func_1839F0(D_004B2570, 0x2000) != 0) {
        if (p->f62 == 0) {
            func_1B9520(p->f64, 4, 0, 1.0f);
            p->f62 = 1;
        }
    }

    t[0][0] = D_004806C0;
    t[0][1] = D_004806C2;
    t[1][0] = D_004806C4;
    t[1][1] = D_004806C6;
    func_28F930(p, 0x25, t[(u32)p->f62][0], 0);
    func_28F930(p, 0x25, t[(u32)p->f62][1], 1);

    if (func_1839F0(D_004B2570, 0x40) != 0) {
        func_1B9520(p->f64, 5, 0, 1.0f);
        if (p->f62 == 0) {
            func_290BD0(p, 0x25, 8, 1, 1, 0);
            func_290BD0(p, 0x25, 8, -1, 0, 0);
        } else {
            func_290BD0(p, 0x25, 8, 1, 0, 0);
            func_290BD0(p, 0x25, 8, -1, 1, 0);
        }
        func_2905B0(p, 0x25, 1.899999976f, 1.899999976f, 1.899999976f, -1.0f);
        func_2904E0(p, 0x25, 1.0f, 1.0f, 1.0f, -1.0f, -0.02999999933f);
        p->f14 = 6;
    }

    if (func_1839F0(D_004B2570, 0x20) != 0) {
        func_1B9520(p->f64, 6, 0, 1.0f);
        func_291110(p, 0x24, 0, 1);
        val = 0;
        idKey = p->f4A[p->f3E][p->f3C];
        i = 0;
        do {
            if (idKey == D_00525AF0[i].key) {
                val = D_00525AF0[i].val;
            }
            i++;
        } while (i < 9);

        lookup = (s32)val;
        func_2910A0(p, D_004806A0[lookup], &spX, &spY);
        pRes = func_290460(p, D_00480690[lookup]);
        q = *(void **)((u8 *)pRes + 0x20);
        {
            s16 f6 = *(s16 *)((u8 *)q + 6);
            s32 half;

            x = spX - 0xA;
            half = f6 >> 1;
            if (f6 < 0) {
                half = (s32)(f6 + 1) >> 1;
            }
            y = (spY + half) - 0xA;
        }

        id16 = 0x28;
        n = 0;
        do {
            func_290F60(p, id16 & 0xFFFF, x, y);
            n++;
            id16 = (s16)(id16 + 1);
        } while (n < 4);

        D_004846A8 = 0;
        D_00480678 = -1;
        p->f14 = 2;
        p->f48 = 0;
        p->f6C = 0;
    }
    return 0;
}
