#include "types.h"
/* normal 0x004EF070 -- FRESH unit, written from the listing in s32 (lane
 * nf32d).  ~680 instructions / 0xA9C bytes, 36 distinct callees, one
 * jalr $25 (a C++ virtual at vtable slot 0xC0 => index (0xC0-8)/4 = 46),
 * so this TU is .cpp for that one call.  The 12 sq/lq are the six
 * callee-saved GPR pairs in the prologue/epilogue, not aligned locals.
 *
 * gp is 0x00485170.  The lwc1 displacements resolve into mwcc float
 * LITERAL POOL entries (0x0047D1C8-0x0048025C):
 *   -0x7E14 D_0047D35C  1.9f       -0x7D1C D_0047D454  1.7f
 *   -0x7BA0 D_0047D5D0  0.2f       -0x7864 D_0047D90C  0.9f
 *   -0x7824 D_0047D94C  0.3f       -0x76EC D_0047DA84 -0.045f
 *   -0x76E0 D_0047DA90  0.785f     -0x76D8 D_0047DA98 -0.2f
 *   -0x7728 D_0047DA48 -0.3f       -0x7704 D_0047DA6C -0.1f
 * The merged sibling normal_FieldHudAllySuggestTimerUpdate_4eea90 measured 1.9f as a LITERAL and
 * D_0047D90C / D_0047DA84 as EXTERNS in exactly the 2905B0+2904E0 pair that
 * also appears here, so that spelling is copied.
 * -0x4CC0 / -0x4CB8 are D_004804B0 / D_004804B8, s16 triples OUTSIDE the
 * pool, copied element-by-element onto two u16 stack triples.
 *
 * BYTE-IDENTICAL 2026-09-05, lane nf32d, session 32: 678 words, MATCH,
 * lit4 ok/6.  The five levers, in the order they paid (2,309 measured arms):
 *
 * 1. THE 6-ARM DISPATCH IS A `switch`, NOT AN if/else-if CHAIN.  Retail tests
 *    11,10,4,3,2,1 (descending) but lays the BODIES out 1,2,3,4,11/10
 *    (ascending).  mwcc emits a switch compare-chain in REVERSE source order
 *    and the case bodies in source order, so only a switch can produce both;
 *    an if/else-if chain emits the bodies in test order and came out 3 words
 *    short with the whole tail transposed.
 * 2. `s32 func_3C3070(void *a, s32 k)`, not `s16 k`: with s16 the two argument
 *    setups are emitted $4 then $5 and retail has $5 then $4.  -2 words.
 * 3. func_1B9520 PROTOTYPE PARAMETER ORDER `(void *, s32, f32, s32)` called
 *    `(D_00484410, 6, 1.0f, 0)`.  Identical registers either way, but the
 *    LAST-declared parameter is emitted last, and retail wants
 *    `daddu $6,$0,$0` in the jal delay slot.  -4 words over two call sites.
 *    `(void*,f32,s32,s32)` and `(f32,void*,s32,s32)` are the same object.
 * 4. The 0x6B x-offset wants `if (f3A6 == 2) {ofs = X;} else {ofs = 0;}`
 *    (or the equivalent ternary) for retail's `bnel`; the seed-then-overwrite
 *    form `ofs = 0; if (...)` gives a plain `bne`, and computing the product
 *    first and clearing in the else is +8.  -1 word.
 * 5. `volatile u16 ta[3]` -- THE LAST 7 WORDS.  Plain `u16 ta[3]` makes mwcc
 *    hoist the LAST element's load AND store to the front of the block (the
 *    load is then stolen by the beql delay slot) and sink `lh $2,0x3A8($20)`
 *    in between, so the block reads L2,D,L0,L1,S2,IX,S0,S1 where retail reads
 *    L0,D,L1,L2,S0,S1,S2,IX.  All six assignment permutations reproduce that
 *    shape exactly (six distinct objects, all 7 bad), and so do a block-scope
 *    aggregate initialiser, a struct copy, an index cast, a hoisted index temp,
 *    a pointer-based copy and a call-result split -- 570 arms, ONE count.
 *    `volatile` on the ARRAY pins the three stores in order and blocks the
 *    hoist.  Note tb[3] (the same three-assignment spelling in case 3) already
 *    matched WITHOUT volatile: what pulls the last pair forward is the
 *    immediately following `lh p->f3A8` competing for the same register.
 */
typedef struct W {
    u8  pad00[0x04];
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
} W;

typedef struct H { u8 pad00[0x20]; W *f20; } H;
typedef struct St { u8 pad00[0x2C]; s16 f2C; } St;
typedef struct Ctx { u8 pad00[0x14]; void *f14; void *f18; void *f1C; } Ctx;

