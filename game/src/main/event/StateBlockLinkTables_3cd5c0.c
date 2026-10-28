/* rgp:protos */
#define RGP_SELF_StateBlockLinkTables_3cd5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of GameDataRefreshWorld_3e6580 (byte-identical, in cunits). */

/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m4;
};

s32 StateBlockLinkTables_3cd5c0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 t0;

    t0 = p0->m4;
    if (t0 != 0) {
        StateTablesLinkAll_421050(t0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    }
    return 1;
}
