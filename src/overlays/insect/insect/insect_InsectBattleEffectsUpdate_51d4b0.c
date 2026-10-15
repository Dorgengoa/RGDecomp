/* insect 0x0051D4B0 -- 1,492 bytes.  CLOSED insect session 68 (2026-09-14).
 * The last 3 words (cluster B, 0051D5B4..0051D5C8) were the 16-byte copy
 * temp: retail `lq $a0 ; ... ; sq $a0,272($sp) ; move $a0,$s1`, ours `$a3`
 * with the argument move scheduled BEFORE the sq.  Spelling the copy as
 * `*(u128 *)&b1 = *(u128 *)&m->f180;` (the MAIN idiom, include/vec.h;
 * typedef unsigned __int128 u128) emits the sq FIRST and the temp takes $a0
 * -- MATCH on all five u128 spellings (member, (s32)+0x180, (u8*)+0x180,
 * .f arrays, via a u128 temp).  A struct assignment, a struct-pointer cast,
 * a union cast, a volatile cast, and SIX union TYPES (s64/u64/s32 lanes,
 * xyzw struct) are all the $a3 object (s67 deck F, s68 decks D/E).
 * Deck build/ix68/arms_51d4b0_ix68e2_u128.py.
 *
 * The ix67 park header follows.
 * ---------------------------------------------------------------------- */
/* PARKED, NOT MATCHING -- do not merge.  3 bad of 373 words (ix43m was 7).
 * insect session 67 (2026-09-14).  Supersedes build/ix43m/parked/.
 * .text sha1 80120c63, EXACT LENGTH 0x5d4, frame -0x130 = retail,
 * GPR callee-saved substitutions 0, caller-saved 1, FPR 0.
 *
 * ONE EDIT versus ix43m, worth the whole 4-word head cluster A:
 *
 *        insect_InsectBattleEffectNodeStep_51e0b0(n);        (ix43m called it with NO argument)
 *
 *    The callee's own merged C (src/overlays/insect/insect_InsectBattleEffectNodeStep_51e0b0.cpp)
 *    takes `H *h`; retail's head `lw $a0,8($v1)` IS that argument.  With the
 *    node passed, `n` has two uses (test + argument), is not propagated, and
 *    is coloured $a0 by the argument; `o + i*4` then takes $v1 and the
 *    `addiu $s0,$v1,8` for `s` sinks into the guard's slot -- retail's head
 *    exactly.  The four earlier sessions' ~45 head spellings (ix43h/j/n,
 *    ix64i, ix67a-d) were all measuring the missing argument.
 *    Deck build/ix67/arms_51d4b0_ix67e_callarg.py (arg_n / arg_n_void = 3;
 *    passing s / o / i instead = 8).
 *
 * THE 3 THAT REMAIN -- cluster B, 0051D5B4..0051D5C8: retail's 16-byte copy
 * temp for `b1 = m->f180` is $a0 (`lq $a0` / `sq $a0` then `move $a0,$s1`);
 * ours copies through $a3 with the `move $a0,$s1` argument move scheduled
 * BEFORE the sq.  The caller-saved pool question (insect s58 sec 3 / s65 sec
 * 2).  ix67f: `*(Vec4 *)&`, union-cast, `&b1.f[0]` byte-identical; copy
 * moved after the products 9, before func_151460 13, via a Vec4 temp 33.
 */
#include "types.h"
typedef unsigned __int128 u128;

typedef struct Vec4 { f32 f[4]; } __attribute__((aligned(16))) Vec4;

typedef struct Sub {
    u8   pad000[0x1F0];
    s32  f1F0;                      /* +0x1F0 */
    u8   pad1F4[0x448 - 0x1F4];
    f32  f448;                      /* +0x448 */
} Sub;

typedef struct Obj {
    u8   pad00[0x6C];
    s16  f6C;                       /* +0x6C */
} Obj;

typedef struct Hnd {
    u8   pad000[0x180];
    Vec4 f180;                      /* +0x180 */
} Hnd;

