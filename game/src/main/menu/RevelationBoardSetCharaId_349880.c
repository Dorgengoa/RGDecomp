/* rgp:protos */
#define RGP_SELF_RevelationBoardSetCharaId_349880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x8];
    s32 m0C;
};

s32 RevelationBoardSetCharaId_349880(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;

    p0->m0C = p1;
    t0 = p0->m00;
    UiSetWidgetsVisibleById_291110(t0, 0x48, 1, 1);
    t1 = p0->m00;
    UiSetWidgetPos_290f60(t1, 0x48, 5, 1);
    return 0;
}
