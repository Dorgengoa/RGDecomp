#include "types.h"

extern void EvTargetSetReset_336bb0(void);
extern void *EvTargetSetGetFirstRef_336960(void *);
extern void *EvTargetSetGetRef30_336950(void *);
extern u8 *EvTargetSetGetTargets_336940(void *);
extern s32 EvTargetSetGetId_336970(void *);
extern s32 TargetRefCopy_2e7140(void *, void *, s32);
extern void TargetRefStashId_2e61b0(void *);

s32 EvTargetSetCopy_336780(u8 *dst, u8 *src, s32 c, s32 d)
{
    EvTargetSetReset_336bb0();
    if (src == 0 || c == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst, EvTargetSetGetFirstRef_336960(src), c) == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst + 0x30, EvTargetSetGetRef30_336950(src), c) == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst + 0x60, EvTargetSetGetTargets_336940(src), c) == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(dst + 0x90, EvTargetSetGetTargets_336940(src) + 0x30, c) == 0) {
        return 0;
    }
    *(s16 *)(dst + 0x114) = EvTargetSetGetId_336970(src);
    *(f32 *)(dst + 0x108) = *(f32 *)(src + 0x108);
    *(f32 *)(dst + 0x10C) = *(f32 *)(src + 0x10C);
    *(f32 *)(dst + 0x110) = *(f32 *)(src + 0x110);
    if (d != 0) {
        TargetRefStashId_2e61b0(dst);
        TargetRefStashId_2e61b0(dst + 0x30);
    }
    return 1;
}
