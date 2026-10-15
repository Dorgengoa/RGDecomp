#include "types.h"

typedef struct CatchInfo {
    void *location;
    void *typeinfo;
    void *dtor;
    void *sublocation;
    s32 pointercopy;
    void *stacktop;
} CatchInfo;

typedef struct ThrowContext {
    char *throwtype;
    void *location;
    void *dtor;
    CatchInfo *catchinfo;
    char *returnaddr;
    char *SP;
    u32 FP;
} ThrowContext;

typedef struct MWExceptionInfo {
    char *code_section;
    char *exception_record;
    char *action_pointer;
    char *data_section;
    char *TOC;
    void *current_function;
} MWExceptionInfo;

typedef struct ex_catchblock {
    char *catch_type;
    u32 catch_pcoffset;
    s32 cinfo_ref;
} ex_catchblock;

extern void EhFindCallSite_102380(char *returnaddr, MWExceptionInfo *info);
extern void Terminate_100ce0(void);
extern void EhParseHeader_1026c0(ThrowContext *context, MWExceptionInfo *info);
extern CatchInfo *EhGetCatchRecord_101700(ThrowContext *context, MWExceptionInfo *info);
extern u8 *EhDispatchHandler_1011d0(ThrowContext *context, MWExceptionInfo *info, s64 *offset);
extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);
extern u8 *DecodeVarInt_100f70(u8 *p, s32 *pval);
extern void EhUnwindActions_101860(ThrowContext *context, MWExceptionInfo *info, u8 *action);
extern void EhRestoreContextAndJump_102550(ThrowContext *context, MWExceptionInfo *info, char *addr);

void EhThrowHandler_101050(ThrowContext *context)
{
    MWExceptionInfo info;
    ex_catchblock catchblock;
    s64 offset;
    CatchInfo *catchinfo;
    u8 *action;
    u8 *p;
    u32 v;
    u32 b1;
    u32 b2;
    s64 off;

    EhFindCallSite_102380(context->returnaddr, &info);
    if (info.exception_record == 0) {
        Terminate_100ce0();
    }
    EhParseHeader_1026c0(context, &info);
    if (context->throwtype == 0) {
        context->catchinfo = EhGetCatchRecord_101700(context, &info);
    } else {
        context->catchinfo = 0;
    }
    action = EhDispatchHandler_1011d0(context, &info, &offset);
    b1 = action[1];
    b2 = action[2] << 8;
    v = b1 | b2 | (action[3] << 16) | (action[4] << 24);
    p = action + 5;
    catchblock.catch_type = (char *)v;
    catchblock.catch_type = v ? (char *)v : 0;
    p = DecodeVarUInt_100ed0(p, &catchblock.catch_pcoffset);
    DecodeVarInt_100f70(p, &catchblock.cinfo_ref);
    EhUnwindActions_101860(context, &info, action);

    off = offset;
    catchinfo = (CatchInfo *)(context->FP + catchblock.cinfo_ref);
    catchinfo->location = context->location;
    catchinfo->typeinfo = context->throwtype;
    catchinfo->dtor = context->dtor;
    if (*context->throwtype == '*') {
        catchinfo->sublocation = &catchinfo->pointercopy;
        catchinfo->pointercopy = *(s32 *)context->location + off;
    } else {
        catchinfo->sublocation = (char *)context->location + off;
    }
    EhRestoreContextAndJump_102550(context, &info, info.code_section + catchblock.catch_pcoffset);
}