typedef struct E { f32 f00; s16 f04; s16 f06; } E;

typedef struct N {
    u8  pad000[0x2D8];
    E   f2D8[5];
    u8  pad300[0x378 - 0x300];
    s16 f378;
    u8  pad37A[0x398 - 0x37A];
    s16 f398;
    u8  pad39A[0x3A0 - 0x39A];
    s16 f3A0;
    s16 f3A2;
    s16 f3A4;
    s16 f3A6;
    s16 f3A8;
    s16 f3AA;
    s16 f3AC;
} N;

struct Obj {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual s32  s046();
    u8  pad004[0x0C - 0x04];
    s32 f00C;
};

typedef struct Big { u8 pad00[0x28]; } Big;

extern "C" const s16 D_005262E0[];
extern "C" const s16 D_005262F0[][2];
extern "C" const s16 D_00526320[][2];

extern "C" u8    D_004B2570[];
extern "C" s16   D_004804B0[3];     /* gp - 0x4CC0 */
extern "C" s16   D_004804B8[3];     /* gp - 0x4CB8 */
extern "C" void *D_00484410;        /* gp - 0xD60  */

extern "C" f32  D_0047D454;        /* gp - 0x7D1C   1.7f    */
extern "C" f32  D_0047D5D0;        /* gp - 0x7BA0   0.2f    */
extern "C" f32  D_0047D90C;        /* gp - 0x7864   0.9f    */
extern "C" f32  D_0047D94C;        /* gp - 0x7824   0.3f    */
extern "C" f32  D_0047DA48;        /* gp - 0x7728  -0.3f    */
extern "C" f32  D_0047DA6C;        /* gp - 0x7704  -0.1f    */
extern "C" f32  D_0047DA84;        /* gp - 0x76EC  -0.045f  */
extern "C" f32  D_0047DA90;        /* gp - 0x76E0   0.785f  */
extern "C" f32  D_0047DA98;        /* gp - 0x76D8  -0.2f    */

extern "C" s32   func_1839F0(const void *a, s32 b);
extern "C" void  func_1B9520(void *a, s32 b, f32 x, s32 c);
extern "C" s32   func_1F59B0(void);
extern "C" s32   func_1F5BE0(void);
extern "C" s32   func_1FB1F0(s32 a);
extern "C" void *func_1FDB50(void);
extern "C" Ctx  *func_1FEDE0(void);
extern "C" void *func_214A10(void *p);
extern "C" void *func_233B50(void *a, s32 b);
extern "C" void  func_290010(void *w, s32 id, s32 a, s32 b);
extern "C" H    *func_290460(void *p, u16 id);
extern "C" f32  *func_2904B0(void *p, u16 id);
extern "C" void  func_2904E0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern "C" void  func_2905B0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern "C" f32   func_290770(void *p, u16 id);
extern "C" void  func_2907A0(void *p, s32 id, f32 t);
extern "C" void  func_290F60(void *p, s32 id, s32 x, s32 y);
extern "C" void  func_2910A0(void *p, s32 id, s32 *x, s32 *y);
extern "C" void  func_291110(void *p, u16 id, s32 a, s32 b);
extern "C" void  func_2BB9A0(void *a);
extern "C" void  func_2BBA10(void *a, s16 *b, s32 c);
extern "C" void  func_3A80E0(void *a);
extern "C" Obj  *func_3A8C60(void *a, s32 i);
extern "C" s32   func_3AE1A0(void *a);
extern "C" St   *func_3AE3E0(void *a);
extern "C" s32   func_3BABD0(void *a);
extern "C" s32   func_3C3070(void *a, s32 k);
extern "C" void  func_3E2660(Big *a, s32 b);
extern "C" void  func_3E3070(Big *a, s32 b, void *c);
extern "C" void  func_3E3D00(Big *a);

extern "C" void  normal_FieldHudAllySuggestPanelPulse_4ee940(N *p);
extern "C" void  normal_FieldHudAllySuggestTimerUpdate_4eea90(N *p);
extern "C" void  normal_FieldHudAllySuggestCancel_4eec90(N *p);
extern "C" void  normal_FieldHudAllySuggestRingsUpdate_4eee80(N *p);
extern "C" s32   normal_FieldHudPartyRowCount_4f9c50(N *p);

extern "C" s32   normal_FieldHudAllySuggestStep_4ef070(N *p);

