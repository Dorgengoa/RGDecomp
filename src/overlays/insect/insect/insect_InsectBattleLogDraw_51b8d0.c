#include "types.h"
/* insect 0x0051B8D0 -- 1,192 bytes, 300 instructions, 45 calls, 21 conditional
 * branches.
 *
 * func_15DE80's result lives in $4 across the whole counting loop and is
 * func_1418C0's first argument -- it is NOT the dead move it looks like.
 *
 * func_26F2A0 / func_26F200 return an 8-byte struct BY VALUE: retail builds it
 * in a compiler temp (0xB8 / 0xB0) and copies it with one ld/sd into the named
 * local (0xC8 / 0xC0), then passes it back in one 64-bit register.
 *
 * `dsll32/dsra32 ..,16` appears TWICE on each of the two func_1451x0 results
 * -- once at the assignment and once at the use -- which is a register-
 * resident s16 LOCAL, not an s32 local with a cast (ix22 round 1's narrowing
 * rule).  `bgez / addiu 1 / sra 1` is the signed `/ 2`.
 *
 * Both counting loops are TOP-tested (entered by a `b` to the test), so they
 * are written as plain `for`s with a `break`, not as rotated do/whiles.
 */

typedef struct Ent {
    u8  pad00[0x51];
    u8  f51;                        /* +0x51 */
    u8  pad52[0x54 - 0x52];
    s8  f54;                        /* +0x54 */
    u8  pad55[0x56 - 0x55];
    s16 f56;                        /* +0x56 */
    s16 f58;                        /* +0x58 */
} Ent;

typedef struct Obj {
    u8   pad00[0x4];
    Ent *f04;                       /* +0x04 */
    s16  f08;                       /* +0x08 */
    s16  f0A;                       /* +0x0A */
    s16  f0C;                       /* +0x0C */
    u8   pad0E[0x10 - 0xE];
    s16  f10;                       /* +0x10 */
    s16  f12;                       /* +0x12 */
    s16  f14;                       /* +0x14 */
    s16  f16;                       /* +0x16 */
    s16  f18;                       /* +0x18 */
    u8   pad1A[0x1E - 0x1A];
    s16  f1E;                       /* +0x1E */
    u8   pad20[0x28 - 0x20];
    u8   f28[4];                    /* +0x28 */
} Obj;

typedef struct V8 { s64 x; } V8;

extern volatile s32 D_00485148;     /* _gp - 0x28 */
extern const u8 D_005253F0[];

extern void  func_13E2F0(void *w, s32 a);
extern void  func_13E3B0(void *w, s32 a);
extern void  func_13E400(void *w, s32 a);
extern void  func_13E460(void *w, s32 a);
extern void  func_13E4C0(void *w, s32 a, s32 b);
extern void  func_13E4D0(void *w, s32 a);
extern void  func_13E4F0(void *w, s32 a);
extern void  func_13E500(void *w, s32 a);
extern void  func_13EC00(void *w, void *s);
extern void  func_13ED60(void *w, s32 a, s32 b);
extern void  func_13EE40(void *w, s32 a, s32 b, s32 c, s32 d);
extern void  func_13F110(void *w, s32 x, s32 y, s32 z);
extern void  func_13F5B0(void *w);
extern void  func_13F730(void *w, s32 a);
extern void  func_1418C0(void *h, s32 id, f32 t);
extern void  func_141A20(void *h);
extern void *func_141B00(void *h);
extern s32   func_1451D0(void *h);
extern s32   func_1451E0(void *h);
extern void *func_159FB0(void *a, const u8 *t, s32 k);
extern void *func_15DE40(void);
extern void *func_15DE80(void);
extern void  func_26CDC0(void *q, Ent *p, s32 x, s32 y);
extern s32   func_26DD30(void *q);
extern void  func_26DD40(void *q, s32 a);
extern s32   func_26E430(void *q);
extern void  func_26E440(void *q, s32 a);
extern s32   func_26EDE0(void *q);
extern void  func_26EDF0(void *q, s32 a);
extern void  func_26F1B0(void *q, V8 v);
extern void  func_26F1E0(void *q, s32 a, s32 b, s32 c, s32 d);
extern V8    func_26F200(void *q);
extern void  func_26F250(void *q, V8 v);
extern void  func_26F280(void *q, s32 a, s32 b, s32 c, s32 d);
extern V8    func_26F2A0(void *q);
extern void  func_26F600(void *q);
extern void  func_26F620(void *q, s32 a, s32 b, s32 c, s32 d);
extern s32   func_2F6660(void);
extern void  insect_InsectPlaySe_510870(s32 k);

