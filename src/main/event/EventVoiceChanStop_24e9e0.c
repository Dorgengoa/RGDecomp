#include "types.h"

extern void ModelObjTexAnimResetByName_1ac510(s32, void *);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void StreamPauseChan_1cd9f0(s32, s32);
extern void StreamStopChan_1cda60(s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetCurrentScene_1f5be0(void);

void EventVoiceChanStop_24e9e0(void *arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 *a0;
    u8 *a2;
    s32 obj;
    s32 ctx;

    if (arg2 != NULL) {
        a0 = (u8 *)arg0;
        a2 = (u8 *)arg2;
        obj = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), *(s32 *)(a2 + 0xC));
        if (obj != 0) {
            ModelObjTexAnimResetByName_1ac510(obj, a2 + 0x10);
        }
        *(s32 *)(a2 + 0) = 0;
        *(s8 *)(a2 + 0x20) = 0;
        *(s32 *)(a2 + 4) = -1;
        ctx = GetLoaderMgr_1f59d0();
        StreamPauseChan_1cd9f0(ctx, arg1);
        StreamStopChan_1cda60(ctx, arg1);
        if ((*(s32 *)(a0 + 0xC) != 0) && (arg3 <= 0) && (*(s32 *)(a0 + 0x10) != -0x3E7)) {
            *(s32 *)(a0 + 0x10) = 0x1E;
        }
    }
}
