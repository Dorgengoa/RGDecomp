/* rgp:protos */
#define RGP_SELF_VuProgSelResolveMaybe_14e370 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    s32 x;
    s32 y;
    s32 i0;
    s32 i1;
    s32 i2;
    s32 kind;
    s32 v0;
    s32 v1;
    s32 v2;
    s32 w0;
    s32 w1;
    s32 w2;
} A14e370;

typedef struct {
    s32 v[4];
} E14e370;

typedef struct {
    E14e370 e[12];
} R14e370;

typedef struct {
    R14e370 r[4];
    s32 *t0;
    s32 *t1;
    s32 *t2;
} T14e370;

extern u8 D_00491280[];

void VuProgSelResolveMaybe_14e370(A14e370 *arg0)
{
    u8 *e;
    s32 x;
    s32 y;

    x = arg0->x * 0x10;
    e = D_00491280 + arg0->y * 0xC0;
    e = e + x;
    arg0->v0 = *(s32 *)(e + 0x0);
    arg0->v1 = *(s32 *)(e + 0x4);
    arg0->v2 = *(s32 *)(e + 0x8);
    arg0->w0 = (*(s32 **)(e + 0x300))[arg0->i0];
    arg0->w1 = (*(s32 **)(e + 0x304))[arg0->i1];
    arg0->w2 = (*(s32 **)(e + 0x308))[arg0->i2];
    arg0->kind = 6;
}
