#include "types.h"

class Sub {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f74(f32 a0) { VCM(void, (void *, f32), 0x74, a0); }
    u8 pad4[0x24 - 4];
};

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f2B0(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x2B0, a0, a1, a2); }
    u8 pad4[0x1EC - 4];
    f32 m1EC;
    u8 pad1F0[0x234 - 0x1F0];
    u8 *m234;
    u8 pad238[0x278 - 0x238];
    Sub m278[8];
    u8 pad398[0x40C - 0x398];
    f32 m40C;
};

extern "C" {
extern s32 UnitBaseUpdate_3b0bf0(Obj *, f32);
extern s32 CharaSysHasEncounterRecMaybe_3a3950(u8 *);
extern s32 CharaSysStateFlag24Bit2Related_3a3880(u8 *);
extern f32 RandFloat_13c010(void);
extern u8 D_0045B078[0x400];
extern u8 *D_00483818;
}

extern "C" s32 UnitUpdate_3bc770(Obj *self, f32 dt) {
    s32 i;
    f32 lim;
    f32 k;
    f32 w;
    u8 *e;

    if (D_00483818 == NULL) {
        return 0;
    }
    if (!(*(*(u8 **)(D_00483818 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (self->fC0() != 0) {
        return 0;
    }
    if (!(UnitBaseUpdate_3b0bf0(self, dt) & 0xFF)) {
        return 0;
    }
    i = 0;
    do {
        self->m278[i].f74(dt);
        i++;
    } while (i < 8);
    if (self->m234 != NULL) {
        k = *(f32 *)D_0045B078;
        lim = self->m1EC / k / 2.0f;
        if (CharaSysHasEncounterRecMaybe_3a3950(*(u8 **)(D_00483818 + 0x20)) == 0 || CharaSysStateFlag24Bit2Related_3a3880(*(u8 **)(D_00483818 + 0x20)) != 0) {
            w = (f32)*(s16 *)(self->m234 + 0x8C);
            if (!(w <= 0.0f) && !((f32)*(s16 *)(self->m234 + 0x8E) <= 0.0f) && !(w <= 0.0f) && !(lim < w) &&
                !(dt <= k * RandFloat_13c010())) {
                k = 60.0f - 60.0f * ((f32)*(s16 *)(self->m234 + 0x8E) / 100.0f);
                if (!(1.0f <= k * RandFloat_13c010())) {
                    self->f2B0(0, 1, 0);
                }
            }
        }
    }
    w = self->m40C;
    if (!(w <= 0.0f)) {
        w = w - dt;
        self->m40C = w;
        if (w < 0.0f) {
            self->m40C = 0.0f;
        }
    }
    return 1;
}
