#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32, s16);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void *EffectFindByName_2dfe10(s32, s32, s16 *);
extern char *strcpy(char *, const char *);
extern u8 D_00461758[];

s32 EffectEntriesFindTexByName_2de7d0(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
    s16 sp8E;
    u8 sp60[0x2E];
    s32 temp_16;
    s32 temp_17;
    void *temp_2;

    sp8E = -1;
    temp_2 = EffectFindByName_2dfe10(arg0, arg1, &sp8E);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_17 = GetDrawCtxNameTable_15de40();
    Sprintf_1343b8(sp60, D_00461758, arg2, sp8E);
    temp_16 = *(s16 *)((u8 *)temp_2 + 0x14);
    if (arg3 != NULL) {
        *arg3 = temp_16;
    }
    if (arg4 != 0) {
        strcpy((char *) arg4, (char *) sp60);
    }
    return NameTableFindByName_159fb0(temp_17, sp60, temp_16);
}
