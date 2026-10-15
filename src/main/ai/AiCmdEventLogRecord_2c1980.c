/* PARK: 2 rounds (ScriptSlotGetInt_2cc9c0(0) vs ScriptSlotGetInt_2cc9c0(arg0) for the first call --
   no size change either way). length 0x138 vs retail 0x13C (4 short).
   objdump shows retail promotes arg1 to a callee-saved reg (s1) UNCONDITIONALLY
   in the entry branch's delay slot (before even testing D_004825DC), and
   folds arg0+8 into ONE register reused for both later uses; ours computes
   arg0+8 fresh at the second call site instead. Register-scheduling/creation-
   order residue, not a value bug. Not re-tried further. */
#include "types.h"

extern s32 Rand_133710(void);
extern void *GetGameData_1fede0(void);
extern void FieldHudLogOpen_203fb0(void);
extern s32 ScriptSlotGetInt_2cc9c0(s32 arg0);
extern s32 ScriptStrTableGet_2ccd90(s32 arg0);
extern s32 CharaEventLogRecord_3a62f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void CharaEventLogKeyRemove_3a6760(s32 arg0, s32 arg1);
extern void CharaEventLogKeyAdd_3a6830(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_0047EE10;
extern s32 D_004825DC;
extern s32 D_004DB928[];

s32 AiCmdEventLogRecord_2c1980(u64 *arg0, s32 arg1)
{
    s32 var_18;
    s32 temp_17;
    s32 var_17;
    s32 temp_16;

    if (D_004825DC == 0) {
        return 0;
    }
    var_18 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    var_17 = -2;
    if (arg1 >= 2) {
        var_17 = ScriptSlotGetInt_2cc9c0((s32)arg0);
    }
    temp_16 = *(s32 *)((u8 *)*(void **)((u8 *)GetGameData_1fede0() + 0x20) + 0x244);
    if (temp_16 != 0) {
        if (ScriptStrTableGet_2ccd90(var_18) != 0) {
            var_17 = -2;
            var_18 = (var_18 % 249) + 0x7F00;
        } else {
            if (var_18 < 0) {
                do {
                    var_18 = (Rand_133710() % 249) + 0x7F00;
                } while (var_18 == D_0047EE10);
            }
            if (var_17 < 0) {
                var_18 = -1;
            }
        }
        if (var_18 >= 0) {
            CharaEventLogKeyAdd_3a6830(temp_16, var_18, 0);
            temp_17 = CharaEventLogRecord_3a62f0(temp_16, var_18, D_004DB928[0], var_17, 1) & 0xFF;
            CharaEventLogKeyRemove_3a6760(temp_16, var_18);
            if (temp_17 != 0) {
                FieldHudLogOpen_203fb0();
            }
            D_0047EE10 = var_18;
        }
    }
    return 1;
}
