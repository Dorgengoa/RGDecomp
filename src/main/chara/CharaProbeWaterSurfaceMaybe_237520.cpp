#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;

struct Rec {
    s32 w[12];      /* 00 */
    Vec v;          /* 30 */
    s16 h[10];      /* 40 */
    s32 i;          /* 54 */
};

struct Elem {
    Rec r;
    u8 pad58[8];
};

struct Owner { u8 pad[0x4CC]; f32 f4CC; };

struct Self {
    u8 pad0[0x50];
    u8 m50[0x24];       /* 50 */
    f32 f74;            /* 74 */
    u8 pad78[0x1D0 - 0x78];
    Rec rec;            /* 1D0 */
    u8 pad228[0x3D0 - 0x228];
    u64 fl;             /* 3D0 */
    u32 i3D8;           /* 3D8 */
    u8 pad3DC[0x3E4 - 0x3DC];
    f32 f3E4;           /* 3E4 */
    f32 f3E8;           /* 3E8 */
    u8 pad3EC[4];
    f32 f3F0;           /* 3F0 */
    Owner *p3F4;        /* 3F4 */
    u8 pad3F8[0x40E - 0x3F8];
    s16 s40E;           /* 40E */
    u8 pad410[2];
    s16 s412;           /* 412 */
};

extern "C" {
void SrtGetPos_1c7430(void *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
f32 CollRayTriTest_1c8ce0(Elem *, void *, void *, Vec *, Vec *);
s32 CollTriIsWaterMaybe_1ce5c0(Elem *);
s32 ModelFindFrameIndexByName_151220(Owner *, s32);
void *ModelGetFrame_1511f0(Owner *, s32);
void FrameGetWorldPos_148f30(void *, Vec *);
}
extern f32 D_0045B080[];
extern f32 D_0047DAB4;
extern f32 D_0047DB14;

static inline f32 radius(Self *self, f32 s) {
    if (self->p3F4 != 0) return self->p3F4->f4CC * (D_0047DB14 * s);
    return 0.0f;
}

static inline bool ownerPos(Owner *o, s32 id, Vec *out) {
    void *x;
    if (o == 0 || id == 0) return false;
    x = ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, id));
    if (x == 0) return false;
    FrameGetWorldPos_148f30(x, out);
    return true;
}

extern "C" void CharaProbeWaterSurfaceMaybe_237520(Self *self, Elem *arr, s32 n, s32 id) {
    Vec vC0;
    Vec vB0;
    Vec vA0;
    Vec v90;
    f32 lim;
    f32 bt2;
    f32 t;
    f32 r;
    f32 s;
    f32 best_t;
    f32 minr;
    s32 best;
    Elem *p;
    s32 i;

    self->s412 = 0;
    self->i3D8 &= ~0x10;
    if (self->fl & 0x800000000000ULL) return;
    if (self->p3F4 == 0) return;
    if (arr == 0 || n <= 0) return;
    SrtGetPos_1c7430(self->m50, &vC0);
    SrtGetPos_1c7430(self->m50, &vB0);
    vB0.y = vB0.y + 500.0f * (s = D_0045B080[0]);
    VecSub_1cbd00(&vA0, &vB0, &vC0);
    minr = D_0047DAB4 * s;
    r = radius(self, s);
    r = (r > minr) ? r : minr;
    lim = vC0.y + r;
    best_t = 1.0f;
    best = -1;
    p = arr;
    for (i = 0; i < n; i++, p++) {
        if (p->r.h[3] & self->s40E) continue;
        t = CollRayTriTest_1c8ce0(p, &p->r.w[4], &p->r.w[8], &vC0, &vA0);
        if (!(best_t <= t) && !(vC0.y + vA0.y * t <= lim)) {
            best_t = t;
            best = i;
        }
    }
    if (best < 0) best_t = 1.0f;
    bt2 = 0.0f;
    best = -1;
    p = arr;
    for (i = 0; i < n; i++, p++) {
        if (CollTriIsWaterMaybe_1ce5c0(p) == 0) continue;
        t = CollRayTriTest_1c8ce0(p, &p->r.w[4], &p->r.w[8], &vC0, &vA0);
        if (!(t <= bt2) && !(best_t <= t)) {
            bt2 = t;
            best = i;
        }
    }
    if (best >= 0) {
        self->f3F0 = vC0.y + vA0.y * bt2;
        self->i3D8 |= 0x10;
        self->rec = arr[best].r;
        self->f3E4 = vC0.y + vA0.y * bt2 - self->f74;
    }
    if (!ownerPos(self->p3F4, id, &v90)) {
        SrtGetPos_1c7430(self->m50, &v90);
        r = radius(self, s);
        r = (r > minr) ? r : minr;
        v90.y = v90.y + 0.5f * r;
    }
    self->f3E8 = v90.y - self->f74;
    if ((self->i3D8 & 0x20) && !(self->fl & 0x800000000000ULL) && self->f3E8 < self->f3E4) {
        self->s412 = 1;
    }
}
