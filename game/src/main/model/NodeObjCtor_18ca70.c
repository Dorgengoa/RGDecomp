/* rgp:protos */
#define RGP_SELF_NodeObjCtor_18ca70 1
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

extern u8 D_004705D0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x68];
    void *m68;
};

struct Obj0 *NodeObjCtor_18ca70(struct Obj0 *p0)
{
    s32 r0;
    s32 r3;

    r0 = ((s32)NodeCtor_18c5b0(p0));
    p0->m68 = D_004705D0;
    FuncDataTableCtor_18fbf0((struct Obj0 *)((u8 *)p0 + 0x114));
    TimeOfDayCtxCtor_18cac0((struct Obj0 *)((u8 *)p0 + 0x148));
    r3 = (NodeObjInit_1951b0(p0), (s32)0);
    return p0;
}
