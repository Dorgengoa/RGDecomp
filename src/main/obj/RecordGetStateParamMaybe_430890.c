#include "types.h"

extern void *RecordFindStateEntry_4308d0(void);

s32 RecordGetStateParamMaybe_430890(void)
{
    s32   r;
    void *p;

    r = 2;
    p = RecordFindStateEntry_4308d0();
    if (p != 0) r = *(s16 *)((u8 *)p + 0x6);
    return r;
}
