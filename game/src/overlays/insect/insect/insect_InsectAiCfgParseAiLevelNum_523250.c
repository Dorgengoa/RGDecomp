/* rgp:protos */
#define RGP_SELF_insect_InsectAiCfgParseAiLevelNum_523250 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x00523250 -- 52 B / 13 words.  Exact twin of insect_InsectAiCfgParseAiLevel_523210
 * against insect_InsectAiCfgAllocLevels_522d70 instead of insect_InsectAiCfgSelectLevel_522d30; same
 * named-handle reading (see that file's comment for the two-word residue the
 * local kills). */
extern void *D_004851B8;
/*rgp*/
/*rgp*/

s32 insect_InsectAiCfgParseAiLevelNum_523250(Slot *v)
{
    void *h;

    h = D_004851B8;
    insect_InsectAiCfgAllocLevels_522d70(h, VariantGetInt_15f780(v));
    return 1;
}