s32 normal_FieldHudAllySuggestStep_4ef070(N *p)
{
    s32  sx;
    s32  sy;
    u16  tb[3];
    volatile u16 ta[3];
    Big  big;
    Ctx *c;
    Obj *ob;
    H   *h;
    W   *w;
    W   *w2;
    St  *st;
    s32  n;
    s16  hd;
    s16  key;
    s16  k;
    s16  cnt;
    s32  i;
    s32  j;
    s32  ofs;
    u16  id;
    u16  m;
    f32  v;
    void *q;
    void *r;

    if (p->f3AC != 0) {
        return 1;
    }
    if (p->f378 == 0) {
        return 1;
    }
    if (p->f3A2 == 0) {
        id = 0x74;
        for (i = 0; i < 5; i++) {
            if (func_290770(p, id) > 0.0f) {
                func_290690(p, id, 0.0f, D_0047DA6C, -1.0f);
            }
            id++;
        }
        return 1;
    }
    if (func_1F59B0() == 0x834) {
        return 1;
    }
    c = func_1FEDE0();
    if (c == 0) {
        return 2;
    }
    hd = func_3C3070(c->f18, p->f398);
    n = normal_FieldHudPartyRowCount_4f9c50(p);
    ob = func_3A8C60(c->f14, p->f398);
    if (ob == 0) {
        normal_FieldHudAllySuggestCancel_4eec90(p);
        return 3;
    }
    w = func_290460(p, 0x6D)->f20;
    st = func_3AE3E0(ob);
    if (st == 0) {
        return 1;
    }
    key = st->f2C;
    for (j = 0; j < 11; j++) {
        if (key == D_005262F0[j][0]) {
            w->f08 = D_005262F0[j][1];
        }
        if (key == D_00526320[j][0]) {
            w->f0A = D_00526320[j][1];
        }
    }
    w->f0C = 0x30;
    w->f04 = 0x30;
    w->f0E = 0x30;
    w->f06 = 0x30;
    func_2910A0(p, 0x6A, &sx, &sy);
    func_290F60(p, 0x6D, sx + 0xE, sy - 0x32);
    func_290F60(p, 0x6C, sx + 0xC, sy - 0x32);
    k = p->f3A2;
    if (k != 0xA && k != 0xB) {
        if (p->f3A6 == 2) {
            func_290F60(p, 0x6E, D_005262E0[hd], 0x33);
            func_291110(p, 0x6E, 1, 1);
        } else {
            func_290F60(p, 0x6E, D_005262E0[hd], 0x19);
            func_291110(p, 0x6E, 1, 1);
        }
    }
    if (p->f3A4 >= 0x96) {
        p->f3A4 = 0x96;
        if (p->f3A2 != 4) {
            normal_FieldHudAllySuggestCancel_4eec90(p);
        }
    }
    if (hd >= n || func_3AE1A0(ob) != 0) {
        normal_FieldHudAllySuggestCancel_4eec90(p);
        p->f3A2 = 0xB;
    }
    normal_FieldHudAllySuggestRingsUpdate_4eee80(p);
    switch (p->f3A2) {
    case 1:
        if (!(*func_2904B0(p, 0x60) < 1.9f)) {
            func_2904E0(p, 0x60, 1.0f, 1.0f, 1.0f, 1.0f, D_0047DA48);
            func_2904E0(p, 0x61, 1.9f, 1.9f, 1.9f, -1.0f, D_0047D5D0);
            func_2904E0(p, 0x63, 1.9f, 1.9f, 1.9f, -1.0f, D_0047D5D0);
            func_291110(p, 0x76, 1, 1);
            func_290F60(p, 0x76, 0x3F, 0x14B);
            p->f2D8[2].f04 = 1;
            p->f3A2 = 2;
        }
        break;
    case 2:
        if (*func_2904B0(p, 0x60) <= 1.0f) {
            func_2905B0(p, 0x60, 1.0f, 1.0f, 1.0f, 1.0f);
            func_2905B0(p, 0x61, 1.9f, 1.9f, 1.9f, 1.0f);
            func_2904E0(p, 0x61, D_0047D90C, D_0047D90C, D_0047D90C, 1.0f,
                        D_0047DA84);
            func_2905B0(p, 0x63, 1.9f, 1.9f, 1.9f, 1.0f);
            func_2904E0(p, 0x63, D_0047D90C, D_0047D90C, D_0047D90C, 1.0f,
                        D_0047DA84);
            func_290690(p, 0x65, 1.0f, D_0047D5D0, -1.0f);
            p->f3A2 = 3;
            func_291110(p, 0x77, 1, 1);
            func_290F60(p, 0x77, 0x3F, 0x14B);
            p->f2D8[3].f04 = 1;
        }
        break;
    case 3:
        p->f3A4++;
        if (func_1839F0(D_004B2570, 0x200) != 0) {
            p->f3A8 = 2;
        } else if (func_1839F0(D_004B2570, 4) != 0) {
            p->f3A8 = 0;
        } else if (func_1839F0(D_004B2570, 1) != 0) {
            p->f3A8 = 1;
        }
        if (p->f3A4 >= 0x96) {
            p->f3A8 = -1;
        }
        normal_FieldHudAllySuggestTimerUpdate_4eea90(p);
        normal_FieldHudAllySuggestPanelPulse_4ee940(p);
        if (ob->s046() != 0) {
            p->f3A8 = 2;
        }
        if (func_1FB1F0(ob->f00C) == 0) {
            p->f3A8 = 2;
        }
        k = p->f3A8;
        if (k >= 0) {
            tb[0] = D_004804B0[0];
            tb[1] = D_004804B0[1];
            tb[2] = D_004804B0[2];
            if (k == 1 && p->f3A0 == -1) {
                return 1;
            }
            if (k == 2) {
                func_1B9520(D_00484410, 6, 1.0f, 0);
            } else {
                func_1B9520(D_00484410, 0x1D, 1.0f, 0);
            }
            func_2904E0(p, tb[p->f3A8], D_0047D454, D_0047D454, D_0047D454,
                        -1.0f, D_0047D5D0);
            func_291110(p, 0x74, 1, 1);
            func_290F60(p, 0x74, 0x3F, 0x14B);
            p->f2D8[0].f04 = 1;
            if (p->f3A8 < 2) {
                func_291110(p, 0x6B, 1, 1);
                func_2907A0(p, 0x6B, 1.0f);
                if (p->f3A6 == 2) {
                    ofs = p->f3A8 * 0x1A;
                } else {
                    ofs = 0;
                }
                func_290F60(p, 0x6B, 0, ofs);
                func_2904E0(p, 0x6B, 1.9f, 1.9f, 1.9f, -1.0f, D_0047D94C);
            }
            p->f3A2 = 4;
        }
        if (p->f3A4 == 0xF && func_3BABD0(c->f1C) == 0) {
            n = func_1F5BE0();
            func_3E3D00(&big);
            func_3E3070(&big, n, ob);
            func_3E2660(&big, 0);
        }
        break;
    case 4:
        ta[0] = D_004804B8[0];
        ta[1] = D_004804B8[1];
        ta[2] = D_004804B8[2];
        m = ta[p->f3A8];
        v = *func_2904B0(p, m);
        if (v >= D_0047D454) {
            func_2904E0(p, m, 1.0f, 1.0f, 1.0f, -1.0f, D_0047DA98);
            func_2904E0(p, 0x6B, 1.0f, 1.0f, 1.0f, -1.0f, D_0047DA48);
        } else {
            if (v <= 1.0f) {
                func_2905B0(p, m, 1.0f, 1.0f, 1.0f, -1.0f);
                func_290690(p, 0x6B, 0.0f, D_0047DA6C, -1.0f);
                cnt = p->f3AA + 1;
                p->f3AA = cnt;
                if (cnt >= 5) {
                    p->f3AA = 5;
                    r = func_233B50(func_1FDB50(), p->f398);
                    q = 0;
                    if (r != 0) {
                        q = func_214A10(r);
                    }
                    k = p->f3A8;
                    if (k == 2) {
                        if (q != 0) {
                            func_2BB9A0(q);
                        }
                        p->f3AC = 0;
                        normal_FieldHudAllySuggestCancel_4eec90(p);
                    } else if (q != 0) {
                        func_2BBA10(q, &p->f398, k);
                        p->f3AC = 0;
                        normal_FieldHudAllySuggestCancel_4eec90(p);
                    }
                }
            }
        }
        break;
    case 10:
    case 11:
        if (func_290770(p, 0x60) <= 0.0f) {
            func_290010(p, 0x5F, 0, -1);
            id = 0x74;
            for (i = 0; i < 5; i++) {
                p->f2D8[i].f00 = D_0047DA90;
                h = func_290460(p, id);
                if (h != 0) {
                    w2 = h->f20;
                    if (w2 != 0) {
                        w2->f04 = 0x22;
                        w2->f06 = 0x22;
                        p->f2D8[i].f04 = 0;
                        func_291110(p, id, 0, 1);
                        id++;
                    }
                }
            }
            if (p->f3A2 == 0xB) {
                func_3A80E0(&p->f398);
            }
            p->f3A2 = 0;
            p->f3A8 = -1;
            p->f3AA = 0;
            p->f3AC = 0;
        }
        break;
    }
    return 0;
}
