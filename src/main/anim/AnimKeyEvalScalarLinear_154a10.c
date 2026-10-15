#include "types.h"
#include "libvu0.h"

#pragma vu0_mmi_reg_binding on

typedef unsigned __int128 u128_154a10;

extern u128_154a10 v4_154a10 asm("vf4");
extern u128_154a10 v5_154a10 asm("vf5");
extern u128_154a10 v6_154a10 asm("vf6");
extern u128_154a10 v7_154a10 asm("vf7");
extern u128_154a10 v8_154a10 asm("vf8");
extern u128_154a10 acc_154a10 asm("ACC");

/* d = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void InterVector_154a10(void *d, void *p1, void *p2, f32 t)
{
    u128_154a10 *b = (u128_154a10 *)(s32)p2;
    u128_154a10 *a = (u128_154a10 *)(s32)p1;

    if (b) {
        b = (u128_154a10 *)(s32)(u32)b;
    }
    v4_154a10 = *b;
    v5_154a10 = *a;
    Vu0ScaleF(t0, t, vf6);
    v7_154a10 = _vsub(v7_154a10, 0xF, v5_154a10, v4_154a10);
    Vu0InterVectorAcc();
    v8_154a10 = _vmaddbc(v8_154a10, 0xF, acc_154a10, v7_154a10, v6_154a10, 8);
    *(u128_154a10 *)d = v8_154a10;
}

typedef struct V4_154a10 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4_154a10;

typedef struct Chan154a10 {
    u8 b0;
    u8 fmt;
    u8 b2;
    u8 b3;
    s16 h4;
    u16 h6;
    s32 w8;
    void *data;
    f32 scale;
} Chan154a10;

typedef struct Key154a10 {
    f32 time;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 i0;
    s32 i1;
    s32 pad1C[3];
} Key154a10;

extern f32 AnimKeyFindSpan_155ff0(Key154a10 *k);

void AnimKeyEvalScalarLinear_154a10(f32 *out, Chan154a10 *ch, f32 time)
{
    Key154a10 k;
    V4_154a10 a8;
    V4_154a10 b8;
    V4_154a10 af;
    V4_154a10 bf;
    V4_154a10 as;
    V4_154a10 bs;
    f32 t;
    f32 v;

    k.a = ch->b2;
    k.b = ch->w8;
    k.d = ch->h6;
    k.time = time;
    k.c = ch->h4;
    t = AnimKeyFindSpan_155ff0(&k);
    if (ch->fmt == 8) {
        s8 *d8 = ch->data;
        if (t == 0.0f) {
            v = (1.0f / 128.0f) * d8[k.i0];
            *out = v * ch->scale;
        } else {
            v = (1.0f / 128.0f) * d8[k.i0];
            a8.x = v * ch->scale;
            v = (1.0f / 128.0f) * d8[k.i1];
            b8.x = v * ch->scale;
            InterVector_154a10(out, &b8, &a8, t);
        }
    } else if (ch->fmt == 0x20) {
        f32 *df = ch->data;
        if (t == 0.0f) {
            *out = df[k.i0];
        } else {
            af.x = df[k.i0];
            bf.x = df[k.i1];
            InterVector_154a10(out, &bf, &af, t);
        }
    } else if (ch->fmt == 0x10) {
        s16 *ds = ch->data;
        if (t == 0.0f) {
            v = (1.0f / 32768.0f) * ds[k.i0];
            *out = v * ch->scale;
        } else {
            v = (1.0f / 32768.0f) * ds[k.i0];
            as.x = v * ch->scale;
            v = (1.0f / 32768.0f) * ds[k.i1];
            bs.x = v * ch->scale;
            InterVector_154a10(out, &bs, &as, t);
        }
    }
}
