#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    s32 i0;
    s32 i1;
    f32 f8;
    f32 fC;
} Link185170;

typedef struct {
    f32 x, y, z, w;
} P185170;

typedef struct {
    s32 unk0;
    s32 unk4;
    u128 *unk8;
    u128 *unkC;
    u128 *unk10;
    P185170 *unk14;
    s32 unk18;
    Link185170 *unk1C;
    u128 unk20;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    u8 pad3C[4];
    u128 unk40;
    s32 unk50;
    f32 unk54;
    f32 unk58;
} T185170;

extern void VecScale_13be00(u128 *, u128 *, f32);
extern void VecSub_13be40(u128 *, u128 *, u128 *);
extern void VecAddInPlace_13e070(u128 *, u128 *);
extern void ClothSolveDistance_185450(u128 *, u128 *, f32, f32);

void ClothSimStep_185170(T185170 *arg0)
{
    s32 k;
    s32 i;
    u128 *p;
    f32 s;
    u128 v;
    Link185170 *e;
    s32 m;
    s32 n;
    u128 *dst;
    u128 *p1;
    P185170 *src;
    u128 *q;
    u128 *r;
    f32 t;
    u128 *q1;
    s32 ok;
    s32 c;

    ok = arg0->unk0 != 0;
    if (ok) {
        ok = arg0->unk4 > 0;
    }
    if (!(ok & 0xFF)) {
        return;
    }
    p1 = arg0->unk8;
    q1 = arg0->unk10;
    for (i = 0; i < arg0->unk4; i++, p1++, q1++) {
        VecAddInPlace_13e070(q1, &arg0->unk20);
        VecAddInPlace_13e070(p1, q1);
    }
    k = 0;
    do {
        e = arg0->unk1C;
        m = arg0->unk18;
        while (m > 0) {
            ClothSolveDistance_185450(&arg0->unk8[e->i0], &arg0->unk8[e->i1], e->f8, e->fC);
            m--;
            e++;
        }
        dst = arg0->unk8;
        src = arg0->unk14;
        c = arg0->unk4;
        while (c > 0) {
            if (!(src->w <= 0.0f)) {
                *dst = *(u128 *)src;
            }
            c--;
            dst++;
            src++;
        }
        k++;
    } while (k < 2);
    arg0->unk50 = arg0->unk50 * 0x10DCD + 1;
    t = arg0->unk58 + 0.5f * (0.5f * ((f32)arg0->unk50 / -2147483648.0f - 0.5f));
    arg0->unk58 = t;
    if (!(t <= 1.5f)) {
        arg0->unk58 = 1.5f;
    }
    if (arg0->unk58 < 0.5f) {
        arg0->unk58 = 0.5f;
    }
    p = arg0->unk8;
    q = arg0->unk10;
    r = arg0->unkC;
    m = arg0->unk4;
    s = arg0->unk34 * (arg0->unk58 * arg0->unk38);
    while (m > 0) {
        VecSub_13be40(q, p, r);
        VecScale_13be00(q, q, arg0->unk30);
        if (arg0->unk38 != 0.0f) {
            arg0->unk50 = arg0->unk50 * 0x10DCD + 1;
            t = arg0->unk54 + 0.5f * (0.5f * ((f32)arg0->unk50 / -2147483648.0f - 0.5f));
            arg0->unk54 = t;
            if (!(t <= 1.0f)) {
                arg0->unk54 = 1.0f;
            }
            if (arg0->unk54 < 0.0f) {
                arg0->unk54 = 0.0f;
            }
            VecScale_13be00(&v, &arg0->unk40, s * arg0->unk54);
            VecAddInPlace_13e070(q, &v);
        }
        m--;
        q++;
        *r = *p;
        p++;
        r++;
    }
}
