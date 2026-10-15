#include "types.h"

typedef struct E8_FUN_0032eee0 {
    s32 a;
    s32 b;
} E8_FUN_0032eee0;

typedef struct R_FUN_0032eee0 {
    u8 pad000[0xBE];
    s16 mBC;
} R_FUN_0032eee0;

extern void *GetObjRefTable_313de0(void);
extern s32 ScriptSlotGetInt_3348b0(E8_FUN_0032eee0 *p);
extern R_FUN_0032eee0 *HandleRegistryLookup_314aa0(void *a, s32 t);

s32 ScriptCmdAttackObjSetWallFxFlagsMaybe_32eee0(E8_FUN_0032eee0 *q, s32 mode)
{
    void *a;
    R_FUN_0032eee0 *b;
    s32 t;

    if (mode != 2) return 0;
    a = GetObjRefTable_313de0();
    t = ScriptSlotGetInt_3348b0(q);
    b = HandleRegistryLookup_314aa0(a, t);
    if (b == 0) return 1;
    b->mBC = ScriptSlotGetInt_3348b0(q + 1);
    return 1;
}
