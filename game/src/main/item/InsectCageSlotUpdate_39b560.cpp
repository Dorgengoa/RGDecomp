/* rgp:protos */
#line 1
#include "types.h"
extern "C" {
void ModelObjExCalcSoundVolPan_1b0780(void *, f32 *, f32 *);
void *GameSceneSoundSlot0GetHandle_1d07c0(void *);
s32 GetGameMode_1f59c0(void);
void *GetCurrentScene_1f5be0(void);
s32 InsectCageSlotGetState_39bb00(void *);
s32 CageRecCountTriggered_3d08c0(void *);
void SoundPlayScaledVolPan_1b9680(void *, s32, s32, f32, f32);
}

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(f32 x0) { VCM(void, (void *, f32), 0x44, x0); }
};

struct Obj {
    u8 pad[0x14];
    void *p14;
    VC_0 *p18;
    u8 pad1c[8];
    f32 f24;
    f32 f28;
    s32 f2c;
};

extern "C" void InsectCageSlotUpdate_39b560(Obj *self, f32 t)
{
    f32 x;
    f32 y;
    if (((short)InsectCageSlotGetState_39bb00(self)) == 2) {
        self->f24 = self->f24 + self->f28;
        if (self->f24 < 0.0f) {
            self->f24 = 0.0f;
            if (self->f28 < 0.0f) {
                self->f28 = 0.0f;
            }
        }
        if (!(self->f24 <= 1.0f)) {
            self->f24 = 1.0f;
            if (!(self->f28 <= 0.0f)) {
                self->f28 = 0.0f;
            }
        }
        *(f32 *)((u8 *)self->p18 + 0x448) = self->f24;
        if (self->p14 != 0 && CageRecCountTriggered_3d08c0(self->p14) > 0) {
            bool flag = true;
            if (GetGameMode_1f59c0() != 6) flag = false;
            if (self->f2c == 0 && flag) {
                ModelObjExCalcSoundVolPan_1b0780(self->p18, &x, &y);
                SoundPlayScaledVolPan_1b9680(GameSceneSoundSlot0GetHandle_1d07c0(GetCurrentScene_1f5be0()), 0x2D, 0, x, y);
            }
            self->f2c += (s32)(100.0f * t);
            if (self->f2c >= 5000) {
                self->f2c = 0;
            }
        } else {
            self->f2c = 0;
        }
        self->p18->f(t);
    }
}
