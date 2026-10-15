#include "types.h"

/* Destructor stub: the outer `if (this)` and the inner one are both in the
   source (the inner guards the sub-object teardown).  The dsll32/dsra32 pair
   is an s32 flag with an explicit (s16) cast at the compare. */

extern void BufHolderDtor_1a1670(void *, s32);
extern void BufHolderDtor_1a1380(void *, s32);
extern void OperatorDelete_100840(void *);

void *EffInstHdlTableDtorMaybe_1a1300(u8 *t, s32 flag)
{
    if (t != 0) {
        if (t != 0) {
            BufHolderDtor_1a1670(t + 0x18, -1);
            BufHolderDtor_1a1670(t + 0xC, -1);
            BufHolderDtor_1a1380(t, -1);
        }
        if ((s16)flag > 0) {
            OperatorDelete_100840(t);
        }
    }
    return t;
}
