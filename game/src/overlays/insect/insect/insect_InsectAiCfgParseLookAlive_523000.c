/* rgp:protos */
#define RGP_SELF_insect_InsectAiCfgParseLookAlive_523000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x00523000 -- the f_allocflag shape (insect_InsectAiCfgParseAttackChain_522f40) WITHOUT the
 * byte field: the guard tests func_15F780's result directly rather than a
 * value read back out of the record, so there is no `sb`/`lbu` pair. */
typedef struct FRec {
    u8 pad00[0x8];
    s64 f08;           /* +0x08 -- ld/ori/sd, so 64-bit */
} FRec;

extern void *D_004851B8;
/*rgp*/
/*rgp*/

s32 insect_InsectAiCfgParseLookAlive_523000(Slot *v)
{
    FRec *r;

    r = ((FRec *)insect_InsectAiCfgSelectLevel_522d30(D_004851B8, -1));
    if (VariantGetInt_15f780(v) != 0) {
        r->f08 = r->f08 | 0x4000;
    }
    return 1;
}
