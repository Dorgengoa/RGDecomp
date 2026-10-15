#include "types.h"
/* normal 0x00506030 -- the reset path: clear 0x43E, two local calls, then a
 * fetch guarded `return 0`, two func_290010 calls, an optional call under
 * `b >= 0` and a shared tail call. */
extern void normal_BtlChgPageSetStateId_5061d0(void *p, s32 a);
extern s32  normal_BtlChgPageStateIdInc_5061b0(void *p);
extern void normal_BtlChgPageSetMember_505fa0(void *p, s32 a);
extern void normal_BtlChgPageSetAbilityReq_5052f0(void *p, s32 a, s32 b);
extern void *normal_UiPageGetLayout_289b60(void *p);
extern void func_290010(void *w, s32 a, s32 b, s32 c);

s32 normal_BtlChgPageStart_506030(void *p, s32 b)
{
    void *w;

    *(s16 *)((u8 *)p + 0x43E) = 0;
    normal_BtlChgPageSetStateId_5061d0(p, -1);
    normal_BtlChgPageStateIdInc_5061b0(p);
    w = normal_UiPageGetLayout_289b60(p);
    if (w == 0) {
        return 0;
    }
    func_290010(w, 0x2B, 1, -1);
    func_290010(w, 1, 1, -1);
    if (b > -1) {
        normal_BtlChgPageSetMember_505fa0(p, b);
    }
    normal_BtlChgPageSetAbilityReq_5052f0(p, -1, 0);
    return 1;
}
