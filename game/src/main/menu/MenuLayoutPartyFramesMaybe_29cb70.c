/* rgp:protos */
#define RGP_SELF_MenuLayoutPartyFramesMaybe_29cb70 1
#include "port/game_protos.h"
#line 1
#define KC 4
#define KW 1
#define KO 3
#define KJ 5
#include "types.h"
#ifndef KO
#define KO 0
#endif
#ifndef KS
#define KS 0
#endif
#if KO == 1
#pragma optimization_level 1
#elif KO == 2
#pragma optimize_for_size on
#elif KO == 3
#pragma optimization_level 3
#elif KO == 4
#pragma optimization_level 2
#endif

#ifndef KI
#define KI 0
#endif
#ifndef KC
#define KC 0
#endif
#if KX
#pragma opt_common_subs off
#endif
#if KC == 0
#define CP(dst, src, N) { s16 *d_ = (s16 *)(dst); s16 *s_ = (s16 *)(src); s32 n_ = N; do { n_--; *d_ = *s_; s_++; d_++; } while (n_ > 0); }
#elif KC == 1
#define CP(dst, src, N) { s16 *d_ = (s16 *)(dst); s16 *s_ = (s16 *)(src); s32 n_ = N; do { *d_++ = *s_++; } while (--n_ > 0); }
#elif KC == 2
#define CP(dst, src, N) { s16 *d_ = (s16 *)(dst); s16 *s_ = (s16 *)(src); s32 n_ = N; do { s16 v_ = *s_; n_--; *d_ = v_; s_++; d_++; } while (n_ > 0); }
#elif KC == 4
#define CP(dst, src, N) { s16 *s_ = (s16 *)(src); s16 *d_ = (s16 *)(dst); s32 n_ = N; do { n_--; *d_ = *s_; s_++; d_++; } while (n_ > 0); }
#elif KC == 5
#define CP(dst, src, N) { s16 *s_ = (s16 *)(src); s16 *d_ = (s16 *)(dst); s32 n_ = N; do { s16 v_ = *s_; n_--; *d_ = v_; s_++; d_++; } while (n_ > 0); }
#elif KC == 6
#define CP(dst, src, N) { s16 *d_ = (s16 *)(dst); s16 *s_ = (s16 *)(src); s32 n_ = N; do { s16 v_ = *s_; n_--; s_++; *d_ = v_; d_++; } while (n_ > 0); }
#else
#define CP(dst, src, N) { s32 i_; for (i_ = 0; i_ < N; i_++) ((s16 *)(dst))[i_] = ((s16 *)(src))[i_]; }
#endif
#ifndef KJ
#define KJ 4
#endif
#if KJ == 0
#define CPI(dst, src, N) { s16 *d_ = (s16 *)(dst); s16 *s_ = (s16 *)(src); s32 n_ = N; do { n_--; *d_ = *s_; s_++; d_++; } while (n_ > 0); }
#elif KJ == 1
#define CPI(dst, src, N) { s16 *d_ = (s16 *)(dst); s16 *s_ = (s16 *)(src); s32 n_ = N; do { *d_++ = *s_++; } while (--n_ > 0); }
#elif KJ == 2
#define CPI(dst, src, N) { s16 *s_ = (s16 *)(src); s16 *d_ = (s16 *)(dst); s32 n_ = N; do { s16 v_ = *s_; n_--; *d_ = v_; s_++; d_++; } while (n_ > 0); }
#elif KJ == 3
#define CPI(dst, src, N) { s32 n_ = N; s16 *s_ = (s16 *)(src); s16 *d_ = (s16 *)(dst); do { n_--; *d_ = *s_; s_++; d_++; } while (n_ > 0); }
#elif KJ == 4
#define CPI(dst, src, N) { s16 *s_ = (s16 *)(src); s16 *d_ = (s16 *)(dst); s32 n_ = N; do { n_--; *d_ = *s_; s_++; d_++; } while (n_ > 0); }
#elif KJ == 5
#define CPI(dst, src, N) *(T9 *)(dst) = *(T9 *)(src);
#else
#define CPI(dst, src, N) { s16 *s_ = (s16 *)(src); s16 *d_ = (s16 *)(dst); s32 n_; for (n_ = N; n_ > 0; n_--) { *d_ = *s_; s_++; d_++; } }
#endif
typedef struct { s16 v[3][7]; } T21;
typedef struct { s16 v[3][3]; } T9;
typedef struct { s16 a; s16 _2; s16 b, c, d, e, f, g; } Rect;
typedef struct {
    Rect r0;
    u8 p10[0x10];
    Rect r20;
    u8 p30[0x16];
    s16 f46;
    u8 p48[0x1E];
    s16 f66;
} Spr;
typedef struct { u8 pad[0x20]; void *p20; } Ent;

