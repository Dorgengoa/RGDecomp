/* rgp:protos */
#define RGP_SELF_TaskStepMinimap_1ffcb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x30];
    s16 m30;
};

void TaskStepMinimap_1ffcb0(void)
{
    struct Obj0 *r0;
    s32 r1;
    s16 t1;

    r0 = GetGameData_1fede0();
    r1 = ((s32)GetMapMgr_201a90());
    t1 = r0->m18->m30;
    MapMgrMinimapUpdate_1e2860(r1, t1);
}
