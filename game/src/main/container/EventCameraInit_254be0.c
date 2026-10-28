/* rgp:protos */
#define RGP_SELF_EventCameraInit_254be0 1
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
    s32 m04;
};

void EventCameraInit_254be0(struct Obj0 *p0, s32 p1, s32 p2)
{
    EventCameraClear_254c30(p0);
    p0->m00 = p1;
    p0->m04 = p2;
    EventCameraReset_254a90(p0);
}
