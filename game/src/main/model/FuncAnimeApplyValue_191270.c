/* rgp:protos */
#define RGP_SELF_FuncAnimeApplyValue_191270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    u8 *obj;
    u8 *a;
    u8 *b;
    u8 *c;
    s32 pad[4];
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} S191270;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC __attribute__((section(".sdata")));

void FuncAnimeApplyValue_191270(S191270 *s, u128 *v) {
    u8 *o;
    s8 *p;
    u8 *b;
    u8 *a;
    u8 *q;
    f32 m[4] __attribute__((aligned(16)));

    o = s->obj;
    *(u128 *)&s->x = *v;
    p = (s8 *)o + 0x60;
    if (p[0xE] != 0) {
        s->y = s->x;
        s->z = s->x;
    }
    b = s->b;
    a = s->a;
    if (b == 0) {
        b = s->c;
    }
    if (b == 0 && a == 0) {
        return;
    }
    switch (p[0xC]) {
    case 1:
        s->w = 1.0f;
        if (p[0xF] != 0) {
            NodeGetTranslation_186650(s->obj, m);
            VecAddInPlace_13e070(m, &s->x);
            if (a != 0) {
                FrameSetPos_14a450(a, m);
            } else {
                NodeSetTranslation_1866b0(b, m);
            }
        } else {
            if (a != 0) {
                FrameSetPos_14a450(a, &s->x);
            } else {
                NodeSetTranslation_1866b0(b, &s->x);
            }
        }
        break;
    case 2:
        if (s->x > (f32)360000) {
            s->x = s->x - (f32)360000;
        }
        if (s->x < (f32)-360000) {
            s->x = s->x + (f32)360000;
        }
        if (s->y > (f32)360000) {
            s->y = s->y - (f32)360000;
        }
        if (s->y < (f32)-360000) {
            s->y = s->y + (f32)360000;
        }
        if (s->z > (f32)360000) {
            s->z = s->z - (f32)360000;
        }
        if (s->z < (f32)-360000) {
            s->z = s->z + (f32)360000;
        }
        s->x = WrapAngle_13c050(D_0047D1FC * s->x / 180.0f);
        s->y = WrapAngle_13c050(D_0047D1FC * s->y / 180.0f);
        s->z = WrapAngle_13c050(D_0047D1FC * s->z / 180.0f);
        s->w = 0.0f;
        if (a != 0) {
            FrameSetRot_14a390(a, &s->x);
        } else {
            NodeSetRotation_186620(b, &s->x);
        }
        break;
    case 3:
        s->w = 0.0f;
        if (a != 0) {
            FrameSetScale_14a2c0(a, &s->x);
        } else {
            NodeSetScale_1865b0(b, &s->x);
        }
        break;
    case 4:
        if (a != 0) {
            q = *(u8 **)(a + 0x20);
            if (q != 0) {
                *(s32 *)(q + 0x0) = 1;
                *(f32 *)(q + 0x10) = s->x;
                *(f32 *)(q + 0x14) = s->y;
                *(f32 *)(q + 0x18) = s->z;
                *(f32 *)(q + 0x1C) = 128.0f;
            }
        }
        break;
    case 5:
        if (a != 0) {
            *(s16 *)(a + 0x2E) = (s32)(16384.0f * s->x);
        } else {
            *(f32 *)(b + 0x64) = s->x;
        }
        break;
    }
}
