/* rgp:protos */
#define RGP_SELF_AnimKeyEvalCamera_155830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 kind;
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

typedef void (*Fn)(void *, Data *, f32);

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    f32 x14;
    f32 x18;
} Dst;

/*rgp*/
extern Fn D_0047DEF0[] __attribute__((section(".sdata")));
extern Fn D_0047DF00[] __attribute__((section(".sdata")));

void AnimKeyEvalCamera_155830(Dst *arg0, Src *arg1, f32 f)
{
    f32 tmp[4] __attribute__((aligned(16)));
    s32 i;
    Ent *e;
    s32 n;
    Data *d;
    Fn fn __attribute__((aligned(16)));

    i = 0;
    e = arg1->ent;
    n = arg1->count;
    arg0->w4 = 0;
    arg0->w10 = 0;
    arg0->wC = 0;
    arg0->w8 = 0;
    arg0->w0 = 0;
    for (; i < n; i++, e++) {
        d = e->data;
        switch (e->type) {
        case 1:
            arg0->w0 = 1;
            AnimKeyEvalQuat_1555b0((u8 *)arg0 + 0x20, e->data, f);
            break;
        case 3:
            arg0->w8 = 1;
            fn = D_0047DEF0[d->kind];
            if (fn != 0) {
                fn((u8 *)arg0 + 0x30, d, f);
            }
            break;
        case 14:
            arg0->w4 = 1;
            fn = D_0047DEF0[d->kind];
            if (fn != 0) {
                fn((u8 *)arg0 + 0x40, d, f);
            }
            break;
        case 13:
            arg0->wC = 1;
            fn = D_0047DF00[d->kind];
            if (fn != 0) {
                fn(tmp, d, f);
                arg0->x14 = tmp[0];
            }
            break;
        case 15:
            arg0->w10 = 1;
            fn = D_0047DF00[d->kind];
            if (fn != 0) {
                fn(tmp, d, f);
                arg0->x18 = tmp[0];
            }
            break;
        }
    }
}
