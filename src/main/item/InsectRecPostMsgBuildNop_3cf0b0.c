#include "types.h"

/* Reads the s32 at +0x18 and leaves it in $v1 (a volatile load with no use;
   the original was a naked accessor).  `schedule off` keeps the load out of
   the jr delay slot. */
#pragma push
#pragma schedule off
void InsectRecPostMsgBuildNop_3cf0b0(u8 *p)
{
    *(volatile s32 *)(p + 0x18);
}
#pragma pop
