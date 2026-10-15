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
extern FRec *insect_InsectAiCfgSelectLevel_522d30(void *a, s16 b);
extern s32 func_15F780(Slot *v);

s32 insect_InsectAiCfgParseLookAlive_523000(Slot *v)
{
    FRec *r;

    r = insect_InsectAiCfgSelectLevel_522d30(D_004851B8, -1);
    if (func_15F780(v) != 0) {
        r->f08 = r->f08 | 0x4000;
    }
    return 1;
}
