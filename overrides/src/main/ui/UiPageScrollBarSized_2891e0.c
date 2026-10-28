/* rg-override: replaces game/src/main/ui/UiPageScrollBarSized_2891e0.c sha256 025f4237d8d5db29068033d67e7112825c2181b878c551d654f17d4077c5ae12
 * why: res = (x - end) / d divides by d = 0 when the list does not scroll (hi == lo: the battle
 * menu's ability list with <= 3 rows, soak2 2026-10-25 UBSan float_cast in
 * normal_BtlChgMenuAbilityListCursorBobCb_502150). The EE FPU has no inf / NaN: DIV.S by zero
 * gives +-FLT_MAX (sign = sign(a) xor sign(b)), so retail's caller computes 22 + MAX * 0 = 22 for
 * the scroll thumb; on the host 0/0 = NaN -> (s32)NaN = INT_MIN put the thumb off screen.
 * The division takes the EE result for d == 0 (ee_div0); everything else is the game file. */
/* rgp:protos */
#define RGP_SELF_UiPageScrollBarSized_2891e0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    s16 v[6];
} T6;

typedef struct {
    f32 v[6];
} F6;

typedef struct {
    s16 x;
    s16 y;
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 e;
    s16 f;
    f32 g;
    f32 h;
    u8 pad[8];
} Cell;

/*rgp*/
extern f32 D_0044F850[6];
extern f32 D_0044F870[6];
extern s16 D_0047EA68[6] __attribute__((section(".sdata")));
extern s16 D_0047EA78[6] __attribute__((section(".sdata")));
extern s16 D_0047EA88[6] __attribute__((section(".sdata")));
extern s16 D_0047EA98[6] __attribute__((section(".sdata")));
extern s16 D_0047EAA8[6] __attribute__((section(".sdata")));
extern s16 D_0047EAB8[6] __attribute__((section(".sdata")));

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

/* EE DIV.S by +0 (d is a non-negative s32): +-FLT_MAX with the dividend's sign */
static inline f32 ee_div0(f32 a)
{
    union { f32 f; u32 u; } v;
    v.f = a;
    v.u = (v.u & 0x80000000u) | 0x7F7FFFFFu;
    return v.f;
}

f32 UiPageScrollBarSized_2891e0(u8 *p, s32 a1, s32 mode, s32 x, s32 lo, s32 hi, s32 flag) {
    T6 t0 __attribute__((aligned(16)));
    T6 t1 __attribute__((aligned(16)));
    T6 t2 __attribute__((aligned(16)));
    T6 t3 __attribute__((aligned(16)));
    T6 t4 __attribute__((aligned(16)));
    T6 t5 __attribute__((aligned(16)));
    F6 e __attribute__((aligned(16)));
    F6 c __attribute__((aligned(16)));
    F6 a __attribute__((aligned(16)));
    F6 b __attribute__((aligned(16)));
    f32 fx;
    Cell *q;
    s32 k;
    s32 d;
    s32 j;
    f32 end;
    f32 res;

    fx = x;
    if (mode != 0 && mode != 1) {
        return 0.0f;
    }
    t0 = *(T6 *)D_0047EA68;
    t1 = *(T6 *)D_0047EA78;
    t2 = *(T6 *)D_0047EA88;
    t3 = *(T6 *)D_0047EA98;
    t4 = *(T6 *)D_0047EAA8;
    t5 = *(T6 *)D_0047EAB8;
    e = *(F6 *)D_0044F850;
    c = *(F6 *)D_0044F870;
    BZERO(&a, 0x18);
    BZERO(&b, 0x18);
    q = ((Cell *)UiPageGetWidgetSprites_289ad0(p, a1));
    if (q == 0) {
        return 0.0f;
    }
    k = 0;
    if (mode == 1) {
        k = 3;
        e.v[1] = (x - (t0.v[3] + t0.v[5])) / t0.v[4];
        a.v[0] = 0.0f;
        a.v[1] = a.v[0] + t0.v[3];
        a.v[2] = a.v[1] + t0.v[4] * e.v[1];
    } else {
        c.v[1] = (x - (t1.v[0] + t1.v[2])) / t1.v[1];
        b.v[0] = 0.0f;
        b.v[1] = b.v[0] + t1.v[0];
        b.v[2] = b.v[1] + t1.v[1] * c.v[1];
    }
    d = hi - lo;
    if (d < 0) {
        d = 0;
    }
    if (mode == 1) {
        e.v[4] = e.v[1] - d;
        a.v[3] = 0.0f;
        a.v[4] = a.v[3] + t4.v[3];
        a.v[5] = a.v[4] + t4.v[4] * e.v[4];
        end = a.v[5] + t4.v[2];
    } else {
        c.v[4] = (x - (t5.v[0] + t5.v[2])) / t5.v[1] - d;
        if (c.v[4] < 1.0f) {
            c.v[4] = 1.0f;
        }
        b.v[3] = 0.0f;
        b.v[4] = b.v[3] + t5.v[0];
        b.v[5] = b.v[4] + t5.v[1] * c.v[4];
        end = b.v[5] + t5.v[2];
    }
    res = d != 0 ? (fx - end) / d : ee_div0(fx - end);
    for (j = 0; j < 3; j++) {
        q->x = a.v[3 + j];
        q->y = 3.0f + b.v[3 + j];
        if (flag != 0) {
            q->a = q->e = 0;
            q->b = q->f = 0;
        } else {
            q->a = q->e = t4.v[k + j];
            q->b = q->f = t5.v[k + j];
        }
        q->c = t2.v[k + j];
        q->d = t3.v[k + j];
        q->g = e.v[3 + j];
        q->h = c.v[3 + j];
        q++;
    }
    *(f32 *)(p + 0x58) = res;
    return res;
}
