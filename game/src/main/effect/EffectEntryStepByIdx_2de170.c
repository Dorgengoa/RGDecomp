/* rgp:protos */
#define RGP_SELF_EffectEntryStepByIdx_2de170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem002de170 {
    u8 pad0[0xE0];
} Elem002de170;

typedef struct Info002de170 {
    u8 pad0[0x8];
    s32 unk8;
} Info002de170;

/*rgp*/

void EffectEntryStepByIdx_2de170(Elem002de170 *arg0, Info002de170 *arg1)
{
    s32 index;

    index = arg1->unk8;
    if ((index < 0) || (index >= 0x30)) return;
    EffectEntryNodeStepById_2da340(arg0 + index, arg1);
}
