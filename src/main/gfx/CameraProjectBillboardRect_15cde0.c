#include "types.h"

typedef unsigned __int128 u128;

typedef union {
    u128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
} Vec4;

typedef struct {
    u8 pad0[0xC];
    f32 near;
    f32 far;
} Range;

typedef struct {
    u8 pad0[0x14];
    Range range;
    u8 pad28[0x1C0 - 0x28];
    u8 mtx[0x40];
    f32 m200;
    u8 pad204[0x10];
    f32 m214;
} Cam;

typedef struct {
    u8 pad0[0xF20];
    Cam *cam;
} Scene;

extern void MtxMulPoint_13c890(Vec4 *, void *);
extern Scene *D_004810A4;

static inline Cam *get_cam(void) {
    if (D_004810A4 == 0) {
        return 0;
    }
    return D_004810A4->cam;
}

static inline s32 in_view(f32 *p, Cam *c) {
    Range *r = &c->range;
    s32 lim = 0xFFF;
    if (p[0] < 0.0f || !(p[0] <= (f32)lim)) {
        return 0;
    }
    if (p[1] < 0.0f || !(p[1] <= (f32)lim)) {
        return 0;
    }
    if (p[3] < r->near || !(p[3] <= r->far)) {
        return 0;
    }
    return 1;
}

s32 CameraProjectBillboardRect_15cde0(s32 *out0, s32 *out1, f32 w, f32 h) {
    Cam *c;
    f32 sx;
    f32 sy;
    f32 inv;
    f32 hw;
    f32 hh;
    Vec4 a;
    Vec4 b;
    Vec4 v;
    s32 r0;
    s32 r1;

    c = get_cam();
    sx = w * c->m200;
    sy = -h * c->m214;
    MtxMulPoint_13c890(&v, c->mtx);
    if (v.f.w < 1.0f) {
        return 0;
    }
    inv = 1.0f / v.f.w;
    v.f.x *= inv;
    v.f.y *= inv;
    v.f.z *= inv;
    a.q = v.q;
    b.q = v.q;
    hw = sx * inv;
    hh = sy * inv;
    hw = 0.5f * (f32)hw;
    a.f.x -= hw;
    hh = 0.5f * (f32)hh;
    a.f.y -= hh;
    b.f.x += hw;
    b.f.y += hh;
    out0[0] = 16.0f * a.f.x;
    out0[1] = 16.0f * a.f.y;
    out0[2] = a.f.z;
    out0[3] = 0;
    out1[0] = 16.0f * b.f.x;
    out1[1] = 16.0f * b.f.y;
    out1[2] = b.f.z;
    out1[3] = 0;
    c = get_cam();
    r0 = in_view((f32 *)&a, c);
    c = get_cam();
    r1 = in_view((f32 *)&b, c);
    return r0 & r1;
}