typedef struct Node {
    Sub  *f00;                      /* +0x00 */
    void *f04;                      /* +0x04 */
    Obj  *f08;                      /* +0x08 */
    Obj  *f0C;                      /* +0x0C */
    u8    pad10[4];
    s32   f14;                      /* +0x14 */
    s16   f18;                      /* +0x18 */
    s16   f1A;                      /* +0x1A */
    s16   f1C;                      /* +0x1C */
    s16   f1E;                      /* +0x1E */
} Node;

typedef struct Ctx {
    u8    pad00[4];
    s32   f04;                      /* +0x04 */
    Node *f08[15];                  /* +0x08 */
    u8    pad44[0x48 - 0x44];
    f32   f48;                      /* +0x48 */
} Ctx;

extern const char D_00525400[];
extern const char D_00525408[];
extern const char D_00525410[];
extern const char D_00525418[];

extern void  insect_InsectBattleEffectNodeStep_51e0b0(Node *n);
extern void  insect_InsectBattleEffectsRemoveNode_51dba0(Ctx *o, Node *n);
extern s32   insect_InsectPieceTestStatus_513280(Obj *a, s32 k);

extern Hnd  *func_1C4A90(s32 h, s16 i);
extern s32   func_1511A0(Hnd *m);
extern void  func_1515B0(Sub *s, s32 v);
extern void  func_151110(Sub *s, f32 *v);
extern void  func_151460(Sub *s);
extern s32   func_151220(void *a, const char *t);
extern s32   func_1511F0(void *a, s32 b);
extern void  func_1867A0(Sub *s, const char *t, s32 c);
extern void  func_148F30(s32 t, f32 *v);
extern void  func_1ADEC0(Hnd *g, s32 k, f32 *v);
extern s32   func_171D90(s32 *p, s32 v);

