#include "types.h"

typedef struct Ent {
    u8 pad0[0x80];
    s16 m80;
    s16 m82;
    u8 pad84[0x14];
} Ent;

typedef struct Mgr {
    u8 pad0[0x10];
    Ent *m10;
    u8 pad14[0xC];
    u8 m20[0x10];
} Mgr;

extern void PathLocalize_1c28c0(char *);
extern s32 LoaderAllocId_1cdb40(Mgr *);
extern s32 LoaderFindFreeUnit_1cdc20(Mgr *);
extern Ent *LoaderGetUnit_1cde10(Mgr *, s16);
extern void S16ArrayAppend_1ce110(void *, s32);
extern s32 S16ArrayGetChecked_1ce170(void *, s32);
extern s32 S16ArrayGetCount_1ce1b0(void *);
extern s16 *S16ArrayGetData_1ce1c0(void *);
extern void LoaderUnitInit_1ce260(Ent *, s32, char *, s32, s32, s32);
extern s32 strcmp(const char *, const char *);

s16 LoaderRequestFileEx_1cd6c0(Mgr *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    char buf[0x80];
    s16 *p;
    s32 n;
    s32 start;
    s32 i;
    Ent *e;
    s32 idx;

    if (arg0->m10 == NULL) {
        return -1;
    }
    if (arg1 == 0) {
        return -1;
    }
    PathLocalize_1c28c0(buf);
    if (S16ArrayGetData_1ce1c0(arg0->m20) != NULL) {
        p = S16ArrayGetData_1ce1c0(arg0->m20);
        n = S16ArrayGetCount_1ce1b0(arg0->m20);
        start = 0;
        for (i = 0; i < n; i++, p++) {
            if (*p == 0x3FFF) {
                start = i + 1;
            }
        }
        for (; start < n; start++) {
            e = LoaderGetUnit_1cde10(arg0, S16ArrayGetChecked_1ce170(arg0->m20, start));
            if (e == NULL) {
                continue;
            }
            if (strcmp((char *)e, buf) != 0) {
                continue;
            }
            if (e->m82 == 1) {
                e->m82 = 0;
            }
            return -1;
        }
    }
    idx = LoaderFindFreeUnit_1cdc20(arg0);
    if (idx < 0) {
        return -1;
    }
    e = &arg0->m10[idx];
    LoaderUnitInit_1ce260(e, LoaderAllocId_1cdb40(arg0), buf, arg2, arg3, 0);
    S16ArrayAppend_1ce110(arg0->m20, idx);
    return e->m80;
}
