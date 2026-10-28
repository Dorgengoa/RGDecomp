/* rgp:protos */
#define RGP_SELF_GameDataLinkStateBlock_3ede00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of GameDataRefreshWorld_3e6580 (byte-identical, in cunits). */

/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 GameDataLinkStateBlock_3ede00(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 t0;

    t0 = p0->m10;
    if (t0 != 0) {
        StateBlockLinkTables_3cd5c0(t0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    }
    return 1;
}
