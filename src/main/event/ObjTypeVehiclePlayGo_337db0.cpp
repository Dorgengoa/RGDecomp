#include "types.h"

/* jalr $25 is C++ VIRTUAL DISPATCH: the vptr lands at +0xDC, so the class
   carries 0xDC bytes of data before its first virtual and the rest after.
   Slot 0x10 = 8 + 4*2 -> the third declared virtual. */
struct Self {
    u8   pad000[0xD0];
    u32  mD0;
    u8   pad0D4[0x8];
    virtual void v0();
    virtual void v1();
    virtual void v2(s32 k);
    u8   pad0E0[0x120 - 0xE0];
    char m120[0x10];
    s16  m130;
    s16  m132;
};

extern "C" const char D_004625E0[];
extern "C" char *strcpy(char *d, const char *s);
extern "C" s32   ObjTypeVehicleSetPathToMapNode_337ec0(void);
extern "C" void *GetCurrentScene_1f5be0(void);
extern "C" void  GameSceneSoundEnvApplyPreset_1d0e30(void *q, s32 a, s32 b, s32 c);
extern "C" void  GameSceneSoundEnvSetLock_1d11a0(void *q, s32 a);

extern "C" s32 ObjTypeVehiclePlayGo_337db0(Self *self, s32 a2, s32 a3, s32 a4)
{
    bool  busy;
    void *q;

    busy = !(self->mD0 & 0x80000000);
    if (!busy) {
        return 0;
    }
    if (ObjTypeVehicleSetPathToMapNode_337ec0() == 0) {
        return 0;
    }
    self->m132 = 0;
    strcpy(self->m120, D_004625E0);
    self->m130 = 1;
    self->v2(0);
    if (a4 >= 0) {
        q = GetCurrentScene_1f5be0();
        GameSceneSoundEnvApplyPreset_1d0e30(q, a4, 0, 0);
        GameSceneSoundEnvSetLock_1d11a0(q, 1);
    }
    return 1;
}
