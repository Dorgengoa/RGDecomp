/* rgp:protos */
#define RGP_SELF_StateBlockCreate_3cd800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 StateBlockCreate_3cd800(struct Obj0 *p0, s32 p1, int rgp_a2, int rgp_a3)
{
    s32 rv6;
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;
    s32 rv5;
    s32 r4;

    rv6 = rv5;
    if (p1 == 0) {
        rv6 = 0;
    } else {
        r0 = (StateBlockInit_3cd890(p0, (int)p1, (int)rgp_a2, (int)rgp_a3), (s32)0);
        r1 = ((s32)MemStackNew_14e130(0x20, p1));
        rv3 = r1;
        if (r1 != 0) {
            r2 = ((s32)StateTablesCtor_421590(r1));
            p0->m04 = r2;
            rv3 = r2;
        } else {
            p0->m04 = r1;
            rv3 = r1;
        }
        rv5 = 1;
        if (rv3 == 0) {
            rv5 = 0;
        } else {
            if (rv3 != 0) {
                r4 = StateTablesInit_421310(rv3, p1);
            }
            rv5 = 1;
        }
        rv6 = rv5;
    }
    return rv6;
}
