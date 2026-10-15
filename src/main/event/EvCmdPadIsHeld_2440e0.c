#include "types.h"

typedef struct E8_FUN_002440e0 {
    s32 a;
    s32 b;
} E8_FUN_002440e0;

extern u8 D_004B2570[];
extern void *ScriptGetInt_2490f0(E8_FUN_002440e0 *p);
extern void *PadIsHeld_183a20(u8 *a, void *b);
extern void ScriptSetRefInt_249030(E8_FUN_002440e0 *p, void *b);

s32 EvCmdPadIsHeld_2440e0(E8_FUN_002440e0 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_2490f0(q++);
    b = PadIsHeld_183a20(D_004B2570, a);
    ScriptSetRefInt_249030(q, b);
    return 1;
}
