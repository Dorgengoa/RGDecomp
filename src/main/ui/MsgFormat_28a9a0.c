#include "types.h"

extern void MsgExpandTokens_28a250(void *);

void *MsgFormat_28a9a0(void *a, s32 b)
{
    if (a == 0) goto zero;
    if (b != 0) goto ok;
zero:
    return 0;
ok:
    MsgExpandTokens_28a250(a);
    return a;
}
