/* rgp:protos */
#define RGP_SELF_EvTargetCarryPosMaybe_3527f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct {
    u8 pad0[0x154];
    s32 unk154;
    u8 pad158[8];
    u128 unk160;
} Item;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvTargetCarryPosMaybe_3527f0(u8 *arg0, s32 arg1, s32 arg2, f32 *arg3, s32 arg4, s32 arg5)
{
    u128 q;
    u8 buf[0x10] __attribute__((aligned(16)));
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
    t = ((s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg1));
    if (t != 0) {
        i = 0;
        while ((it = ((Item *)ArrayGetChecked_1ad400(t, i))) != NULL) {
            i++;
            it->unk160 = q;
            it->unk154 = 1;
        }
    }
    return 1;
}