extern T21 D_00450A30;
extern T21 D_00450A60;
extern T21 D_00450A90;
extern T21 D_00450AC0;
extern T9 D_00450AF0;
extern s16 D_0047EC30;
extern s16 D_0047EC32;
extern s16 D_0047EC34;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuLayoutPartyFramesMaybe_29cb70(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *ptrs[3];
    s16 c[3];
    T21 t0 __attribute__((aligned(16)));
    T21 t1 __attribute__((aligned(16)));
    T21 t2 __attribute__((aligned(16)));
    T21 t3 __attribute__((aligned(16)));
    T9 idx __attribute__((aligned(16)));
    u8 *g;
    s32 n;
    Ent *e;
    Spr *q;
    s16 *row;
    s32 i;
    u16 id;

    g = ((u8 *)GetGameData_1fede0());
    CP(&t0, &D_00450A30, 21)
    CP(&t1, &D_00450A60, 21)
    CP(&t2, &D_00450A90, 21)
    CP(&t3, &D_00450AC0, 21)
    n = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
#if KW
    if (arg3 == 0) {
#else
    if (arg3 != 0) return 0;
#endif
    if (arg2 >= n) arg2 = n - 1;

    e = ((Ent *)UiFindWidget_290460(*(void **)(arg0 + 0x4C4), 0xB8));
    if (e == 0) return 0;
    q = e->p20;
    if (q == 0) return 0;
    q->r0.g = 0;
    q->r0.f = 0;
    q->r0.c = 0;
    q->r0.b = 0;
    q->r20.a = t0.v[arg2][0];
    q->r20.b = t0.v[arg2][1];
    q->r20.c = t0.v[arg2][2];
    q->r20.d = t0.v[arg2][3];
    q->r20.e = t0.v[arg2][4];
    q->r20.f = t0.v[arg2][5];
    q->r20.g = t0.v[arg2][6];
    q->f46 = 0x66;
    q->f66 = 0x58;

    e = ((Ent *)UiFindWidget_290460(*(void **)(arg0 + 0x4C4), 0xB9));
    if (e == 0) return 0;
    q = e->p20;
    if (q == 0) return 0;
    q->r0.a = t1.v[arg2][0];
    q->r0.b = t1.v[arg2][1];
    q->r0.c = t1.v[arg2][2];
    q->r0.d = t1.v[arg2][3];
    q->r0.e = t1.v[arg2][4];
    q->r0.f = t1.v[arg2][5];
    q->r0.g = t1.v[arg2][6];
    q->r20.a = t2.v[arg2][0];
    q->r20.b = t2.v[arg2][1];
    q->r20.c = t2.v[arg2][2];
    q->r20.d = t2.v[arg2][3];
    q->r20.e = t2.v[arg2][4];
    q->r20.f = t2.v[arg2][5];
    q->r20.g = t2.v[arg2][6];
    q->f46 = 0x58;
    q->f66 = 0x58;

    e = ((Ent *)UiFindWidget_290460(*(void **)(arg0 + 0x4C4), 0xBA));
    if (e == 0) return 0;
    q = e->p20;
    if (q == 0) return 0;
#if KI == 1
    CPI(&idx, &D_00450AF0, 9)
#endif
    q->r0.a = t3.v[arg2][0];
    q->r0.b = t3.v[arg2][1];
    q->r0.c = t3.v[arg2][2];
    q->r0.d = t3.v[arg2][3];
    q->r0.e = t3.v[arg2][4];
    q->r0.f = t3.v[arg2][5];
    q->r0.g = t3.v[arg2][6];
#if KI == 2
    CPI(&idx, &D_00450AF0, 9)
#endif
    q->r20.g = 0;
    q->r20.f = 0;
    q->r20.c = 0;
    q->r20.b = 0;
    q->f46 = 0x58;
    q->f66 = 0x66;
#if KI == 0
    CPI(&idx, &D_00450AF0, 9)
#endif

    for (i = 0; i < 3; i++) {
        e = ((Ent *)UiFindWidget_290460(*(void **)(arg0 + 0x4C4), i + 0xB8));
        if (e == 0) return 0;
        ptrs[i] = e->p20;
    }
    row = idx.v[arg2];
    for (i = 0; i < 3; i++) {
        e = ((Ent *)UiFindWidget_290460(*(void **)(arg0 + 0x4C4), i + 0xB8));
        if (e == 0) return 0;
        e->p20 = ptrs[row[i]];
    }
    c[0] = D_0047EC30;
    c[1] = D_0047EC32;
    c[2] = D_0047EC34;
    for (i = 0; i < 3; i++) {
        id = row[i] + 0xB8;
        if (((Ent *)UiFindWidget_290460(*(void **)(arg0 + 0x4C4), id)) == 0) return 0;
        UiSetWidgetPos_290f60(*(void **)(arg0 + 0x4C4), id, c[i], 0x10);
    }
#if KW
    }
#endif
    return 0;
}
