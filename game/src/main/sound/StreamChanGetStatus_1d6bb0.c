/* rgp:protos */
#define RGP_SELF_StreamChanGetStatus_1d6bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
struct Obj0 { u8 pad000[0x80]; s16 m80; };
s32 StreamChanGetStatus_1d6bb0(struct Obj0 *p0)
{
    if (((unsigned char)StreamChanIsOpenReq_1d7290(p0)) == 0) {
        if (((unsigned char)StreamChanIsResumeReq_1d7280(p0)) == 0) {
            goto ok;
        }
    }
    return -1;
ok:
    return SoundStreamSlotQueryState_1bd210(p0->m80);
}
