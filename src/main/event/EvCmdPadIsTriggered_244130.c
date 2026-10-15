#include "types.h"

typedef struct E8_FUN_00244130 {
    s32 a;
    s32 b;
} E8_FUN_00244130;

extern u8 D_004B2570[];
extern void *ScriptGetInt_2490f0(E8_FUN_00244130 *p);
extern void *PadIsTriggered_1839f0(u8 *a, void *b);
extern void ScriptSetRefInt_249030(E8_FUN_00244130 *p, void *b);

s32 EvCmdPadIsTriggered_244130(E8_FUN_00244130 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_2490f0(q++);
    b = PadIsTriggered_1839f0(D_004B2570, a);
    ScriptSetRefInt_249030(q, b);
    return 1;
}
