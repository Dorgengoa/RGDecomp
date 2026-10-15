#include "types.h"

extern u8 D_00451F00[];
extern u8 D_004E69D0[];

extern void *ScriptArgGetStr_301a00(void);
extern void *ParseFlagNames_1ca700(void *a, void *b, s32 c);
extern void EvObjSetFlags_2f9cb0(void *a, void *b);

s32 EvScriptCmdDoorObjSetFlags_2ff4b0(s32 a, s32 mode)
{
    void *x;
    void *y;

    if (mode != 1) return 0;
    x = ScriptArgGetStr_301a00();
    y = ParseFlagNames_1ca700(x, D_00451F00, 0);
    EvObjSetFlags_2f9cb0(D_004E69D0, y);
    return 1;
}
