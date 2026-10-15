#include "types.h"

/* Script-command handler, structural twin of src/wf/main/EvCmdOptionsSet_240930.c:
   GetGameData_1fede0() result held in a callee-saved register across the dispatch,
   and the `addiu $17,$17,0x8` is the POST-INCREMENT ON A POINTER USED AS THE
   CALL ARGUMENT (the 12-arm measured null recorded in EvCmdOptionsSet_240930.c: every
   other spelling folds the +8 into the argument and is one word short).

   jtbl_00461510 is 13 entries; only index 10 has a body, the other twelve
   point at the shared epilogue, so the source still spells THIRTEEN cases.
   The `lw 0xC($16)` / `lh 0x1E($2)` pair is INSIDE the arm, so the accessor's
   result is dereferenced there and not before the dispatch.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  AiCmdOptionsGet_2c5d80  00461510  34   # jtbl_00461510, 13 cases */

extern void *GetGameData_1fede0(void);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

struct Obj1 {
    u8 pad000[0x1E];
    s16 m1E;
};

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Cmd {
    s32 a;
    s32 b;
};

s32 AiCmdOptionsGet_2c5d80(struct Cmd *p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r1;

    r0 = GetGameData_1fede0();
    r1 = ScriptSlotGetInt_2cc9c0((s32)p0++);
    switch (r1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    case 10:
        ScriptSlotStoreIntRef_2cc900((s32)p0, r0->m0C->m1E);
        break;
    case 11:
    case 12:
        break;
    }
    return 1;
}
