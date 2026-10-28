/* rgp:protos */
#define RGP_SELF_EvTargetSetCopy_336780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvTargetSetCopy_336780(u8 *dst, u8 *src, s32 c, s32 d)
{
    EvTargetSetReset_336bb0((void *)dst);
    if (src == 0 || c == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst, EvTargetSetGetFirstRef_336960(src), c) == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst + 0x30, EvTargetSetGetRef30_336950(src), c) == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst + 0x60, ((u8 *)EvTargetSetGetTargets_336940(src)), c) == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst + 0x90, ((u8 *)EvTargetSetGetTargets_336940(src)) + 0x30, c) == 0) {
        return 0;
    }
    *(s16 *)(dst + 0x114) = ((short)EvTargetSetGetId_336970(src));
    *(f32 *)(dst + 0x108) = *(f32 *)(src + 0x108);
    *(f32 *)(dst + 0x10C) = *(f32 *)(src + 0x10C);
    *(f32 *)(dst + 0x110) = *(f32 *)(src + 0x110);
    if (d != 0) {
        TargetRefStashId_2e61b0(dst);
        TargetRefStashId_2e61b0(dst + 0x30);
    }
    return 1;
}
