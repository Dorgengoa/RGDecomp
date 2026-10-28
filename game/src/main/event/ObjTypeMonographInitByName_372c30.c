/* rgp:protos */
#define RGP_SELF_ObjTypeMonographInitByName_372c30 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    s32 mE0;
    s32 mE4;
};

s32 ObjTypeMonographInitByName_372c30(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;

    ObjTypeMonographReset_372cd0(p0);
    EvObjInitByName_2f9de0(p0, p1, p2, p3);
    r2 = ((s32)GetEventObjMgr_2d1960());
    r3 = ((s32)EventObjMgrFindVolumeRecByName_2e9bc0(r2, p4));
    p0->mE0 = r3;
    r4 = ((s32)GetEventObjMgr_2d1960());
    r5 = ((s32)EventObjMgrFindParamRecByName_2e9af0(r4, p5));
    p0->mE4 = r5;
    return r5;
}
