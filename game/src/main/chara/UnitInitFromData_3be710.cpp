/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

class VThis {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12() { VCM0(void, 0x38); }
    void v13() { VCM0(void, 0x3C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * get() { return VCM0(u8 *, 0x35C); }
};
class VSub {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void reset() { VCM0(void, 0x1C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void set(void *o, s32 id) { VCM(void, (void *, void *, s32), 0x78, o, id); }
};

typedef struct Flags408 {
    u8 b0:1;
    u8 a:1;
    u8 b:1;
    u8 c:1;
    u8 d:1;
    u8 e:1;
    u8 f:1;
    u8 g:1;
    u8 h:1;
    u8 x1:1;
    u8 i:1;
    u8 j:1;
    u8 k:1;
    u8 l:1;
    u8 x6:1;
    u8 x7:1;
} Flags408;

typedef struct Flags80 {
    u8 s0:1;
    u8 s1:1;
    u8 s2:1;
    u8 s3:1;
    u8 s4:1;
    u8 s5:1;
    u8 s6:1;
    u8 s7:1;
    u8 t0:1;
    u8 t1:1;
    u8 t2:1;
    u8 t3:5;
} Flags80;

typedef struct Data {
    s16 id;             /* 0x00 */
    u8 pad2[0x76];
    s16 n78;            /* 0x78 */
    u8 pad7A[2];
    s16 **list;         /* 0x7C */
    Flags80 fl;         /* 0x80 */
} Data;

typedef struct Src {
    u8 pad0[4];
    u16 h4;             /* 0x04 */
    u16 h6;             /* 0x06 */
    u16 h8;             /* 0x08 */
    u16 hA;             /* 0x0A */
    f32 f0C[4];         /* 0x0C */
    f32 f1C[3];         /* 0x1C */
    s8 c28[5];          /* 0x28 */
    s8 c2D[5];          /* 0x2D */
    s8 c32[8];          /* 0x32 */
    s8 c3A[8];          /* 0x3A */
    s8 c42[4];          /* 0x42 */
} Src;

typedef struct Obj {
    u8 pad0[4];
    s16 id;             /* 0x004 */
    u8 pad6[0xA];
    u16 h10;            /* 0x010 */
    u8 pad12[0x1A];
    u16 h2C[2];         /* 0x02C */
    u8 pad30[0xC];
    f32 f3C[3][2];      /* 0x03C */
    s16 a54[5][2];      /* 0x054 */
    s16 a68[8][2];      /* 0x068 */
    s16 a88[8][2];      /* 0x088 */
    s16 aA8[4][2];      /* 0x0A8 */
    u8 padB8[0x234 - 0xB8];
    Data *data;         /* 0x234 */
    u8 f238;            /* 0x238 */
    u8 pad239;
    s16 f23A;           /* 0x23A */
    u16 h23C[2];        /* 0x23C */
    f32 f240[4][2];     /* 0x240 */
    u16 h260[2];        /* 0x260 */
    s16 a264[5][2];     /* 0x264 */
    u8 sub[8][0x24];    /* 0x278 (ends 0x398) */
    u8 pad398[0x408 - 0x398];
    Flags408 fl;        /* 0x408 */
} Obj;

extern "C" u8 UnitBaseInitFromData_3b8300(void *, int);

extern "C" s32 UnitInitFromData_3be710(Obj *o, s32 unused, Data *d)
{
    Src *s;
    s32 i;
    s32 k;
    s32 n;
    s16 **p;
    s16 *e;
    VSub *v;

    if (d == 0) {
        return 0;
    }
    o->id = d->id;
    o->data = d;
    if (UnitBaseInitFromData_3b8300((void *)o, (int)unused) == 0) {
        return 0;
    }
    o->f238 = 0;
    o->f23A = -1;
    s = (Src *)((VThis *)o)->get();
    if (s == 0) {
        return 0;
    }
    o->h10 = s->h4;
    i = 0;
    do {
        o->h23C[i] = s->h6;
        o->h2C[i] = s->h8;
        o->f240[0][i] = s->f0C[0];
        o->f240[1][i] = s->f0C[1];
        o->f240[2][i] = s->f0C[2];
        o->f240[3][i] = s->f0C[3];
        o->f3C[0][i] = s->f1C[0];
        o->f3C[1][i] = s->f1C[1];
        o->f3C[2][i] = s->f1C[2];
        o->h260[i] = s->hA;
        for (k = 0; k < 5; k++) {
            o->a264[k][i] = s->c28[k];
        }
        for (k = 0; k < 5; k++) {
            o->a54[k][i] = s->c2D[k];
        }
        for (k = 0; k < 8; k++) {
            o->a68[k][i] = s->c32[k];
        }
        for (k = 1; k < 8; k++) {
            o->a88[k - 1][i] = s->c3A[k];
        }
        for (k = 0; k < 4; k++) {
            o->aA8[k][i] = s->c42[k];
        }
        i++;
    } while (i < 2);
    o->fl.a = d->fl.s0;
    o->fl.b = d->fl.s1;
    o->fl.c = d->fl.s3;
    o->fl.d = d->fl.t0;
    o->fl.e = d->fl.t1;
    o->fl.h = d->fl.t2;
    o->fl.f = d->fl.s4;
    o->fl.i = d->fl.s5;
    o->fl.j = d->fl.s6;
    o->fl.k = d->fl.s7;
    o->fl.g = 0;
    o->fl.l = 0;
    for (k = 0; k < 8; k++) {
        ((VSub *)o->sub[k])->reset();
    }
    p = o->data->list;
    n = 0;
    if (p != 0 && o->data->n78 > 0) {
        for (k = 0; k < o->data->n78; k++, p++) {
            e = *p;
            if (e != 0) {
                v = (VSub *)o->sub[n];
                n++;
                v->set(o, *e);
            }
        }
    }
    ((VThis *)o)->v12();
    ((VThis *)o)->v13();
    return 1;
}
