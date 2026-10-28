/* rgp:protos */
#define RGP_SELF_ScriptStrTableFree_2ccaa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004825DC;

struct Obj0;

struct Obj0 {
    u8 pad000[0xD00];
    s32 mD00;
};

void ScriptStrTableFree_2ccaa0(void)
{
    s32 t0;
    struct Obj0 *r0;
    s32 t1;
    s32 t2;

    t0 = D_004825DC;
    if (t0 != 0) {
        r0 = GetCharaResMgr_1fdb60();
        t1 = r0->mD00;
        if (t1 != 0) {
            t2 = D_004825DC;
            MemStackHeapFree_14dcb0(t1, t2);
            D_004825DC = 0;
            return;
        }
        D_004825DC = 0;
        return;
    }
}
