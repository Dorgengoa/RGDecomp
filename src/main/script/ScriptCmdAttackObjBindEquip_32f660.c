#include "types.h"

u8 *GetGameData_1fede0();                               /* extern */
s32 FieldHudLogOpen_203fb0();                                   /* extern */
s32 IsInBattle_288420();                                 /* extern */
s32 GetObjRefTable_313de0();                                 /* extern */
s32 JudgeObjectSyncOwner_314440(u8 *);                             /* extern */
u8 *HandleRegistryLookup_314aa0(s32, s32);                       /* extern */
s32 ScriptSlotGetCodeAddr_334870(s32);                              /* extern */
s32 ScriptSlotGetInt_3348b0(s32);                              /* extern */
s32 CharaSysEventLogKeyAdd_3a33b0(s32, s32, s32);                        /* extern */
s32 ExecInfoInitFromEquipSlotByName_3a7500(u8 *, s32, s32, s32);              /* extern */

s32 ScriptCmdAttackObjBindEquip_32f660(s32 arg0, s32 arg1) {
    s32 id;
    u8 *t;
    u8 *p;
    s32 a;
    u8 *t2;
    s32 b;

    if (arg1 != 3) {
        return 0;
    }
    if (IsInBattle_288420() == 0) {
        return 1;
    }
    id = ScriptSlotGetInt_3348b0(arg0);
    t = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), id);
    if (t == 0) {
        return 1;
    }
    a = *(s16 *)(t + 0x86);
    p = t + 0x10;
    b = ScriptSlotGetCodeAddr_334870(arg0 + 8);
    ExecInfoInitFromEquipSlotByName_3a7500(p, a, b, ScriptSlotGetCodeAddr_334870(arg0 + 0x10));
    JudgeObjectSyncOwner_314440(t);
    t2 = GetGameData_1fede0();
    *(s16 *)p = id;
    CharaSysEventLogKeyAdd_3a33b0(*(s32 *)(t2 + 0x20), id, 0);
    FieldHudLogOpen_203fb0();
    return 1;
}
