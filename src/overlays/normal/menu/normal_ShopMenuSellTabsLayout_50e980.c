#include "types.h"
/* normal 0x0050E980 -- CLOSED 2026-09-01 (s22), 167 bad -> BYTE-IDENTICAL on
 * ONE token.  This unit was [[normal-cse-cost-split]]'s headline instance and
 * that file called the class unreachable after "every source spelling and two
 * full 488-variant pragma sweeps".  It is reachable:
 *
 *   func_28F710(..., 0x16, 0x29, (u32)i * 2);      <- call 1  THE CAST
 *   func_28F710(..., 0x16, 0x29, i * 2 + 1);       <- call 2  plain
 *
 * Retail computes `i * 2` for call 1 and RECOMPUTES it after the `jal` for
 * call 2; our build kept it in a SIXTH callee-saved register spanning both.
 * `(u32)i * 2` and `i * 2` are DIFFERENT expressions to mwcc, so the two sites
 * stop being one value and the recompute falls out -- [[insect-cse-two-spellings]]
 * ("write ONE value TWO WAYS") applied to an INDEX rather than an address.
 *
 * !! WHY THE OLD SWEEPS MISSED IT.  The recorded null list -- i*2 / i+i / i<<1
 * / 2*i, "every one giving the IDENTICAL object" -- changed BOTH sites at once.
 * That is the diagonal of a 2-site lattice and every diagonal cell loses,
 * because two sites spelled the SAME way are one value whatever the spelling.
 * Measured here, 12 cells: the four uniform spellings give 3 objects at 167;
 * every MIXED cell containing exactly one `(u32)` gives ONE object and it is
 * the MATCH.  Same failure shape as [[mwcc-mixed-exit-statements]].
 * The cast is the SPLIT, not the type: it works at site 1 or at site 2, and
 * `(s32)((u32)i * 2 + 1)` at site 2 is the same object as `(u32)i * 2` at
 * site 1.
 *
 * normal_ThinkMenuTabsLayout_520500 is the same function on another widget bank and took
 * this source verbatim -- byte-identical on its first build.
 */
typedef struct Item {
    s16  f00;
    s16  f02;
    u8   pad04[4];
    s64  f08;
    u8   pad10[0x1C - 0x10];
    s16  f1C;
    s16  f1E;
} Item;

typedef struct Hold { u8 pad00[0x24]; Item *f24; } Hold;
typedef struct Ctx  { u8 pad00[0x18]; void *f18; } Ctx;

extern void *D_004845C8;          /* gp - 0xBA8 */
extern s32   D_004659E8[];        /* main-image count, addressed lui/%lo */

extern Ctx  *func_1FEDE0(void);
extern void  func_28F710(void *p, s32 id, s32 c, s32 d, s32 e, s32 f, s32 g,
                         s32 h, s32 i, s32 j, s32 k);
extern Hold *func_290460(void *p, s32 id);
extern void  func_2905B0(void *p, s32 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern s32   func_3C7BA0(void *p, s32 a, s32 b, s32 c);

s32 normal_ShopMenuSellTabsLayout_50e980(s32 id, s32 sel)
{
    Ctx  *c;
    Hold *w;
    Item *a;
    Item *b;
    s32   n;
    s32   i;
    s32   j;

    c = func_1FEDE0();
    n = D_004659E8[0];
    for (i = 0; i < n; i++) {
        if (i == sel) {
            func_28F710(D_004845C8, id, i * 42 + 0x1B, -0x1A, 0x16, 0x29, 0x88, 1,
                        0x16, 0x29, (u32)i * 2);
            func_28F710(D_004845C8, id, i * 42 + 0x31, -0x1A, 0x16, 0x29, 0xA6, 1,
                        0x16, 0x29, i * 2 + 1);
        } else {
            func_28F710(D_004845C8, id, i * 42 + 0x1B, -0x18, 0x16, 0x1B, 0x88, 0x2B,
                        0x16, 0x1B, (u32)i * 2);
            func_28F710(D_004845C8, id, i * 42 + 0x31, -0x18, 0x16, 0x1B, 0xA6, 0x2B,
                        0x16, 0x1B, i * 2 + 1);
        }
    }
    w = func_290460(D_004845C8, 0x39);
    if (w == 0) {
        return 0;
    }
    a = w->f24;
    if (a == 0) {
        return 0;
    }
    func_2905B0(D_004845C8, 0x39, 0.5f, 0.5f, 0.5f, 1.0f);
    b = func_290460(D_004845C8, 0x3A)->f24;
    if (b == 0) {
        return 0;
    }
    for (j = 0; j < 7; j++) {
        if (j == sel) {
            if (j < n) {
                b->f00 = j * 42 + 0x3B;
                b->f02 = -0xC;
                b->f1C = 0xA;
                b->f1E = 0x10;
                b->f08 = func_3C7BA0(c->f18, 0, j, 0);
            } else {
                b->f00 = -1;
            }
        } else {
            a->f00 = j * 42 + 0x3B;
            a->f02 = -0xC;
            a->f1C = 0xA;
            a->f1E = 0x10;
            if (j < n) {
                a->f08 = func_3C7BA0(c->f18, 0, j, 0);
            }
            if (j >= n) {
                a->f00 = -1;
            }
            a++;
        }
    }
    func_291110(D_004845C8, 0x39, 1, 1);
    return 1;
}
