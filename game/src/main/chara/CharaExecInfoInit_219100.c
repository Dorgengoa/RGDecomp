/* rgp:protos */
#define RGP_SELF_CharaExecInfoInit_219100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x6C];
    s32 m6C;
    u8 m70;
    u8 m71;
};

void CharaExecInfoInit_219100(struct Obj0 *p0)
{
    ExecInfoInit_3a7940(p0);
    p0->m6C = -1;
    p0->m70 = 0;
    p0->m71 = 0;
}
