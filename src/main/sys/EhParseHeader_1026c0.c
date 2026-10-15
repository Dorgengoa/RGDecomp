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
} ThrowContext;

typedef struct MWExceptionInfo {
    char *code_section;
    char *exception_record;
    u8 *action_pointer;
} MWExceptionInfo;

extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);

void EhParseHeader_1026c0(ThrowContext *context, MWExceptionInfo *info)
{
    char *rec = info->exception_record;
    s32 flags = rec[0] & 0x40;
    u8 *p;

    context->has_frame_ptr = rec[0] & 0x20;
    context->saved_fprs = rec[0] & 0x10;
    context->saved_gprs = rec[0] & 0xF;
    p = DecodeVarUInt_100ed0((u8 *)rec + 1, &context->frame_size);
    p = DecodeVarUInt_100ed0(p, &context->frame_offset);
    if (context->has_frame_ptr) {
        context->FP = (char *)(s32)context->regs[30];
    } else {
        context->FP = context->SP;
    }
    if (flags) {
        DecodeVarUInt_100ed0(p, &context->dyn_offset);
    } else {
        context->dyn_offset = 0;
    }
}
