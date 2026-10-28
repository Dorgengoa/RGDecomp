/* rgp:protos */
#define RGP_SELF_EvCmdSoundSlotFgLoad_261bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00481F78;

s32 EvCmdSoundSlotFgLoad_261bf0(void *rgp_a0) {
    s32 temp_2;
    s32 temp_17;
    s32 temp_16;

    temp_2 = ScriptGetInt_26a2a0((void *)rgp_a0);
    if (!(GameSceneSoundSlot5HasLoadedId_1d07d0(D_00481F78, temp_2) & 0xFF)) {
        return 0;
    }
    temp_16 = *(s32 *)((u8 *)D_00481F78 + 0x1808);
    temp_17 = ((s32)MemStackHeapAlloc_14db10(temp_16, 2, 0, 0x40));
    MemStackReturnToOwnerMaybe_14dad0(temp_16);
    MemStackHeapFree_14dcb0(temp_16, temp_17);
    return GameSceneSoundSlot5RequestLoad_1d0690(D_00481F78, temp_2) & 0xFF;
    return 0;
}
