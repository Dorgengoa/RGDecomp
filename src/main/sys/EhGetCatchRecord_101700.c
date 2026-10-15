#include "types.h"

typedef struct CatchInfo {
    void *location;
    void *typeinfo;
    void *dtor;
    void *sublocation;
    s32 pointercopy;
    void *stacktop;
} CatchInfo;

typedef struct Regs { __int128 r[42]; } Regs;

typedef struct ThrowContext {
    char *throwtype;
    void *location;
    void *dtor;
    CatchInfo *catchinfo;
    char *returnaddr;
    char *SP;
    char *FP;
    u32 pad;
    Regs regs;
} ThrowContext;

typedef struct MWExceptionInfo {
    char *code_section;
    char *exception_record;
    u8 *action_pointer;
    char *data_section;
    char *TOC;
    struct { void *p; } current_function;
} MWExceptionInfo;

typedef struct ActionIterator {
    MWExceptionInfo info;
    ThrowContext context;
} ActionIterator;

extern void Terminate_100ce0(void);
extern u8 *DecodeVarInt_100f70(u8 *p, s32 *pval);
extern u8 EhSkipActions_102070(ActionIterator *iter);

static inline u8 CurrentAction(ActionIterator *iter)
{
    return iter->info.action_pointer ? (*iter->info.action_pointer & 0x1F) : 0;
}

CatchInfo *EhGetCatchRecord_101700(ThrowContext *context, MWExceptionInfo *info)
{
    ActionIterator iter;
    s32 cinfo_ref;
    CatchInfo *catchinfo;
    u8 type;

    iter.info.code_section = info->code_section;
    iter.info.exception_record = info->exception_record;
    iter.info.action_pointer = info->action_pointer;
    iter.info.data_section = info->data_section;
    iter.info.TOC = info->TOC;
    iter.info.current_function = info->current_function;
    iter.context.throwtype = context->throwtype;
    iter.context.location = context->location;
    iter.context.dtor = context->dtor;
    iter.context.catchinfo = context->catchinfo;
    iter.context.returnaddr = context->returnaddr;
    iter.context.SP = context->SP;
    iter.context.FP = context->FP;
    iter.context.pad = context->pad;
    iter.context.regs = context->regs;

    for (type = CurrentAction(&iter);; type = EhSkipActions_102070(&iter)) {
        switch (type) {
        case 0: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 15:
            continue;
        case 13:
            break;
        default:
            Terminate_100ce0();
            break;
        }
        break;
    }
    DecodeVarInt_100f70(iter.info.action_pointer + 1, &cinfo_ref);
    catchinfo = (CatchInfo *)(iter.context.FP + cinfo_ref);
    context->throwtype = (char *)catchinfo->typeinfo;
    context->location = catchinfo->location;
    context->dtor = 0;
    context->catchinfo = catchinfo;
    return catchinfo;
}
