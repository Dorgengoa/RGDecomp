#include "types.h"


typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Mot {
    u8 pad0[0x10];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[0x14];
    s32 f30;
    s32 f34;
    f32 f38;
} Mot;
typedef struct Obj {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad40[0x10];
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
    f32 f68;
    u8 pad6C[4];
    f32 f70;
    f32 f74;
    f32 f78;
    s32 f7C;
    u8 pad80[0x20];
    f32 fA0;
    f32 fA4;
    f32 fA8;
    u8 padAC[0x44];
    f32 fF0;
    u8 padF4[4];
    f32 fF8;
    f32 fFC;
    V4 v100;
    u8 pad110[0x10];
    V4 v120;
    u8 pad130[0x10];
    s32 f140;
} Obj;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void VecAdd_13be20(V4 *, V4 *, V4 *);
extern void VecSub_13be40(V4 *, V4 *, V4 *);
extern void sceVu0CopyVector(V4 *, V4 *);
extern void sceVu0DivVector(V4 *, V4 *, f32);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));
extern const f32 D_0047DBD0 __attribute__((section(".sdata")));
extern const f32 D_0047DBD4 __attribute__((section(".sdata")));
extern const f32 D_0047DBD8 __attribute__((section(".sdata")));
extern const f32 D_0047DBDC __attribute__((section(".sdata")));
extern const f32 D_0047DBE0 __attribute__((section(".sdata")));
extern const f32 D_0047DBE4 __attribute__((section(".sdata")));
extern const f32 D_0047DBE8 __attribute__((section(".sdata")));
extern const f32 D_0047DBEC __attribute__((section(".sdata")));
extern const f32 D_0047DBF0 __attribute__((section(".sdata")));
extern const f32 D_0047DBF4 __attribute__((section(".sdata")));
extern const f32 D_0047DBF8 __attribute__((section(".sdata")));
extern const f32 D_0047DBFC __attribute__((section(".sdata")));
extern const f32 D_0047DC00 __attribute__((section(".sdata")));
extern const f32 D_0047DC04 __attribute__((section(".sdata")));

#define WRAP(a, KS, KC, KA) if ((a) > D_0047D1FC) { (a) -= KS; } else if ((a) <= KC) { (a) += KA; }

s32 EventCameraCmdOrbitMove_255720(Mot *m, Obj *o) {
    s32 n;
    s32 half;
    f32 d;
    s32 moved;
    s32 moved2;


    n = m->f34;
    if (n == 0) {
        half = o->f140;
    } else {
        half = o->f140 / 2;
    }
    if (o->f3C >= m->f30 + half) {
        o->f3C = 0;
        return 0;
    }
    if (o->f3C <= 0) {
        if (o->f7C != 0) {
            d = m->f10 - o->fA0;
        } else {
            d = m->f10 - o->f70;
        }
        if (d > D_0047D1FC) {
            d -= D_0047DBD4;
        } else if (d <= D_0047DBD0) {
            d += D_0047DBD4;
        }
        o->fF0 = d / (f32)m->f30;
        o->fF8 = (m->f14 - o->f74) / (f32)m->f30;
        o->fFC = (m->f18 - o->f78) / (f32)m->f30;
        o->f140 = (s32)((f32)m->f30 * m->f38);
        o->v120.x = o->fF0;
        o->v120.y = o->fF8;
        o->v120.z = o->fFC;
        o->v120.w = 1.0f;
        sceVu0DivVector(&o->v120, &o->v120, (f32)o->f140);
        if (m->f34 != 2) {
            sceVu0CopyVector(&o->v100, &o->v120);
        } else {
            o->v100.x = o->fF0;
            o->v100.y = o->fF8;
            o->v100.z = o->fFC;
            o->v100.w = 1.0f;
        }
    } else if (o->f7C != 0) {
        moved = 0;
        if (o->f3C < o->f140) {
        if (n == 0) goto go0;
        if (n == 1) {
go0:
            VecAdd_13be20(&o->v100, &o->v100, &o->v120);
            o->fA0 += o->v100.x;
            WRAP(o->fA0, D_0047DBD4, D_0047DBD8, D_0047DBDC);
            moved = 1;
            o->fA4 += o->v100.y;
            o->fA8 += o->v100.z;
        }
        }
        n = m->f34;
        if ((n == 2 && o->f3C >= m->f30 - o->f140 / 2) || (n == 0 && o->f3C >= m->f30)) {
            VecSub_13be40(&o->v100, &o->v100, &o->v120);
            o->fA0 += o->v100.x;
            WRAP(o->fA0, D_0047DBDC, D_0047DBE0, D_0047DBE4);
            moved = 1;
            o->fA4 += o->v100.y;
            o->fA8 += o->v100.z;
            o->f5C = 1.0f;
        }
        if (!moved) {
            o->fA0 += o->fF0;
            WRAP(o->fA0, D_0047DBE4, D_0047DBE8, D_0047DBEC);
            o->fA4 += o->fF8;
            o->fA8 += o->fFC;
        }
    } else {
        moved2 = 0;
        if (o->f3C < o->f140) {
        if (n == 0) goto go1;
        if (n == 1) {
go1:
            VecAdd_13be20(&o->v100, &o->v100, &o->v120);
            o->f70 += o->v100.x;
            WRAP(o->f70, D_0047DBEC, D_0047DBF0, D_0047DBF4);
            moved2 = 1;
            o->f74 += o->v100.y;
            o->f78 += o->v100.z;
        }
        }
        n = m->f34;
        if ((n == 2 && o->f3C >= m->f30 - o->f140 / 2) || (n == 0 && o->f3C >= m->f30)) {
            VecSub_13be40(&o->v100, &o->v100, &o->v120);
            o->f70 += o->v100.x;
            WRAP(o->f70, D_0047DBF4, D_0047DBF8, D_0047DBFC);
            moved2 = 1;
            o->f74 += o->v100.y;
            o->f78 += o->v100.z;
            o->f5C = 1.0f;
        }
        if (!moved2) {
            o->f70 += o->fF0;
            WRAP(o->f70, D_0047DBFC, D_0047DC00, D_0047DC04);
            o->f74 += o->fF8;
            o->f78 += o->fFC;
        }
        o->f50 = o->f60 + o->f78 * Sinf_128fd0(o->f70);
        o->f54 = o->f74 + o->f64;
        o->f58 = o->f68 + o->f78 * Cosf_128d30(o->f70);
    }
    o->f3C++;
    return 1;
}
