/* rgp:protos */
#define RGP_SELF_FieldControlActivate_27a960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F920[];
extern u8 D_0045F930[];
extern u8 D_0045F940[];

s32 FieldControlActivate_27a960(void)
{
    s32 r0;
    s32 rv8;
    s32 r1;
    s32 rv5;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r6;
    s32 r7;

    r0 = ((unsigned char)GetFieldControlActive_27bd40());
    rv8 = r0;
    if (r0 == 0) {
        r1 = FieldControlBeginMaybe_2f13b0();
        rv5 = (r1 & 0xFF);
        if ((r1 & 0xFF) != 0) {
            r2 = TaskSetEnabled_27c2a0(1, D_0045F920);
            r3 = TaskSetEnabled_27c2a0(1, D_0045F940);
            r4 = TaskSetEnabled_27c2a0(1, D_0045F930);
            rv5 = r4;
        }
        r6 = (SetFieldControlActive_27bd30(1), (s32)0);
        r7 = (SetTaskListChanged_1f56b0(1), (s32)0);
        rv8 = r7;
    }
    return rv8;
}
