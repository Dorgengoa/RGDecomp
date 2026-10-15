#include "types.h"

typedef struct Obj_FUN_001d1ea0 {
    u8 pad000[0xC];
    s32 f0C;
    s32 f10;
    u8 pad014[0x4];
    s32 f18;
    u8 pad01C[0x14];
    u8 f30;
} Obj_FUN_001d1ea0;

typedef struct T_FUN_001d1ea0 T_FUN_001d1ea0;

extern T_FUN_001d1ea0 *SoundSlotGetBankId_1d2130(void);
extern void SoundBankRelease_1bb6e0(T_FUN_001d1ea0 *t);
extern void MemStackReset_14d830(void *p);
extern s32 SoundSlotLoadBank_1d1f20(Obj_FUN_001d1ea0 *o, s32 v);
extern void LoaderReleaseHandle_1ccb70(Obj_FUN_001d1ea0 *o);

s32 SoundSlotStartLoaded_1d1ea0(Obj_FUN_001d1ea0 *o, s32 v)
{
    if (o->f0C < 0) {
        return -1;
    }
    SoundBankRelease_1bb6e0(SoundSlotGetBankId_1d2130());
    MemStackReset_14d830(&o->f30);
    o->f10 = o->f0C;
    o->f18 = SoundSlotLoadBank_1d1f20(o, v);
    LoaderReleaseHandle_1ccb70(o);
    o->f0C = -1;
    return o->f18;
}
