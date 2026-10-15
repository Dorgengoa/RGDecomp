#include "types.h"
#include "vec.h"

typedef struct {
    u8 pad0[0x154];
    s32 unk154;
    u8 pad158[8];
    u128 unk160;
} Item;

extern Item *ArrayGetChecked_1ad400(s32 arg0, s32 arg1);
extern s32 ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern void VecSub_1cbd00(u128 *arg0, s32 arg1, u128 *arg2);
extern void VecCopy_1cbe30(u128 *arg0, s32 arg1);
extern f32 AngleWrap_1cbf30(f32 arg0);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 EventVolumeRecAnyHitMoveAllowed_2e4be0(s32 arg0, void *arg1);
extern void XformToLocal_2e7440(u8 *arg0, void *arg1, s32 arg2);
extern void XformTransformPoint_2e75a0(u8 *arg0, s32 arg1, void *arg2);
extern f32 EventObjGetYaw_2e7630(u8 *arg0);

s32 EvTargetCarryPosMaybe_3527f0(u8 *arg0, s32 arg1, s32 arg2, f32 *arg3, s32 arg4, s32 arg5)
{
    u128 q;
    u8 buf[0x10];
    f32 f;
    s32 t;
    s32 i;
    Item *it;

    if (arg4 == 0) {
        return 0;
    }
    VecCopy_1cbe30(&q, arg2);
    XformToLocal_2e7440(arg0 + 0x80, buf, arg2);
    if (EventVolumeRecAnyHitMoveAllowed_2e4be0(arg4, buf) == 0) {
        return 0;
    }
    if (arg5 == 0) {
        return 1;
    }
    XformTransformPoint_2e75a0(arg0 + 0x38, arg2, buf);
    VecSub_1cbd00(&q, arg2, &q);
    f = EventObjGetYaw_2e7630(arg0 + 0x38);
    arg3[1] = AngleWrap_1cbf30(arg3[1] + AngleWrap_1cbf30(f - EventObjGetYaw_2e7630(arg0 + 0x80)));
    t = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg1);
    if (t != 0) {
        i = 0;
        while ((it = ArrayGetChecked_1ad400(t, i)) != NULL) {
            i++;
            it->unk160 = q;
            it->unk154 = 1;
        }
    }
    return 1;
}
