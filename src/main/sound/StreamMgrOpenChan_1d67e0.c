#include "types.h"

extern void StreamMgrCloseChan_1d67a0(u8 *);
extern s32 StreamChanOpen_1d6e40(u8 *, s32, s32, s32, s32);

s32 StreamMgrOpenChan_1d67e0(u8 *a, s32 i, s32 c, s32 d, s32 e, s32 f)
{
    StreamMgrCloseChan_1d67a0(a);
    if (i < 0) goto zero;
    if (i < 4) goto ok;
zero:
    return 0;
ok:
    return StreamChanOpen_1d6e40(a + i * 224, c, d, e, f);
}
