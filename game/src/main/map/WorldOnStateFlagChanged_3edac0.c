/* rgp:protos */
#define RGP_SELF_WorldOnStateFlagChanged_3edac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Guard one is a one-bit field at 0x2C.  Guard two compares the last two
   parameters narrowed to s16 -- the dsll32/dsra32 16 pairs are the explicit
   casts, and retail FALLS THROUGH into the teardown, so that is the if body. */

typedef struct {
    u8 pad00[0x2C];
    unsigned char b0 : 1;
} __attribute__((aligned(4))) SDAC0;

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
