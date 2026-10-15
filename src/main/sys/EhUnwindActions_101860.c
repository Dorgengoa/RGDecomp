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

typedef void (*DtorFunc)(void *, s32);
typedef void (*DeleteFunc)(void *);

extern void Terminate_100ce0(void);
extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);
extern u8 *DecodeVarInt_100f70(u8 *p, s32 *pval);
extern char *EhUnwindRestoreRegs_102770(ThrowContext *context, MWExceptionInfo *info);
extern void EhFindCallSite_102380(char *retaddr, MWExceptionInfo *info);
extern void EhParseHeader_1026c0(ThrowContext *context, MWExceptionInfo *info);

#define LE32(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))

static inline u8 *GetDtorFunc(u8 *p, DtorFunc *out)
{
    *out = (DtorFunc)LE32(p);
    return p + 4;
}

static inline u8 *GetDeleteFunc(u8 *p, DeleteFunc *out)
{
    *out = (DeleteFunc)LE32(p);
    return p + 4;
}

static inline u8 *GetCatchType(u8 *ap, void **out)
{
    *out = (void *)LE32(ap + 1);
    return ap + 5;
}

void EhUnwindActions_101860(ThrowContext *context, MWExceptionInfo *info, u8 *catcher)
{
    u8 action;
    u8 *p;
    u32 regvar;

    for (;;) {
        if (info->action_pointer == 0) {
            EhFindCallSite_102380(EhUnwindRestoreRegs_102770(context, info), info);
            if (info->exception_record == 0) {
                Terminate_100ce0();
            }
            EhParseHeader_1026c0(context, info);
            if (info->action_pointer == 0) {
                continue;
            }
        }
        action = *info->action_pointer;
        switch (action & 0x1F) {
        case 1: {
            s32 target;
            DecodeVarInt_100f70(info->action_pointer + 1, &target);
            info->action_pointer = info->action_pointer + target;
            break;
        }
        case 2: {
            s32 local;
            DtorFunc dtor;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &local);
            dtor = (DtorFunc)LE32(p);
            dtor(context->FP + local, -1);
            info->action_pointer = p + 4;
            break;
        }
        case 3: {
            s32 cond;
            s32 local;
            DtorFunc dtor;
            regvar = action & 0x40;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &cond);
            p = DecodeVarInt_100f70(p, &local);
            p = GetDtorFunc(p, &dtor);
            if (regvar ? (s8)context->regs.r[cond] : *(s8 *)(context->FP + cond)) {
                dtor(context->FP + local, -1);
            }
            info->action_pointer = p;
            break;
        }
        case 4: {
            s32 pointer;
            DtorFunc dtor;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &pointer);
            p = GetDtorFunc(p, &dtor);
            dtor(regvar ? (char *)(s32)context->regs.r[pointer] : *(char **)(context->FP + pointer), -1);
            info->action_pointer = p;
            break;
        }
        case 5: {
            s32 localarray;
            u32 elements;
            u32 element_size;
            DtorFunc dtor;
            char *ptr;
            u32 n;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &localarray);
            p = DecodeVarUInt_100ed0(p, &elements);
            p = DecodeVarUInt_100ed0(p, &element_size);
            p = GetDtorFunc(p, &dtor);
            ptr = context->FP + localarray;
            n = elements;
            ptr += n * element_size;
            for (; n != 0; n--) {
                ptr -= element_size;
                dtor(ptr, -1);
            }
            info->action_pointer = p;
            break;
        }
        case 6: {
            s32 objectptr;
            s32 offset;
            DtorFunc dtor;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &objectptr);
            p = DecodeVarInt_100f70(p, &offset);
            p = GetDtorFunc(p, &dtor);
            dtor((regvar ? (char *)(s32)context->regs.r[objectptr] : *(char **)(context->FP + objectptr)) + offset, 0);
            info->action_pointer = p;
            break;
        }
        case 7: {
            s32 objectptr;
            s32 offset;
            DtorFunc dtor;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &objectptr);
            p = DecodeVarInt_100f70(p, &offset);
            p = GetDtorFunc(p, &dtor);
            dtor((regvar ? (char *)(s32)context->regs.r[objectptr] : *(char **)(context->FP + objectptr)) + offset, -1);
            info->action_pointer = p;
            break;
        }
        case 8: {
            s32 cond;
            s32 objectptr;
            s32 offset;
            DtorFunc dtor;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &cond);
            p = DecodeVarInt_100f70(p, &objectptr);
            p = DecodeVarInt_100f70(p, &offset);
            p = GetDtorFunc(p, &dtor);
            if ((action & 0x40) ? (s8)context->regs.r[cond] : *(s8 *)(context->FP + cond)) {
                dtor((regvar ? (char *)(s32)context->regs.r[objectptr] : *(char **)(context->FP + objectptr)) + offset, -1);
            }
            info->action_pointer = p;
            break;
        }
        case 9: {
            s32 objectptr;
            s32 offset;
            u32 elements;
            u32 element_size;
            DtorFunc dtor;
            char *ptr;
            u32 n;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &objectptr);
            p = DecodeVarInt_100f70(p, &offset);
            p = DecodeVarUInt_100ed0(p, &elements);
            p = DecodeVarUInt_100ed0(p, &element_size);
            p = GetDtorFunc(p, &dtor);
            if (regvar) {
                ptr = (char *)(s32)context->regs.r[objectptr] + offset;
            } else {
                ptr = *(char **)(context->FP + objectptr) + offset;
            }
            n = elements;
            ptr += n * element_size;
            for (; n != 0; n--) {
                ptr -= element_size;
                dtor(ptr, -1);
            }
            info->action_pointer = p;
            break;
        }
        case 10: {
            s32 pointer;
            DeleteFunc del;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &pointer);
            p = GetDeleteFunc(p, &del);
            del(regvar ? (char *)(s32)context->regs.r[pointer] : *(char **)(context->FP + pointer));
            info->action_pointer = p;
            break;
        }
        case 11: {
            s32 cond;
            s32 pointer;
            DeleteFunc del;
            regvar = action & 0x20;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &cond);
            p = DecodeVarInt_100f70(p, &pointer);
            p = GetDeleteFunc(p, &del);
            if ((action & 0x40) ? (s8)context->regs.r[cond] : *(s8 *)(context->FP + cond)) {
                del(regvar ? (char *)(s32)context->regs.r[pointer] : *(char **)(context->FP + pointer));
            }
            info->action_pointer = p;
            break;
        }
        case 12: {
            char *catch_type;
            u32 pcoffset;
            s32 cinfo_ref;
            if (catcher == info->action_pointer) {
                return;
            }
            p = GetCatchType(info->action_pointer, (void **)&catch_type);
            p = DecodeVarUInt_100ed0(p, &pcoffset);
            info->action_pointer = DecodeVarInt_100f70(p, &cinfo_ref);
            break;
        }
        case 13: {
            s32 cinfo_ref;
            CatchInfo *ci;
            p = DecodeVarInt_100f70(info->action_pointer + 1, &cinfo_ref);
            ci = (CatchInfo *)(context->FP + cinfo_ref);
            if (ci->dtor) {
                if (context->location == ci->location) {
                    context->dtor = ci->dtor;
                } else {
                    ((DtorFunc)ci->dtor)(ci->location, -1);
                }
            }
            info->action_pointer = p;
            break;
        }
        case 15: {
            u32 specs;
            u32 pcoffset;
            s32 cinfo_ref;
            if (catcher == info->action_pointer) {
                return;
            }
            p = DecodeVarUInt_100ed0(info->action_pointer + 1, &specs);
            p = DecodeVarUInt_100ed0(p, &pcoffset);
            p = DecodeVarInt_100f70(p, &cinfo_ref);
            info->action_pointer = p + specs * 4;
            break;
        }
        case 0: case 14:
        default:
            Terminate_100ce0();
            break;
        }
        if (action & 0x80) {
            info->action_pointer = 0;
        }
    }
}
