/* rgp:protos */
#define RGP_SELF_CharaCmdCharaShow_22e270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `beql $2,$0` into the else arm with the shared `lw $4,0x0($18)` duplicated
   into its delay slot: the FALL-THROUGH (ObjRecSetFlag2_1c3e80) is the `if` body. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

s32 CharaCmdCharaShow_22e270(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 r0;
    s32 a;
    s32 b;
    s32 o;

    if (argc != 2) {
        return 0;
    }
    r0 = GetCurrentScene_1f5be0();
    if (r0 == 0) {
        return 1;
    }
    a = ScriptArgGetInt_302d70(p1);
    b = ScriptArgGetInt_302d70(p1 + 5);
    if (b != 0) {
        o = ObjIdResolveAlias_1ce490(p0->m00, a);
        ObjRecSetFlag2_1c3e80(r0, 1, o);
    } else {
        o = ObjIdResolveAlias_1ce490(p0->m00, a);
        ObjRecClearFlag2_1c3e40(r0, 1, o);
    }
    return 1;
}
