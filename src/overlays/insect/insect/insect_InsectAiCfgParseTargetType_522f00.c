#include "types.h"
#include "vm_slot.h"
/* insect 0x00522F00 -- 64 B / 16 words.  The f_allocflag shape of
 * insect_InsectAiCfgParseAttackChain_522f40 / 005230b0 WITHOUT the flag guard: allocate the record,
 * store func_15F780's result into one byte field, return 1.  No `lbu`
 * read-back because nothing tests the field afterwards.
 * D_004851B8 is _gp + 0x48, inside the gp window, so it is NOT const. */
typedef struct FRec {
    u8 pad00[0x2];
    u8 f02;            /* +0x02 */
} FRec;

extern void *D_004851B8;
extern FRec *insect_InsectAiCfgSelectLevel_522d30(void *a, s16 b);
extern s32 func_15F780(Slot *v);

s32 insect_InsectAiCfgParseTargetType_522f00(Slot *v)
{
    FRec *r;

    r = insect_InsectAiCfgSelectLevel_522d30(D_004851B8, -1);
    r->f02 = func_15F780(v);
    return 1;
}
