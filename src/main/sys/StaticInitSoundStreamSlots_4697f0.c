#include "types.h"

extern const u8 D_004A25F0[];
extern s32 D_004814E0;
extern void SoundStreamSlotCtor_1bf720(void);
extern void SoundStreamSlotDtor_1bf6c0(void);
extern void SoundStreamSlotsDtor_1bf6a0(void);
extern void ConstructArray_100620(const u8 *a, void *b, void *c, s32 d, s32 e);
extern void RegisterGlobalObject_100dc0(s32 a, void *b, s32 *c);

void StaticInitSoundStreamSlots_4697f0(void)
{
    ConstructArray_100620(D_004A25F0, (void *)SoundStreamSlotCtor_1bf720, (void *)SoundStreamSlotDtor_1bf6c0, 0x128, 4);
    RegisterGlobalObject_100dc0(0, (void *)SoundStreamSlotsDtor_1bf6a0, &D_004814E0);
}
