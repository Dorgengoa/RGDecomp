#include "types.h"

typedef struct {
    u8 pad0[0x3A];
    s16 unk3A;
    u8 pad3C[0x44 - 0x3C];
    s32 unk44;
} Obj001dcf20;

extern s32 ConstructNewArray_100710(s32, const void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern Obj001dcf20 *MapAreaDefGetRecTable_1dcf20(s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern s32 ScriptArgGetInt_1ecbe0(s32);
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s32 MapBlockCtor_1dd920(s32);

s32 MapDefCmdBlockCount_1ec860(s32 arg0, s32 arg1)
{
    s32 var_17;
    s32 temp_2;
    Obj001dcf20 *temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004818FC != 0 && D_004818F8 != 0) {
        goto body;
    }
    return 1;
body:
    temp_16 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    var_17 = ScriptArgGetInt_1ecbe0(arg0);
    if (MapDataGetId_1e7bd0(D_004818FC) == 0x6A4) {
        var_17 += 0x140;
    }
    temp_2 = ConstructNewArray_100710(MemStackNew_14e1b0((var_17 * 0xCC) + 0x10, D_004818F8), (const void *)MapBlockCtor_1dd920, 0, 0xCC, var_17);
    temp_16->unk44 = temp_2;
    if (temp_2 != 0) {
        temp_16->unk3A = var_17;
    }
    return 1;
}
