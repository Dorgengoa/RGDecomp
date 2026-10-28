/* rgp:protos */
#define RGP_SELF_EvCmdOptionsGet_2408b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Twin of EvCmdOptionsSet_240930 -- adjacent address, identical frame, identical
   seven-case shape, adjacent slot.  jtbl_0045E9C0: entries 0-4 and 6 -> the
   shared epilogue, entry 5 -> the only arm.  Read EvCmdOptionsSet_240930.c's comment
   first; the post-increment argument is the whole lesson and it transfers
   verbatim.

   The +0x1C s16 read (`lh $5,0x1C($16)`) is the same field
   src/leaves/OptionsSetDrawMessage_3d6020.c already names, so r0->m0C points at that object
   type -- which is also what the twin passes to OptionsSetDrawMessage_3d6020.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  EvCmdOptionsGet_2408b0  0045E9C0  1C   # jtbl_0045E9C0, 7 cases */

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj1 {
    u8 pad000[0x1C];
    s16 m1C;
};

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Cmd {
    s32 a;
    s32 b;
};

s32 EvCmdOptionsGet_2408b0(struct Cmd *p0, s32 p1)
{
    struct Obj0 *r0;
    struct Obj1 *t0;
    s32 r1;

    r0 = GetGameData_1fede0();
    t0 = r0->m0C;
    r1 = ScriptGetInt_2490f0((s32)p0++);
    switch (r1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    case 5:
        ScriptSetRefInt_249030((s32)p0, t0->m1C);
        break;
    case 6:
        break;
    }
    return 1;
}
