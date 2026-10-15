#include "types.h"

typedef struct T329460 {
    u8  pad000[0x40];
    f32 f40;
    f32 f44;
    f32 f48;
    u8  pad4C[0x11A - 0x4C];
    s8  f11A;
    u8  pad11B[0x170 - 0x11B];
    void *f170;
    void *f174;
} T329460;

extern s32 IsWidescreen_1c6ab0(T329460 *);
extern f32 MinimapGetDrawAlpha_32a180(T329460 *);
extern void MinimapSetAspectScale_324c60(T329460 *, f32);
extern void MinimapDrawEntry_325720(T329460 *, void *, f32 *, f32, s32);

void MinimapDrawEntries_329460(T329460 *self, f32 *p, f32 t)
{
    f32 s;
    void *q;

    if (self->f11A == 0) {
        return;
    }
    s = 1.0f;
    if (IsWidescreen_1c6ab0(self) != 0) {
        s = s * 0.75f;
    }
    if (MinimapGetDrawAlpha_32a180(self) <= 0.0f) {
        return;
    }
    MinimapSetAspectScale_324c60(self, s);
    {
        f32 v[4] = {0};

        v[0] = p[0] + self->f40;
        v[1] = p[1] + self->f44;
        v[2] = p[2] + self->f48;
        q = self->f170;
        if (q != 0) {
            MinimapDrawEntry_325720(self, q, v, t, 0);
        }
        q = self->f174;
        if (q != 0) {
            MinimapDrawEntry_325720(self, q, v, t, 1);
        }
    }
}