void insect_InsectBattleEffectsUpdate_51d4b0(Ctx *o)
{
    Vec4  b0;
    s32    i;
    Vec4  b1;
    Vec4  ec;
    Vec4  ea;
    Vec4  ed;
    Vec4  fc;
    Vec4  fa;
    Vec4  fd;
    Vec4  ac;
    Node **s;
    Node  *n;
    Node  *q;
    Node  *r;
    Node  *e;
    Obj   *a;
    Obj   *b;
    Hnd   *m;
    Sub   *h;
    Hnd   *g;
    void  *t;
    u8    *p;
    u32    nn;
    s32    v;
    s32    c;
    s32    d;
    s32    x;
    s32    y;
    s32    yv;
    s32    j;
    f32    sp;
    f32    fx;
    f32    fy;

    for (i = 0; i < 15; i++) {
        n = o->f08[i];
        s = &o->f08[i];
        if (n != 0) {
            insect_InsectBattleEffectNodeStep_51e0b0(n);
            n = *s;
            a = n->f08;
            h = n->f00;
            b = n->f0C;
            if (a != 0 && h != 0) {
                x = a->f6C;
                m = func_1C4A90(o->f04, (s16)x);
                if (m != 0) {
                    p = (u8 *)b0.f;
                    nn = 0x10;
                    if (p != 0) {
                        do {
                            *p = 0;
                            nn--;
                            p++;
                        } while (nn != 0);
                    }
                    v = func_1511A0(m);
                    func_1515B0(h, v);
                    func_151110(h, b0.f);
                    h->f448 = 1.0f;
                }
                q = *s;
                x = q->f1C;
                y = q->f1E;
                if (x != -1 && y != -1) {
                    func_151460(h);
                    *(u128 *)&b1 = *(u128 *)&m->f180;
                    fx = 4.0f * (f32)x;
                    fy = 4.0f * (f32)y;
                    b1.f[0] = fx;
                    b1.f[0] = fx - 8.0f;
                    b1.f[2] = fy;
                    b1.f[2] = fy - 12.0f;
                    func_151110(h, b1.f);
                }
                r = *s;
                switch (r->f14) {
                case 0xE:
                case 0xF:
                case 0x10:
                case 0x12:
                case 0x15:
                case 0x16:
                case 0x1A:
                case 0x1B:
                case 0x1C:
                case 0x1D:
                case 0x1F:
                case 0x20:
                case 0x21:
                    t = r->f04;
                    if (t != 0) {
                        func_151460(h);
                        c = func_151220(t, D_00525400);
                        d = func_1511F0(t, c);
                        func_1515B0(h, d);
                        p = (u8 *)ac.f;
                        nn = 0x10;
                        if (p != 0) {
                            do {
                                *p = 0;
                                nn--;
                                p++;
                            } while (nn != 0);
                        }
                        func_151110(h, ac.f);
                    }
                    if (func_171D90(&h->f1F0, -1) != 0) {
                        func_151460(h);
                        insect_InsectBattleEffectsRemoveNode_51dba0(o, *s);
                    }
                    break;
                case 0x14:
                    if (insect_InsectPieceTestStatus_513280(a, 0) != 0 &&
                        insect_InsectPieceTestStatus_513280(a, 0x1B) != 0) {
                        if (h == 0) {
                            break;
                        }
                        func_1867A0(h, D_00525408, 2);
                    } else {
                        insect_InsectBattleEffectsRemoveNode_51dba0(o, *s);
                    }
                    break;
                case 0x11:
                case 0x13:
                case 0x18:
                    if (r->f18 < 0) {
                        insect_InsectBattleEffectsRemoveNode_51dba0(o, r);
                    }
                    break;
                case 0x19:
                    func_1867A0(h, D_00525408, 0);
                    if ((*s)->f18 < 0) {
                        insect_InsectBattleEffectsRemoveNode_51dba0(o, *s);
                    }
                    break;
                case 0x1E:
                    if (h == 0) {
                        break;
                    }
                    c = func_151220(m, D_00525410);
                    d = func_1511F0(m, c);
                    if (d != 0) {
                        func_148F30(d, ec.f);
                    }
                    func_151460(h);
                    func_1867A0(h, D_00525408, 0);
                    if (b != 0) {
                        if (b == a) {
                            insect_InsectBattleEffectsRemoveNode_51dba0(o, *s);
                            break;
                        }
                        g = func_1C4A90(o->f04, b->f6C);
                        if (g != 0) {
                            ea = g->f180;
                            sp = 25.0f / o->f48;
                            for (j = 0; j < 3; j++) {
                                ed.f[j] = (ea.f[j] - ec.f[j]) / sp;
                            }
                        }
                    }
                    e = o->f08[(u32)i];
                    yv = e->f1A;
                    if (e->f18 < 0) {
                        insect_InsectBattleEffectsRemoveNode_51dba0(o, e);
                        break;
                    }
                    for (j = 0; j < 3; j++) {
                        ec.f[j] = ec.f[j] +
                                  ed.f[j] * (25.0f / o->f48 - (f32)yv);
                    }
                    func_151110(h, ec.f);
                    break;
                case 0x17:
                    if (h == 0) {
                        break;
                    }
                    c = func_151220(m, D_00525418);
                    d = func_1511F0(m, c);
                    if (d != 0) {
                        func_148F30(d, fc.f);
                    }
                    func_151460(h);
                    func_1867A0(h, D_00525408, 0);
                    if (b != 0) {
                        g = func_1C4A90(o->f04, b->f6C);
                        if (g != 0) {
                            func_1ADEC0(g, 0, fa.f);
                            sp = 25.0f / o->f48;
                            for (j = 0; j < 3; j++) {
                                fd.f[j] = (fa.f[j] - fc.f[j]) / sp;
                            }
                        }
                    }
                    e = o->f08[(u32)i];
                    yv = e->f1A;
                    if (e->f18 < 0) {
                        insect_InsectBattleEffectsRemoveNode_51dba0(o, e);
                        break;
                    }
                    for (j = 0; j < 3; j++) {
                        fc.f[j] = fc.f[j] +
                                  fd.f[j] * (25.0f / o->f48 - (f32)yv);
                    }
                    func_151110(h, fc.f);
                    break;
                case 0x22:
                    break;
                }
            }
        }
    }
}
