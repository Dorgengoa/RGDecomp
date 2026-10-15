#include "types.h"

extern void EffectEntryStepByIdx_2de170(void *, s16 *);

void EffectStep_2e0e00(u8 *p, s16 *q)
{
    s16 v;

    v = *q;
    switch (v) {
    case 2:
    case 3:
        EffectEntryStepByIdx_2de170(p + 0x1674, q);
        break;
    }
}
