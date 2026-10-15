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
extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);
extern u8 *DecodeVarInt_100f70(u8 *p, s32 *pval);
extern char *EhUnwindRestoreRegs_102770(ThrowContext *context, MWExceptionInfo *info);
extern void EhFindCallSite_102380(char *retaddr, MWExceptionInfo *info);
extern void EhParseHeader_1026c0(ThrowContext *context, MWExceptionInfo *info);

#define LE32(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))

static inline u8 *GetCatchType(u8 *ap, void **out)
{
    *out = (void *)LE32(ap + 1);
    return ap + 5;
}

s32 EhSkipActions_102070(ActionIterator *iter)
{
    s32 action;
    s32 a_local;
    s32 b_cond, b_local;
    s32 c_pointer;
    s32 d_localarray; u32 d_elements, d_element_size;
    s32 e_objectptr, e_offset;
    s32 f_objectptr, f_offset;
    s32 g_cond, g_objectptr, g_offset;
    s32 h_objectptr, h_offset; u32 h_elements, h_element_size;
    s32 i_pointer;
    s32 j_cond, j_pointer;
    char *k_catch_type; u32 k_pcoffset; s32 k_cinfo_ref;
    s32 l_cinfo_ref;
    u32 m_specs, m_pcoffset; s32 m_cinfo_ref;
    s32 n_offset;
    u8 *p;
    ThrowContext *context = &iter->context;

    for (;;) {
        if (!iter->info.action_pointer || ((action = *iter->info.action_pointer) & 0x80)) {
            EhFindCallSite_102380(EhUnwindRestoreRegs_102770(context, &iter->info), &iter->info);
            if (iter->info.exception_record == 0) {
                Terminate_100ce0();
            }
            EhParseHeader_1026c0(context, &iter->info);
            if (iter->info.action_pointer == 0) {
                continue;
            }
            break;
        }
        switch (action & 0x1F) {
        case 2:
            iter->info.action_pointer = DecodeVarInt_100f70(iter->info.action_pointer + 1, &a_local) + 4;
            break;
        case 3:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &b_cond);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &b_local) + 4;
            break;
        case 4:
            iter->info.action_pointer = DecodeVarInt_100f70(iter->info.action_pointer + 1, &c_pointer) + 4;
            break;
        case 5:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &d_localarray);
            p = DecodeVarUInt_100ed0(p, &d_elements);
            iter->info.action_pointer = DecodeVarUInt_100ed0(p, &d_element_size) + 4;
            break;
        case 6:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &e_objectptr);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &e_offset) + 4;
            break;
        case 7:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &f_objectptr);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &f_offset) + 4;
            break;
        case 8:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &g_cond);
            p = DecodeVarInt_100f70(p, &g_objectptr);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &g_offset) + 4;
            break;
        case 9:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &h_objectptr);
            p = DecodeVarInt_100f70(p, &h_offset);
            p = DecodeVarUInt_100ed0(p, &h_elements);
            iter->info.action_pointer = DecodeVarUInt_100ed0(p, &h_element_size) + 4;
            break;
        case 10:
            iter->info.action_pointer = DecodeVarInt_100f70(iter->info.action_pointer + 1, &i_pointer) + 4;
            break;
        case 11:
            p = DecodeVarInt_100f70(iter->info.action_pointer + 1, &j_cond);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &j_pointer) + 4;
            break;
        case 12:
            p = GetCatchType(iter->info.action_pointer, (void **)&k_catch_type);
            p = DecodeVarUInt_100ed0(p, &k_pcoffset);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &k_cinfo_ref);
            break;
        case 13:
            iter->info.action_pointer = DecodeVarInt_100f70(iter->info.action_pointer + 1, &l_cinfo_ref);
            break;
        case 15:
            p = DecodeVarUInt_100ed0(iter->info.action_pointer + 1, &m_specs);
            p = DecodeVarUInt_100ed0(p, &m_pcoffset);
            iter->info.action_pointer = DecodeVarInt_100f70(p, &m_cinfo_ref) + m_specs * 4;
            break;
        case 0: case 1: case 14:
        default:
            Terminate_100ce0();
            break;
        }
        break;
    }
    while ((action = *iter->info.action_pointer & 0x1F) == 1) {
        DecodeVarInt_100f70(*(u8 **)&iter->info.action_pointer + 1, &n_offset);
        iter->info.action_pointer += n_offset;
    }
    return action;
}
