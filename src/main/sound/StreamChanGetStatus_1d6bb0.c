#include "types.h"
extern s32 StreamChanIsOpenReq_1d7290(void *);
extern s32 StreamChanIsResumeReq_1d7280(void *);
extern s32 SoundStreamSlotQueryState_1bd210(s32);
struct Obj0 { u8 pad000[0x80]; s16 m80; };
s32 StreamChanGetStatus_1d6bb0(struct Obj0 *p0)
{
    if (StreamChanIsOpenReq_1d7290(p0) == 0) {
        if (StreamChanIsResumeReq_1d7280(p0) == 0) {
            goto ok;
        }
    }
    return -1;
ok:
    return SoundStreamSlotQueryState_1bd210(p0->m80);
}
