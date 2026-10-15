#include "types.h"
typedef unsigned __int128 u128;

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} __attribute__((aligned(16))) Vec4;

typedef struct Tri {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 n;
    u8 pad40[0x20];
} Tri;

typedef struct Mesh {
    s32 count;
    Tri *tris;
    s32 c;
    s32 d;
} Mesh;

extern const f32 D_0047D448 __attribute__((section(".sdata")));
extern s32 MeshRaycastTris_16f3c0(Mesh *, Vec4 *, Vec4 *, Vec4 *, s32, s32);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);

static inline s32 Cast(Tri *tris, s32 count, Vec4 *p0, Vec4 *p1, Vec4 *out, s32 nearest, s32 mask)
{
    Mesh m;

    m.count = count;
    m.tris = tris;
    m.c = 0;
    m.d = 0;
    return MeshRaycastTris_16f3c0(&m, p0, p1, out, nearest, mask);
}

s32 CollPushOutWallsMaybe_16d730(Tri *tris, s32 count, Vec4 *in, Vec4 *out, s32 mask, f32 r, f32 lim)
{
    Vec4 pt;
    Vec4 a;
    Vec4 b;
    Vec4 cur;
    Vec4 n;
    f32 h;
    s32 fa;
    s32 bits = 0;
    s32 fb;
    s32 k;

    fb = 0;
    fa = 0;
    h = r / D_0047D448;
    *(u128 *)&cur = *(u128 *)in;
    *out = *in;

    pt.x = cur.x + h;
    pt.y = (f32)cur.y;
    pt.z = cur.z + h;
    k = Cast(tris, count, &cur, &pt, &a, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            fa = 1;
            bits |= 5;
        }
    }
    pt.x = cur.x - h;
    pt.y = (f32)cur.y;
    pt.z = cur.z - h;
    k = Cast(tris, count, &cur, &pt, &b, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            bits |= 0xA;
            fb = 1;
        }
    }
    if (fa && fb) {
        out->x = 0.5f * (a.x + b.x);
        out->z = 0.5f * (a.z + b.z);
    } else {
        if (fa) {
            out->x = a.x - h;
            out->z = a.z - h;
        }
        if (fb) {
            out->x = b.x + h;
            out->z = b.z + h;
        }
    }

    *(u128 *)&cur = *(u128 *)out;
    fb = 0;
    fa = 0;
    pt.x = cur.x + h;
    pt.y = (f32)cur.y;
    pt.z = cur.z - h;
    k = Cast(tris, count, &cur, &pt, &a, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            fa = 1;
            bits |= 9;
        }
    }
    pt.x = cur.x - h;
    pt.y = (f32)cur.y;
    pt.z = cur.z + h;
    k = Cast(tris, count, &cur, &pt, &b, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            bits |= 6;
            fb = 1;
        }
    }
    if (fa && fb) {
        out->x = 0.5f * (a.x + b.x);
        out->z = 0.5f * (a.z + b.z);
    } else {
        if (fa) {
            out->x = a.x - h;
            out->z = a.z + h;
        }
        if (fb) {
            out->x = b.x + h;
            out->z = b.z - h;
        }
    }

    *(u128 *)&cur = *(u128 *)out;
    fb = 0;
    fa = 0;
    pt.x = cur.x + r;
    pt.y = (f32)cur.y;
    pt.z = (f32)cur.z;
    k = Cast(tris, count, &cur, &pt, &a, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            fa = 1;
            bits |= 1;
        }
    }
    pt.x = cur.x - r;
    pt.y = (f32)cur.y;
    pt.z = (f32)cur.z;
    k = Cast(tris, count, &cur, &pt, &b, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            bits |= 2;
            fb = 1;
        }
    }
    if (fa && fb) {
        out->x = 0.5f * (a.x + b.x);
    } else {
        if (fa) {
            out->x = a.x - r;
        }
        if (fb) {
            out->x = b.x + r;
        }
    }

    *(u128 *)&cur = *(u128 *)out;
    fb = 0;
    fa = 0;
    pt.x = (f32)cur.x;
    pt.y = (f32)cur.y;
    pt.z = cur.z + r;
    k = Cast(tris, count, &cur, &pt, &a, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            bits |= 4;
            fa = 1;
        }
    }
    pt.x = (f32)cur.x;
    pt.y = (f32)cur.y;
    pt.z = cur.z - r;
    k = Cast(tris, count, &cur, &pt, &b, 0, mask);
    if (k != -1) {
        VecNormalize_13bd90(&n, &tris[k].n);
        if (n.y < lim && !(n.y <= -lim)) {
            bits |= 8;
            fb = 1;
        }
    }
    if (fa && fb) {
        out->z = 0.5f * (a.z + b.z);
    } else {
        if (fa) {
            out->z = a.z - r;
        }
        if (fb) {
            out->z = b.z + r;
        }
    }
    return bits;
}
