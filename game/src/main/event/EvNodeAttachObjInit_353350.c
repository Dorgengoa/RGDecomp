/* rgp:protos */
#define RGP_SELF_EvNodeAttachObjInit_353350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                         /* extern */
/*rgp*/                              /* extern */
/*rgp*/                             /* extern */
/*rgp*/                 /* extern */
/*rgp*/ /* extern */
/*rgp*/                           /* extern */
/*rgp*/                           /* extern */
/*rgp*/

s32 EvNodeAttachObjInit_353350(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_19;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 temp_2_4;
    u16 var_2;

    EvNodeAttachObjReset_3535c0((void *)arg0);
    if (arg2 == NULL || arg3 == 0) {
        return 0;
    }
    if (EvObjInit_2f9cf0(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
        return 0;
    }
    temp_19 = ((s32)EvObjGetEventRec_353340(arg2));
    EventRecReset_2e5840((u8 *)arg0 + 0xE0);
    (*(s32 *)((u8 *)(arg0) + 0xF0)) = 0;
    if (temp_19 == 0 || arg3 == 0) {
        var_2 = 0;
    } else if (EventRecGetKey_2e5730(temp_19) != 0 && (temp_2_2 = ((s32)MemStackStrDup_14cff0(EventRecGetKey_2e5730(temp_19), arg3)), (*(s32 *)((u8 *)(arg0) + 0xEC)) = temp_2_2, temp_2_2 == 0)) {
        var_2 = 0;
    } else {
        var_2 = 1;
    }
    if (!var_2) {
        return 0;
    }
    if (TargetRefCopy_2e7140((u8 *)arg0 + 0xF4, ((s32)EvNodeAttachObjGetNodeTargetRef_353330(arg2)), arg3) == 0) {
        return 0;
    }
    temp_2_3 = ((s32)MemStackStrDup_14cff0((*(s32 *)((u8 *)(arg2) + 0x12C)), arg3));
    (*(s32 *)((u8 *)(arg0) + 0x12C)) = temp_2_3;
    if (temp_2_3 == 0) {
        return 0;
    }
    temp_2_4 = ((s32)MemStackStrDup_14cff0((*(s32 *)((u8 *)(arg2) + 0x130)), arg3));
    (*(s32 *)((u8 *)(arg0) + 0x130)) = temp_2_4;
    if (temp_2_4 == 0) {
        return 0;
    }
    temp_2 = ((s32)MemStackStrDup_14cff0((*(s32 *)((u8 *)(arg2) + 0x134)), arg3));
    (*(s32 *)((u8 *)(arg0) + 0x134)) = temp_2;
    return temp_2 != 0;
}
