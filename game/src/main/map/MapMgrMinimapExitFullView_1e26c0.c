/* rgp:protos */
#define RGP_SELF_MapMgrMinimapExitFullView_1e26c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
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
    u8 pad000[0x60];
    s32 m60;
    u8 pad064[0x223C];
    s32 m22A0;
    s32 m22A4;
    s32 m22A8;
    s32 m22AC;
};

void MapMgrMinimapExitFullView_1e26c0(struct Obj0 *p0)
{
    s32 r3;
    struct Obj0 * l6;
    s32 l5;
    s32 t0;

    GetGameData_1fede0();
    GetActionMgr_1fdb50();
    GetMapMgr_201a90();
    r3 = ((s32)GetMinimapMgr_201a70());
    MinimapMgrRefreshAll_3219a0(r3);
    l6 = (struct Obj0 *)((u8 *)p0 + 0x1928);
    l5 = 0;
    do {
        MinimapSetNormalView_1d9c20(l6);
        l5 = (l5 + 1);
        l6 = (struct Obj0 *)((u8 *)l6 + 0x1CC);
    } while (l5 < 4);
    p0->m22A0 = 0;
    p0->m22A4 = 0;
    p0->m22A8 = 0;
    p0->m22AC = 0x3F800000;
    t0 = p0->m60;
    p0->m60 = (t0 & -5);
}
