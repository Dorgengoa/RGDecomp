#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x14 - 8];
    s32 unk14;
} Deep0025F7B0;

typedef struct {
    u8 pad0[0x1188];
    Deep0025F7B0 *unk1188;
} Mid0025F7B0;

typedef struct {
    u8 pad0[0x24];
    Mid0025F7B0 *unk24;
} Ctx0025F7B0;

typedef struct {
    u8 pad0[4];
    s32 unk4;
} Obj00430B90;

Ctx0025F7B0 *GetGameData_1fede0();                        /* extern */
void ScriptSetRefInt_26a1e0(s32, s32);                        /* extern */
Obj00430B90 *RecordGetPayloadIfKind14_430b90(Mid0025F7B0 *);           /* extern */

s32 EvCmdRecordGetKind_25f7b0(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_18;
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_5;
    s32 var_18;
    s32 var_20;
    Ctx0025F7B0 *temp_2;
    Deep0025F7B0 *temp_2_2;
    Obj00430B90 *temp_2_3;

    var_20 = arg0;
    temp_2 = GetGameData_1fede0();
    temp_2_2 = temp_2->unk24->unk1188;
    /* ORDER IS LOAD ORDER, ROTATED: three adjacent field reads come out
       (2nd, 3rd, 1st) of the source order, so retail's unk4/unk14/unk0
       emission needs unk0/unk4/unk14 written here.
       [[levers.d/mwcc-elementwise-fill-rotation]]. All six permutations
       measured: this one MATCHes, two more are 2 bad, two are 3. */
    temp_16 = temp_2_2->unk0;
    temp_5 = temp_2_2->unk4;
    temp_18 = temp_2_2->unk14;
    if (arg1 > 0) {
        temp_4 = var_20;
        var_20 += 8;
        ScriptSetRefInt_26a1e0(temp_4, temp_5);
    }
    if (arg1 >= 2) {
        temp_4_2 = var_20;
        var_20 += 8;
        ScriptSetRefInt_26a1e0(temp_4_2, temp_18);
    }
    var_18 = 0;
    if (temp_16 == 2) {
        temp_2_3 = RecordGetPayloadIfKind14_430b90(temp_2->unk24);
        if (temp_2_3 != NULL) {
            var_18 = temp_2_3->unk4;
        }
    }
    if (arg1 >= 3) {
        ScriptSetRefInt_26a1e0(var_20, var_18);
    }
    return 1;
}
