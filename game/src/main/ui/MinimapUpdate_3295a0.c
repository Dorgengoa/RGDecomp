/* rgp:protos */
#define RGP_SELF_MinimapUpdate_3295a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 { f32 x, y, z, w; } Vec4;
typedef struct Obj {
    u8 pad0[0x40];
    f32 x40;
    f32 x44;
    f32 x48;
    u8 pad4C[0x12C - 0x4C];
    u8 list[0x160 - 0x12C];
    f32 f160;
    f32 f164;
    f32 f168;
    f32 f16C;
    u8 *e170;
    u8 *e174;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B078[];
extern f32 D_0047D858;
extern f32 D_00482B9C;

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_ != NULL) { while (n_ != 0) { *p_ = 0; n_--; p_++; } } }

void MinimapUpdate_3295a0(Obj *self, Vec4 *pos) {
    Vec4 v __attribute__((aligned(16)));
    s32 n;
    s32 i;
    s16 key;
    u8 *e;
    f32 dt;
    f32 h;
    f32 lim;
    f32 f;
    f32 r;

    if (self->e170 == NULL && self->e174 == NULL) {
        MinimapRequestEntry_32ab90(self, ((u8 *)EntryListSelectByIndex_323540(self->list, 0)));
    }
    MinimapScrollStep_3243f0(self);
    MinimapFadeUpdate_32a0f0(self, MinimapGetFadeDuration_32a160(self));
    MinimapCrossfadeUpdate_32a950(self);
    dt = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    if (DrawEnvGetVsyncInterval_144130(GetDrawCtx_15de80()) == 1) {
        dt /= 2.0f;
    }
    h = 0.5f * D_0045B078[0];
    lim = h + 0.5f * (f32)D_0045B078[0];
    self->f160 += dt;
    if (self->f160 > lim) {
        self->f160 -= lim;
    }
    if (self->f160 < h) {
        r = D_0047D858 / h;
        self->f164 = (1.0f + Cosf_128d30(r * self->f160)) / 2.0f;
    } else {
        self->f164 = 1.0f;
    }
    self->f168 += 0.75f;
    if (self->f168 >= 360.0f) {
        self->f168 -= 360.0f;
    }
    self->f16C += dt;
    if (self->f16C >= D_00482B9C) {
        self->f16C -= D_00482B9C;
    }
    if (pos == NULL) return;
    ZERO(&v, 0x10);
    v.x = pos->x + self->x40;
    v.y = pos->y + self->x44;
    v.z = pos->z + self->x48;
    switch (((short)EntryListGetKind_323690(self->list))) {
    case 2:
        if (self->e170 != NULL) {
            n = ((short)EntryListGetCount_323680(self->list));
            key = EntryGetGroupId_3238d0(self->e170);
            for (i = 0; i < n; i++) {
                e = ((u8 *)EntryListSelectByIndex_323540(self->list, i));
                if (e == NULL) continue;
                if (key == EntryGetGroupId_3238d0(e)) {
                    MinimapRevealAround_329940(self, e, &v, 0);
                }
            }
        }
        if (self->e174 != NULL) {
            n = ((short)EntryListGetCount_323680(self->list));
            key = EntryGetGroupId_3238d0(self->e174);
            for (i = 0; i < n; i++) {
                e = ((u8 *)EntryListSelectByIndex_323540(self->list, i));
                if (e == NULL) continue;
                if (key == EntryGetGroupId_3238d0(e)) {
                    MinimapRevealAround_329940(self, e, &v, 1);
                }
            }
        }
        break;
    default:
        if (self->e170 != NULL) {
            MinimapRevealAround_329940(self, self->e170, &v, 0);
        }
        if (self->e174 != NULL) {
            MinimapRevealAround_329940(self, self->e174, &v, 1);
        }
        break;
    }
}
