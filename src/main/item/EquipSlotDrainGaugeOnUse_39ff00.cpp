#include "types.h"

class V39ff00 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual s32 alive();
    u8 pad4[0xC];
    f32 unk10;
};

typedef struct { u8 pad[0x24C]; u8 lo:4; u8 b4:1; } H39ff00;
typedef struct { u8 pad[0x20]; H39ff00 *h; } G39ff00;

extern "C" {
extern s32 EquipSlotGetGaugeUseCost_3a0260(V39ff00 *);
extern G39ff00 *D_00483748;
}

extern "C" s32 EquipSlotDrainGaugeOnUse_39ff00(V39ff00 *self)
{
    f32 t;

    if (self->alive() == 0) {
        return 0;
    }
    if (self->unk10 <= 0.0f) {
        return 0;
    }
    if (D_00483748->h->b4) {
        return 0;
    }
    t = self->unk10 - (f32)EquipSlotGetGaugeUseCost_3a0260(self);
    self->unk10 = t;
    return (s32)t;
}
