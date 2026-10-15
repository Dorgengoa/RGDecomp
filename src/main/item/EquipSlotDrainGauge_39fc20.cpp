#include "types.h"

class VB {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual s32 fC0();
};

class VA0 {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual VB *f40();
};

class VA : public VA0 {
public:
    u8 pad4[0xC];
    f32 m10;
};

extern "C" f32 EquipSlotGetGaugeDrainRate_3a0290(VA *);
extern u8 *D_00483748;
extern u8 *D_00483754;

extern "C" s32 EquipSlotDrainGauge_39fc20(VA *arg0, f32 fparg0) {
    VB *b;
    f32 v;
    f32 t;

    if (D_00483748 == NULL) {
        return 0;
    }
    if (!(*(u8 *)(*(u8 **)(D_00483748 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    b = arg0->f40();
    if ((b != NULL) && (b->fC0() != 0)) {
        return 0;
    }
    if (!(arg0->m10 <= 0.0f) && (((u64) ((s64) (*(u8 *)(D_00483754 + 0x24C)) << 0x3B) >> 0x3F) == 0)) {
        t = fparg0 * EquipSlotGetGaugeDrainRate_3a0290(arg0);
        arg0->m10 -= t;
        if (arg0->m10 < 0.0f) {
            arg0->m10 = 0.0f;
        }
    }
    return 1;
}
