#include "types.h"

extern void ConstructArray_100620(void *, void *, void *, s32, s32);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void SoundStreamDtor_1bfc30(void);
extern void SoundStreamTableEntryCtor_1bfd10(void);
extern void SoundStreamTableDtor_1c2790(void);

extern void *D_00481518;
extern s32 D_004A3AC0[];
extern u8 D_004A3AC4[];
extern s16 D_004A3EE4[];

void StaticInitSoundStreamTable_469840(void)
{
    D_004A3AC0[0] = 8;
    ConstructArray_100620(D_004A3AC4, (void *)SoundStreamTableEntryCtor_1bfd10, (void *)SoundStreamDtor_1bfc30, 0x84, 8);
    D_004A3EE4[0] = 1;
    RegisterGlobalObject_100dc0(D_004A3AC0, (void *)SoundStreamTableDtor_1c2790, &D_00481518);
}
