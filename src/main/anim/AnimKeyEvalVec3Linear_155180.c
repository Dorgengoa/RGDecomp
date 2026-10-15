#include "types.h"
#include "libvu0.h"

#pragma vu0_mmi_reg_binding on

typedef unsigned __int128 u128_155180;

extern u128_155180 v4_155180 asm("vf4");
extern u128_155180 v5_155180 asm("vf5");
extern u128_155180 v6_155180 asm("vf6");
extern u128_155180 v7_155180 asm("vf7");
extern u128_155180 v8_155180 asm("vf8");
extern u128_155180 acc_155180 asm("ACC");

/* d = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void InterVector_155180(void *d, void *p1, void *p2, f32 t)
{
    u128_155180 *b = (u128_155180 *)(s32)p2;
    u128_155180 *a = (u128_155180 *)(s32)p1;

    if (b) {
        b = (u128_155180 *)(s32)(u32)b;
    }
    v4_155180 = *b;
    v5_155180 = *a;
    Vu0ScaleF(t0, t, vf6);
    v7_155180 = _vsub(v7_155180, 0xF, v5_155180, v4_155180);
    Vu0InterVectorAcc();
    v8_155180 = _vmaddbc(v8_155180, 0xF, acc_155180, v7_155180, v6_155180, 8);
    *(u128_155180 *)d = v8_155180;
}

typedef struct V4_155180 {
    f32 x[4];
} __attribute__((aligned(16))) V4_155180;

typedef struct Chan155180 {
    u8 b0;
    u8 fmt;
    u8 b2;
    u8 b3;
    s16 h4;
    u16 h6;
    s32 w8;
    void *data;
    f32 scale[3];
} Chan155180;

typedef struct Key155180 {
    f32 time;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 i0;
    s32 i1;
    s32 pad1C[3];
} Key155180;

extern f32 AnimKeyFindSpan_155ff0(Key155180 *k);

void AnimKeyEvalVec3Linear_155180(f32 *out, Chan155180 *ch, f32 time)
{
    Key155180 k;
    V4_155180 a16;
    V4_155180 b16;
    V4_155180 a8;
    V4_155180 b8;
    V4_155180 af;
    V4_155180 bf;
    f32 t;
    f32 v;
    s32 i;

    k.a = ch->b2;
    k.b = ch->w8;
    k.d = ch->h6;
    k.time = time;
    k.c = ch->h4;
    t = AnimKeyFindSpan_155ff0(&k);
    if (ch->fmt == 0x10) {
        s16 *d16 = ch->data;
        if (t == 0.0f) {
            s16 *p = &d16[k.i0 * 3];
            v = (1.0f / 32768.0f) * p[0];
            out[0] = v * ch->scale[0];
            v = (1.0f / 32768.0f) * p[1];
            out[1] = v * ch->scale[1];
            v = (1.0f / 32768.0f) * p[2];
            out[2] = v * ch->scale[2];
        } else {
            s16 *p0 = &d16[k.i0 * 3];
            s16 *p1 = &d16[k.i1 * 3];
            v = (1.0f / 32768.0f) * p0[0];
            a16.x[0] = v * ch->scale[0];
            v = (1.0f / 32768.0f) * p0[1];
            a16.x[1] = v * ch->scale[1];
            v = (1.0f / 32768.0f) * p0[2];
            a16.x[2] = v * ch->scale[2];
            v = (1.0f / 32768.0f) * p1[0];
            b16.x[0] = v * ch->scale[0];
            v = (1.0f / 32768.0f) * p1[1];
            b16.x[1] = v * ch->scale[1];
            v = (1.0f / 32768.0f) * p1[2];
            b16.x[2] = v * ch->scale[2];
            InterVector_155180(out, &b16, &a16, t);
        }
    } else if (ch->fmt == 8) {
        s8 *d8 = ch->data;
        if (t == 0.0f) {
            s8 *p = &d8[k.i0 * 3];
            for (i = 0; i < 3; i++) {
                v = (1.0f / 128.0f) * p[i];
                out[i] = v * ch->scale[i];
            }
        } else {
            s8 *p0 = &d8[k.i0 * 3];
            s8 *p1 = &d8[k.i1 * 3];
            for (i = 0; i < 3; i++) {
                v = (1.0f / 128.0f) * p0[i];
                a8.x[i] = v * ch->scale[i];
            }
            for (i = 0; i < 3; i++) {
                v = (1.0f / 128.0f) * p1[i];
                b8.x[i] = v * ch->scale[i];
            }
            InterVector_155180(out, &b8, &a8, t);
        }
    } else if (ch->fmt == 0x20) {
        f32 *df = ch->data;
        if (t == 0.0f) {
            f32 *p = &df[k.i0 * 3];
            out[0] = p[0];
            out[1] = p[1];
            out[2] = p[2];
        } else {
            f32 *p0 = &df[k.i0 * 3];
            f32 *p1 = &df[k.i1 * 3];
            af.x[0] = p0[0];
            af.x[1] = p0[1];
            af.x[2] = p0[2];
            bf.x[0] = p1[0];
            bf.x[1] = p1[1];
            bf.x[2] = p1[2];
            InterVector_155180(out, &bf, &af, t);
        }
    }
}
