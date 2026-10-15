#include "types.h"

extern void MemStackReturnToOwnerMaybe_14dad0(s32 arg0);
extern s32 MemStackHeapAlloc_14db10(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void MemStackHeapFree_14dcb0(s32 arg0, s32 arg1);
extern s32 GameSceneSoundSlot5RequestLoad_1d0690(void *arg0, s32 arg1);
extern s32 GameSceneSoundSlot5HasLoadedId_1d07d0(void *arg0, s32 arg1);
extern s32 ScriptGetInt_26a2a0(void);
extern void *D_00481F78;

s32 EvCmdSoundSlotFgLoad_261bf0(void) {
    s32 temp_2;
    s32 temp_17;
    s32 temp_16;

    temp_2 = ScriptGetInt_26a2a0();
    if (!(GameSceneSoundSlot5HasLoadedId_1d07d0(D_00481F78, temp_2) & 0xFF)) {
        return 0;
    }
    temp_16 = *(s32 *)((u8 *)D_00481F78 + 0x1808);
    temp_17 = MemStackHeapAlloc_14db10(temp_16, 2, 0, 0x40);
    MemStackReturnToOwnerMaybe_14dad0(temp_16);
    MemStackHeapFree_14dcb0(temp_16, temp_17);
    return GameSceneSoundSlot5RequestLoad_1d0690(D_00481F78, temp_2) & 0xFF;
    return 0;
}
