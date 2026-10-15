#pragma optimization_level 3
#include "types.h"

extern s32 ArchiveGetFileByPath_1c2800(s32 arg0, void *arg1, s32 *arg2);
extern s32 PathFindFileName_368b60(void *arg0, s32 arg1);
extern s32 DataTableRunEntryUpdateCfg_41cae0(void *arg0, s32 arg1, s32 arg2);
extern void strcat(void *arg0, s32 arg1);
extern void strcpy(void *arg0, s32 arg1);
extern s32 D_0047FFE0;

#pragma opt_common_subs off
s32 DataTableRunEntryUpdateCfgFromArchive_41cba0(void *arg0, s32 arg1, s32 arg2)
{
    s32 sp7C;
    u8 sp30[0x4C];
    s32 r;
    void *t;
    void *u;

    if (arg1 == 0) {
        return 0;
    }
    t = *(void **)((u8 *)arg0 + 0x10);
    if (t == NULL) {
        return 0;
    }
    if (*(s32 *)((u8 *)t + 0x34) <= 0) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    strcpy(sp30, PathFindFileName_368b60(u, arg2));
    strcat(sp30, D_0047FFE0);
    sp7C = 0;
    r = ArchiveGetFileByPath_1c2800(arg1, sp30, &sp7C);
    if (r == 0 || sp7C <= 0) {
        return 0;
    }
    return DataTableRunEntryUpdateCfg_41cae0(arg0, r, sp7C);
}
