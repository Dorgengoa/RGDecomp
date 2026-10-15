#include "types.h"

extern void MapObjParamRefreshCondsMaybe_3ed0a0(void *, s32);
extern void BgmParamRefreshCondsMaybe_3ece90(void *, s32);
extern void TranspParamRefreshCondsMaybe_3ecce0(void *, s32);
extern void TreasureBoxParamRefreshCondsMaybe_3eca40(void *, s32);
extern void NpcDataRefreshCondsMaybe_3eb930(void *, s32);
extern void MapApplySaveStateMaybe_1fe560(void);
extern void PartySelectEncounter_3c9c30(s32);
extern void CharaSysEncounterDistRoll_3a59d0(s32, s32);
extern void PartyRefreshBgmOverride_3ca730(s32);

/* Guard one is a one-bit field at 0x2C.  Guard two compares the last two
   parameters narrowed to s16 -- the dsll32/dsra32 16 pairs are the explicit
   casts, and retail FALLS THROUGH into the teardown, so that is the if body. */

typedef struct {
    u8 pad00[0x2C];
    u32 b0 : 1;
} SDAC0;

s32 WorldOnStateFlagChanged_3edac0(u8 *p, s32 unused, s32 a, s32 b)
{
    if (((SDAC0 *)p)->b0) {
        return 0;
    }
    if ((u8)a != (u8)b) {
        MapObjParamRefreshCondsMaybe_3ed0a0(p, -1);
        BgmParamRefreshCondsMaybe_3ece90(p, -1);
        TranspParamRefreshCondsMaybe_3ecce0(p, -1);
        TreasureBoxParamRefreshCondsMaybe_3eca40(p, -1);
        NpcDataRefreshCondsMaybe_3eb930(p, -1);
        MapApplySaveStateMaybe_1fe560();
        PartySelectEncounter_3c9c30(*(s32 *)(p + 0x18));
        CharaSysEncounterDistRoll_3a59d0(*(s32 *)(p + 0x20), 0);
        PartyRefreshBgmOverride_3ca730(*(s32 *)(p + 0x18));
    }
    return 1;
}
