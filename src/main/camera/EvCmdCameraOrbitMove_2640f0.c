#include "types.h"

/* Script-command handler family (TaggedGetFloat_26a280 = f32 operand fetch,
   ScriptGetInt_26a2a0 = s32 operand fetch; the operand cursor is an 8-byte cell
   post-incremented in the jal delay slot -- same idiom as EvCmdMesWinSetParam_265f00). */

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
/* LEVER (new): the ARGUMENT SETUP ORDER in the listing is the source
   parameter order even though the GPR and FPR pools are independent --
   retail interleaves i1,f1,f2,i2,f3,i3,f4, so the prototype does. */
extern void EventCameraNodeAddOrbitMove_253be0(s32, f32, f32, s32, f32, s32, f32);
extern s32 D_00482060;

s32 EvCmdCameraOrbitMove_2640f0(Cmd *p0)
{
    /* three callee-saved FPRs, first declared = highest ($f22,$f21,$f20) */
    f32 x, y, z;
    s32 a, b;

    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    z = TaggedGetFloat_26a280((s32)p0++);
    a = ScriptGetInt_26a2a0((s32)p0++);
    b = ScriptGetInt_26a2a0((s32)p0++);
    /* the last fetch is inline: retail keeps it in $f0 and only then loads
       the gp handle into $4 */
    EventCameraNodeAddOrbitMove_253be0(D_00482060, x, y, a, z, b, TaggedGetFloat_26a280((s32)p0));
    return 1;
}
