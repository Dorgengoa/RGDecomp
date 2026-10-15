#include "types.h"

/* Known-positive sibling shape of EvCmdMenuHelpIsOpen_25bcd0 (byte-identical, in cunits). */

extern s32 InsectEntryMenuResReady_203390(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

s32 EvCmdMenuInsectEntryResReady_25c370(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = InsectEntryMenuResReady_203390();
    r1 = ScriptSetRefInt_26a1e0(p0, (r0 & 0xFF));
    return 1;
}
