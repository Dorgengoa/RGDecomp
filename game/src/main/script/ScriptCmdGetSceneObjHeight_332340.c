/* rgp:protos */
#define RGP_SELF_ScriptCmdGetSceneObjHeight_332340 1
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
    u8 pad000[0x4CC];
    f32 m4CC;
};

s32 ScriptCmdGetSceneObjHeight_332340(s32 p0)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    s32 rv4;
    f32 t0;
    s32 r3;

    r0 = ScriptSlotGetInt_3348b0(p0);
    r1 = GetCurrentScene_1f5be0();
    if (r1 == 0) {
        return 0;
    }
    r2 = ObjRecGetLiveObject_1c4a90(r1, r0);
    rv4 = 1;
    if (r2 == 0) {
        rv4 = 0;
    } else {
        t0 = r2->m4CC;
        r3 = (ScriptSlotStoreFloatRef_3347d0((p0 + 8), t0), (s32)0);
        rv4 = 1;
    }
    return rv4;
}
