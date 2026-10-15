#include "types.h"

typedef struct Elem002de170 {
    u8 pad0[0xE0];
} Elem002de170;

typedef struct Info002de170 {
    u8 pad0[0x8];
    s32 unk8;
} Info002de170;

void EffectEntryNodeStepById_2da340(Elem002de170 *elem, Info002de170 *info, s32 index);

void EffectEntryStepByIdx_2de170(Elem002de170 *arg0, Info002de170 *arg1)
{
    s32 index;

    index = arg1->unk8;
    if ((index < 0) || (index >= 0x30)) return;
    EffectEntryNodeStepById_2da340(arg0 + index, arg1, index);
}
