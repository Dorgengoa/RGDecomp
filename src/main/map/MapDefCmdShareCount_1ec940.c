#include "types.h"

typedef struct {
    u8 pad0[0x58];
} Templ001DD970;

typedef struct {
    u8 pad0[0x38];
    s16 unk38;
    u8 pad3A[0x40 - 0x3A];
    s32 unk40;
} Obj001DCF20;

s32 ConstructNewArray_100710(s32, Templ001DD970 *, s32, s32, s32); /* extern */
s32 MemStackNew_14e1b0(s32, s32);                         /* extern */
Obj001DCF20 *MapAreaDefGetRecTable_1dcf20(s32);                     /* extern */
s32 ScriptArgGetInt_1ecbe0(s32);                              /* extern */
extern s32 D_004818F8;
extern s32 D_004818FC;
extern Templ001DD970 MapShareCtor_1dd970;

s32 MapDefCmdShareCount_1ec940(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;
    Obj001DCF20 *temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    temp_16 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    temp_2 = ScriptArgGetInt_1ecbe0(arg0);
    temp_2_2 = ConstructNewArray_100710(MemStackNew_14e1b0((temp_2 * 0x58) + 0x10, D_004818F8), &MapShareCtor_1dd970, 0, 0x58, temp_2);
    temp_16->unk40 = temp_2_2;
    if (temp_2_2 != 0) {
        temp_16->unk38 = temp_2;
    }
    return 1;
}
