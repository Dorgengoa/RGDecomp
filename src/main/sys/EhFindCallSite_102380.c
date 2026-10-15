#include "types.h"

typedef struct ExceptionTableIndex {
    u32 functionoffset;
    u32 functionsize;
    char *exceptionoffset;
} ExceptionTableIndex;

typedef struct MWExceptionInfo {
    char *code_section;
    char *exception_record;
    u8 *action_pointer;
    ExceptionTableIndex *exception_table_start;
    ExceptionTableIndex *exception_table_end;
} MWExceptionInfo;

extern s32 EhFindExceptionTableMaybe_102690(MWExceptionInfo *info, char *retaddr);
extern u8 *EhSkipHeaderVarUInts_102640(char *rec);
extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);
static inline ExceptionTableIndex *FindIndex(ExceptionTableIndex *exceptionindex, s32 count, u32 returnoffset)
{
    ExceptionTableIndex *p;
    s32 i, m, n;

    for (i = 0, n = count - 1; i <= n;) {
        p = &exceptionindex[m = (i + n) >> 1];
        if (returnoffset < p->functionoffset) {
            n = m - 1;
        } else if (returnoffset > p->functionoffset + (p->functionsize & ~1)) {
            i = m + 1;
        } else {
            return p;
        }
    }
    return 0;
}

void EhFindCallSite_102380(char *returnaddr, MWExceptionInfo *info)
{
    ExceptionTableIndex *p;
    u32 returnoffset;
    u8 *ap;
    u32 offset, start, size, action;

    info->exception_record = 0;
    info->action_pointer = 0;
    if (EhFindExceptionTableMaybe_102690(info, returnaddr) == 0) return;
    returnoffset = (s64)(s32)returnaddr & ~1;
    p = FindIndex(info->exception_table_start, info->exception_table_end - info->exception_table_start, returnoffset);
    if (p == 0) return;
    if (p->functionsize & 1) {
        info->exception_record = (char *)&p->exceptionoffset;
    } else {
        info->exception_record = p->exceptionoffset;
    }
    info->code_section = (char *)p->functionoffset;
    returnoffset -= p->functionoffset;
    ap = EhSkipHeaderVarUInts_102640(info->exception_record);
    offset = 0;
    for (;;) {
        ap = DecodeVarUInt_100ed0(ap, &start);
        if (start == 0) return;
        ap = DecodeVarUInt_100ed0(ap, &size);
        ap = DecodeVarUInt_100ed0(ap, &action);
        offset += start;
        if (returnoffset < offset) return;
        offset += size;
        if (returnoffset <= offset) {
            info->action_pointer = (u8 *)info->exception_record + action;
            return;
        }
    }
}
