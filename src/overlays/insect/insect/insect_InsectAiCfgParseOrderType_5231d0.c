#include "types.h"
#include "vm_slot.h"
/* insect 0x005231D0 -- 64 B / 16 words.  Exact twin of insect_InsectAiCfgParseTargetType_522f00,
 * only the byte offset differs (0x00 instead of 0x02).  Same f_allocflag shape
 * as insect_InsectAiCfgParseAttackChain_522f40 minus the flag guard. */
typedef struct FRec {
    u8 f00;            /* +0x00 */
} FRec;

extern void *D_004851B8;
extern FRec *insect_InsectAiCfgSelectLevel_522d30(void *a, s16 b);
extern s32 func_15F780(Slot *v);

s32 insect_InsectAiCfgParseOrderType_5231d0(Slot *v)
{
    FRec *r;

    r = insect_InsectAiCfgSelectLevel_522d30(D_004851B8, -1);
    r->f00 = func_15F780(v);
    return 1;
}
