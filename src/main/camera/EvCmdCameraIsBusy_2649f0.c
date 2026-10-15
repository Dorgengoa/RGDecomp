#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern s32 EventCameraIsIdle_254a40(s32);
extern void ScriptSetRefInt_26a1e0(s32, u8);
extern s32 D_00482060;

/* the operand cursor is NOT advanced here -- retail passes $4 = the incoming
   pointer verbatim.  `sltu $2,$0,$2 / xori 1 / andi 0xFF` is the boolean
   negation narrowed to the u8 parameter.  `== 0` folds to a single `sltiu`
   and is ONE WORD SHORT; `!x`, `(x != 0) ^ 1`, `!(x != 0)`, `x ? 0 : 1` and
   `b = x != 0; b ^ 1` are ONE object and all match. */
s32 EvCmdCameraIsBusy_2649f0(Cmd *p0)
{
    ScriptSetRefInt_26a1e0((s32)p0, !EventCameraIsIdle_254a40(D_00482060));
    return 1;
}
