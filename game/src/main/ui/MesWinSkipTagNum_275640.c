/* rgp:protos */
#define RGP_SELF_MesWinSkipTagNum_275640 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F6CE[];
extern u8 D_0045F6CF[];

struct Obj0;

struct Obj0 {
    s32 m00;
};

void MesWinSkipTagNum_275640(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s8 t1;
    s32 t2;
    s8 t3;

    if ((p1 < 0xA) != 0) {
        t0 = p0->m00;
        t1 = *(s8 *)((u8 *)D_0045F6CE + (p2 << 1));
        p0->m00 = (t0 + t1);
    } else {
        t2 = p0->m00;
        t3 = *(s8 *)((u8 *)D_0045F6CF + (p2 << 1));
        p0->m00 = (t2 + t3);
    }
}
