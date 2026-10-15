#include "types.h"
#pragma optimization_level 3
#pragma opt_propagation off

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) do { *p_ = 0; n_--; p_++; } while (n_); }

typedef struct V3 { f32 x, y, z, w; } V3;
typedef struct Rect { f32 x0, z0, x1, z1; } Rect;
typedef struct Pos { f32 x, y, z; } Pos;
typedef struct Obj {
    u8 pad0[0x20];
    f32 m20;
    u8 pad24[4];
    f32 m28;
    u8 pad2C[0x24];
    f32 m50;
    f32 m54;
    f32 m58;
    u8 pad5C[0xC0];
    s8 m11C;
    u8 pad11D[0x53];
    void *m170;
    void *m174;
} Obj;

extern void FUN_00323ad0_dummy(void);
extern s32 EntryGetTileSize_323ad0(void *);
extern f32 EntryGetScale_323b30(void *);
extern void EntryGetGridSize_323bb0(void *, s32 *, s32 *);
extern void MinimapGetEntryGridOrigin_323e40(Obj *, void *, f32 *, f32 *);
extern s32 AngleToQuadrant_323fd0(Obj *);
extern void MinimapSetScrollStep_3244a0(Obj *, s32, s32);

s32 MinimapScrollToClamped_324530(Obj *self, Pos *pos, s32 n, s32 arg3)
{
    V3 cur;
    Rect r;
    s32 w;
    s32 h;
    f32 x;
    f32 z;
    s32 t;
    void *a;
    f32 sc;
    f32 cnt;
    s32 ret;
    f32 s;
    f32 fw;
    f32 fh;
    f32 x2;
    f32 z2;

    ret = 0;
    ZERO16(&cur);
    cur.x = pos->x;
    a = self->m170;
    cur.y = pos->y;
    cur.z = pos->z;
    if (a == 0) {
        a = self->m174;
    }
    if (a == 0) {
        return 0;
    }
    MinimapGetEntryGridOrigin_323e40(self, a, &x, &z);
    EntryGetGridSize_323bb0(a, &w, &h);
    sc = EntryGetScale_323b30(a);
    cnt = EntryGetTileSize_323ad0(a);
    switch (AngleToQuadrant_323fd0(self)) {
    case 0:
    case 2:
        break;
    case 1:
    case 3:
        t = w;
        w = h;
        h = t;
        break;
    }
    s = cnt * sc;
    fw = (f32)w * s;
    fh = (f32)h * s;
    x += self->m20;
    x2 = fw + x;
    z += self->m28;
    z2 = fh + z;
    ZERO16(&r);
    r.z1 = z2;
    r.x1 = x2;
    r.x0 = x;
    r.z0 = z;
    if (self->m11C == 2) {
        if (pos->x < r.x0 || r.x1 < pos->x) {
            if (pos->x < r.x0) {
                pos->x = 1.0f + r.x0;
            } else if (r.x1 < pos->x) {
                pos->x = 1.0f + r.x1;
            }
            ret = 1;
        }
        if (pos->z < r.z0 || r.z1 < pos->z) {
            if (pos->z < r.z0) {
                pos->z = 1.0f + r.z0;
            } else if (r.z1 < pos->z) {
                pos->z = 1.0f + r.z1;
            }
            ret = 2;
        }
    }
    cur.x = pos->x;
    cur.y = pos->y;
    cur.z = pos->z;
    switch (ret) {
    case 0:
        self->m50 = cur.x;
        ret = 1;
        self->m54 = cur.y;
        self->m58 = cur.z;
        break;
    case 1:
        self->m50 = cur.x;
        ret = 0;
        self->m54 = cur.y;
        self->m58 = cur.z;
        break;
    case 2:
        self->m50 = cur.x;
        ret = 0;
        self->m54 = cur.y;
        self->m58 = cur.z;
        break;
    }
    if (n <= 0) {
        n = 1;
    }
    if (n > 0) {
        MinimapSetScrollStep_3244a0(self, n, arg3);
    }
    return ret;
}
