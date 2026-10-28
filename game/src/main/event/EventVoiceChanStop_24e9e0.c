/* rgp:protos */
#define RGP_SELF_EventVoiceChanStop_24e9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EventVoiceChanStop_24e9e0(void *arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 *a0;
    u8 *a2;
    s32 obj;
    s32 ctx;

    if (arg2 != NULL) {
        a0 = (u8 *)arg0;
        a2 = (u8 *)arg2;
        obj = ((s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), *(s32 *)(a2 + 0xC)));
        if (obj != 0) {
            ModelObjTexAnimResetByName_1ac510(obj, a2 + 0x10);
        }
        *(s32 *)(a2 + 0) = 0;
        *(s8 *)(a2 + 0x20) = 0;
        *(s32 *)(a2 + 4) = -1;
        ctx = ((s32)GetLoaderMgr_1f59d0());
        StreamPauseChan_1cd9f0(ctx, arg1);
        StreamStopChan_1cda60(ctx, arg1);
        if ((*(s32 *)(a0 + 0xC) != 0) && (arg3 <= 0) && (*(s32 *)(a0 + 0x10) != -0x3E7)) {
            *(s32 *)(a0 + 0x10) = 0x1E;
        }
    }
}
