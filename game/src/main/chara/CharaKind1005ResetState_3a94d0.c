/* rgp:protos */
#define RGP_SELF_CharaKind1005ResetState_3a94d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CharaKind1002ResetState_3a99a0 (byte-identical, in cunits). */

/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 CharaKind1005ResetState_3a94d0(struct Obj0 *p0)
{
    s32 r0;
    s32 rv1;

    r0 = CharaKind1002ResetState_3a99a0(p0);
    rv1 = 1;
    if ((r0 & 0xFF) == 0) {
        rv1 = 0;
    } else {
        p0->m08 = 0x3ED;
        rv1 = 1;
    }
    return rv1;
}
