#include "types.h"

extern void *GetStreamMgr_207ea0(void *);
extern void StreamMgrSetChanVolumeFade_1d63a0(f32, void *, s32, void *);

void StreamChan1SetVolumeFade_2072f0(void *p, f32 v)
{
    void *q;

    q = GetStreamMgr_207ea0(p);
    StreamMgrSetChanVolumeFade_1d63a0(v, q, 1, p);
}
