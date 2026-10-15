#include "types.h"

typedef struct ThrowContext {
    char *throwtype;
    void *location;
    void *dtor;
    void *catchinfo;
    char *returnaddr;
    char *SP;
    char *FP;
    u32 pad;
    __int128 regs[31];
    u32 pad2[4];
    u32 frame_size;
    u32 frame_offset;
    s32 saved_gprs;
    s32 saved_fprs;
    s32 has_frame_ptr;
    u32 dyn_offset;
    u32 fregs[32];
} ThrowContext;

typedef struct MWExceptionInfo {
    char *code_section;
    char *exception_record;
    u8 *action_pointer;
} MWExceptionInfo;

char *EhUnwindRestoreRegs_102770(ThrowContext *context, MWExceptionInfo *info)
{
    u64 size = context->frame_size;
    u64 offset = context->frame_offset;
    s32 flags = info->exception_record[0] & 0x40;
    u64 n = context->saved_gprs;
    u64 dyn;
    u32 *dp;
    __int128 *p;
    char *ret;
    s32 i;

    if (flags) {
        dyn = context->dyn_offset;
        dp = (u32 *)(context->FP + offset + ((dyn * 4 + 15) & ~15));
        p = (__int128 *)((u32)dp + n * 16);
    } else {
        p = (__int128 *)(context->FP + offset + n * 16);
    }
    if (context->has_frame_ptr) {
        p++;
    }
    ret = *(char **)p;
    if (context->has_frame_ptr) {
        p--;
        context->regs[30] = *p;
    } else if (n == 9) {
        p--;
        n--;
        context->regs[30] = *p;
    }
    p -= n;
    for (i = 0; i < n; i++) {
        context->regs[16 + i] = *p++;
    }
    context->SP = context->FP + size;
    if (flags) {
        dp -= dyn;
        for (i = 0; i < dyn; i++) {
            context->fregs[20 + i] = dp[i];
        }
    }
    return ret;
}
