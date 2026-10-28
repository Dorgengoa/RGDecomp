/* rgp:protos */
#define RGP_SELF_AnimKeyEvalFrame_155e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct {
    u8 kind;
    u8 x1;
    u8 x2;
    u8 x3;
    s16 x4;
    u16 x6;
    s32 x8;
    u8 *xC;
} Data;

typedef struct {
    s32 type;
    Data *data;
} Ent;

typedef struct {
    u8 pad[0xC];
    s32 count;
    Ent ent[1];
} Src;

typedef struct {
    f32 f;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 out;
    s32 pad[3];
} Tmp;

typedef void (*Fn)(void *, Data *, f32);

typedef struct {
    f32 w0;
    f32 w4;
    f32 w8;
    f32 wC;
    f32 w10;
    s32 x14;
    u8 pad18[0x50 - 0x18];
} Dst;

/*rgp*/
/*rgp*/
extern Fn D_0047DEF0[] __attribute__((section(".sdata")));

void AnimKeyEvalFrame_155e10(Dst *arg0, Src *arg1, f32 f)
{
    Tmp tmp __attribute__((aligned(16)));
    s32 i;
    Ent *e;
    s32 n;
    Data *d;
    Fn fn __attribute__((aligned(16)));

    i = 0;
    e = arg1->ent;
    n = arg1->count;
    VEC4_ZERO(*(Vec4 *)&arg0->w0);
    VEC4_ZERO(*(Vec4 *)&arg0->w10);
    for (; i < n; i++, e++) {
        d = e->data;
        switch (e->type) {
        case 1:
            arg0->w0 = 1.0f;
            AnimKeyEvalQuat_1555b0((u8 *)arg0 + 0x50, e->data, f);
            break;
        case 3:
            arg0->w8 = 1.0f;
            fn = D_0047DEF0[d->kind];
            if (fn != 0) {
                fn((u8 *)arg0 + 0x20, d, f);
            }
            break;
        case 4:
            arg0->wC = 1.0f;
            fn = D_0047DEF0[d->kind];
            if (fn != 0) {
                fn((u8 *)arg0 + 0x40, d, f);
            }
            break;
        case 2:
            arg0->w4 = 1.0f;
            fn = D_0047DEF0[d->kind];
            if (fn != 0) {
                fn((u8 *)arg0 + 0x30, d, f);
            }
            break;
        case 7:
            arg0->w10 = 1.0f;
            tmp.a = d->x2;
            tmp.b = d->x8;
            tmp.d = d->x6;
            tmp.f = f;
            tmp.c = d->x4;
            AnimKeyFindSpan_155ff0(&tmp);
            if (d->x1 != 8) {
                arg0->x14 = 0;
            } else {
                arg0->x14 = d->xC[tmp.out];
            }
            break;
        }
    }
}
