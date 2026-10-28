/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjGetHitFlags_32f520 1
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
    u8 pad000[0x80];
    s32 m80;
};

s32 ScriptCmdAttackObjGetHitFlags_32f520(s32 p0, s32 p1)
{
    s32 rv;
    s32 r0;
    s32 r1;
    struct Obj0 *r2;

    if (p1 != 2) {
        return 0;
    }
    rv = -1;
    r0 = ((s32)GetObjRefTable_313de0());
    r1 = ScriptSlotGetInt_3348b0(p0);
    r2 = HandleRegistryLookup_314aa0(r0, r1);
    if (r2 != 0) {
        rv = r2->m80;
    }
    ScriptSlotStoreIntRef_3347f0((p0 + 8), rv);
    return 1;
}