void insect_InsectBattleLogDraw_51b8d0(Obj *o)
{
    V8    v1;
    V8    v2;
    V8    t1;
    V8    t2;
    s32   ra[4];
    s32   rb[4];
    void *h;
    void *h2;
    void *w;
    void *sp;
    void *q;
    Ent  *p;
    s32   c21;
    s32   c22;
    s32   c23;
    s16   x;
    s16   y;
    u8   *cp;
    u32   cn;
    s32   n;
    s32   i;

    if (o->f04 == 0) {
        return;
    }
    h = func_15DE80();
    q = o->f28;
    if (q == 0) {
        return;
    }
    n = 0;
    p = o->f04;
    i = 0;
    while (i < 0x50) {
        if (p->f54 == 0) {
            break;
        }
        n++;
        i++;
        p++;
    }
    if (n == 0) {
        return;
    }
    if (o->f18 < n) {
        n = o->f18;
    }
    func_1418C0(h, 0x338, 1.0f);
    t1 = func_26F2A0(q);
    v1 = t1;
    t2 = func_26F200(q);
    v2 = t2;
    c21 = func_26EDE0(q);
    c22 = func_26E430(q);
    func_26E440(q, -1);
    c23 = func_26DD30(q);
    func_26EDF0(q, 2);
    func_26F620(q, o->f08 + o->f10, o->f0A + o->f14, o->f08 + o->f12,
                o->f0A + o->f16);
    p = o->f04;
    i = 0;
    while (i < n) {
        if (p->f56 > 0) {
            break;
        }
        if (p->f58 >= 0) {
            insect_InsectPlaySe_510870(p->f58);
            p->f58 = -1;
        }
        func_26DD40(q, p->f51);
        func_26F280(q, 0x80, 0x80, 0x80, 0x80);
        func_26F1E0(q, 0x80, 0x80, 0x80, 0x80);
        func_26CDC0(q, p, o->f08, o->f0A - o->f0C + i * 0x18);
        i++;
        p++;
    }
    func_26DD40(q, c23);
    func_26E440(q, c22);
    func_26F250(q, v1);
    func_26F1B0(q, v2);
    func_26EDF0(q, c21);
    func_26F600(q);
    if (o->f1E != 0) {
    if (func_2F6660() == 0) {
        D_00485148 = D_00485148 + 1;
    }
    if (D_00485148 > 0x1E) {
        D_00485148 = 0;
    }
    if (D_00485148 >= 0xF) {
        return;
    }
    h2 = func_15DE80();
    x = func_1451E0(h2);
    y = func_1451D0(h2);
    sp = func_159FB0(func_15DE40(), D_005253F0, -1);
    w = func_141B00(h2);
    func_13E500(w, 1);
    func_13E4F0(w, 1);
    func_13E4C0(w, 6, 0);
    func_13E4D0(w, 1);
    func_13E460(w, 0);
    func_13E2F0(w, 0);
    func_13E3B0(w, 1);
    func_13E400(w, 1);
    func_13F730(w, 6);
    func_13EC00(w, sp);
    cp = (u8 *)ra;
    cn = 0x10;
    if (cp != 0) {
        do {
            *cp = 0;
            cn--;
            cp++;
        } while (cn != 0);
    }
    ra[0] = (x - 0x16) / 2;
    ra[1] = (y + 0x114) / 2 - 6;
    cp = (u8 *)rb;
    cn = 0x10;
    if (cp != 0) {
        do {
            *cp = 0;
            cn--;
            cp++;
        } while (cn != 0);
    }
    rb[0] = (x + 0x16) / 2;
    rb[1] = (y + 0x134) / 2 - 6;
    func_13EE40(w, 0x80, 0x80, 0x80, 0x80);
    func_13ED60(w, 0xE4, 0);
    func_13F110(w, ra[0], ra[1], 0);
    func_13ED60(w, 0xF6, 0x10);
    func_13F110(w, rb[0], rb[1], 0);
    func_13F5B0(w);
    func_141A20(h2);
    } else {
        D_00485148 = 0;
    }
}
