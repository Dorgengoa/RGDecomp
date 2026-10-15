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

typedef struct ex_catchblock {
    char *catch_type;
    u32 catch_pcoffset;
    s32 cinfo_ref;
} ex_catchblock;

typedef struct ex_specification {
    u32 specs;
    u32 pcoffset;
    s32 cinfo_ref;
    u8 *spec;
} ex_specification;

extern void Terminate_100ce0(void);
extern s32 EhCatchTypeCompare_100a60(char *throwtype, char *catchtype, s64 *offset_result);
extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);
extern u8 *DecodeVarInt_100f70(u8 *p, s32 *pval);
extern void EhUnwindActions_101860(ThrowContext *context, MWExceptionInfo *info, u8 *action);
extern void EhRestoreContextAndJump_102550(ThrowContext *context, MWExceptionInfo *info, char *addr);
extern u8 EhSkipActions_102070(ActionIterator *iter);

static inline s32 IsInSpecification(char *extype, ex_specification *spec)
{
    u8 *p;
    u32 i;
    s64 offset;

    for (i = 0, p = spec->spec; i < spec->specs; i++, p += 4) {
        if (EhCatchTypeCompare_100a60(extype, (char *)(p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24)), &offset)) {
            return 1;
        }
    }
    return 0;
}

static inline void HandleUnexpected(ThrowContext *context, MWExceptionInfo *info, ex_specification *unexp, u8 *unexp_action)
{
    CatchInfo *ci;
    EhUnwindActions_101860(context, info, unexp_action);
    ci = (CatchInfo *)(context->FP + unexp->cinfo_ref);
    ci->location = context->location;
    ci->typeinfo = context->throwtype;
    ci->dtor = context->dtor;
    ci->stacktop = unexp_action;
    EhRestoreContextAndJump_102550(context, info, info->code_section + unexp->pcoffset);
}

static inline u8 CurrentAction(ActionIterator *iter)
{
    return iter->info.action_pointer ? (*iter->info.action_pointer & 0x1F) : 0;
}

u8 *EhDispatchHandler_1011d0(ThrowContext *context, MWExceptionInfo *info, s64 *result_offset)
{
    ActionIterator iter;
    ex_specification spec;
    ex_catchblock catchblock;
    u8 *action;
    u8 *p;
    u32 v;
    u32 b1;
    u32 b2;
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
        case 0: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 13:
            break;
        case 12:
            action = iter.info.action_pointer;
            b1 = action[1];
            b2 = action[2] << 8;
            v = b1 | b2 | (action[3] << 16) | (action[4] << 24);
            p = action + 5;
            catchblock.catch_type = (char *)v;
            catchblock.catch_type = v ? (char *)v : 0;
            p = DecodeVarUInt_100ed0(p, &catchblock.catch_pcoffset);
            DecodeVarInt_100f70(p, &catchblock.cinfo_ref);
            if (!EhCatchTypeCompare_100a60(context->throwtype, catchblock.catch_type, result_offset)) {
                break;
            }
            goto found;
        case 15:
            p = DecodeVarUInt_100ed0(iter.info.action_pointer + 1, &spec.specs);
            p = DecodeVarUInt_100ed0(p, &spec.pcoffset);
            spec.spec = DecodeVarInt_100f70(p, &spec.cinfo_ref);
            if (!IsInSpecification(context->throwtype, &spec)) {
                HandleUnexpected(context, info, &spec, iter.info.action_pointer);
            }
            break;
        default:
            Terminate_100ce0();
            goto found;
        }
    }
found:
    return iter.info.action_pointer;
}
