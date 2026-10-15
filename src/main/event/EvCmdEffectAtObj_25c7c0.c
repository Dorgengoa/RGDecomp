#include "types.h"
#include "vec.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Ctx002E1020;

typedef struct {
    u8 pad0[0x180];
    u128 unk180;
} Obj001C4A90;

Obj001C4A90 *ObjRecGetLiveObject_1c4a90(s32, s32);                /* extern */
s32 ScriptGetCodeAddr_26a200(s32);                              /* extern */
s32 ScriptGetInt_26a2a0(s32);                              /* extern */
s32 GetEffectMgr_2d9040();                                 /* extern */
void EffectSetId_2e0100(s32, Ctx002E1020 *, s32);         /* extern */
void EffectSetPos_2e0bb0(s32, Ctx002E1020 *, void *);      /* extern */
void EffectCreateByName_2e1020(Ctx002E1020 *, s32, s32, s32);    /* extern */
extern s32 D_00481F78;

s32 EvCmdEffectAtObj_25c7c0(s64 *arg0, s32 arg1) {
    Ctx002E1020 sp40;
    u128 sp30;
    s32 temp_17;
    u32 temp_2;
    Obj001C4A90 *temp_2_2;

    if (arg1 != 2) {
        return 0;
    }
    temp_17 = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(&sp40, temp_17, ScriptGetCodeAddr_26a200((s32)arg0++), -1);
    temp_2 = ScriptGetInt_26a2a0((s32)arg0);
    EffectSetId_2e0100(temp_17, &sp40, temp_2);
    temp_2_2 = ObjRecGetLiveObject_1c4a90(D_00481F78, temp_2);
    if (temp_2_2 != NULL) {
        sp30 = (u128) temp_2_2->unk180;
        EffectSetPos_2e0bb0(temp_17, &sp40, &sp30);
    }
    return 1;
}
