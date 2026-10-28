/* rgp:protos */
#define RGP_SELF_insect_InsectAiCfgParseOrderType_5231d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x005231D0 -- 64 B / 16 words.  Exact twin of insect_InsectAiCfgParseTargetType_522f00,
 * only the byte offset differs (0x00 instead of 0x02).  Same f_allocflag shape
 * as insect_InsectAiCfgParseAttackChain_522f40 minus the flag guard. */
typedef struct FRec {
    u8 f00;            /* +0x00 */
} FRec;

extern void *D_004851B8;
/*rgp*/
/*rgp*/

s32 insect_InsectAiCfgParseOrderType_5231d0(Slot *v)
{
    FRec *r;

    r = ((FRec *)insect_InsectAiCfgSelectLevel_522d30(D_004851B8, -1));
    r->f00 = VariantGetInt_15f780(v);
    return 1;
}
