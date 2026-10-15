#include "types.h"

/* Known-positive sibling shape of GameDataRefreshWorld_3e6580 (byte-identical, in cunits). */

extern void StateBlockLinkTables_3cd5c0(s32);

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 GameDataLinkStateBlock_3ede00(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m10;
    if (t0 != 0) {
        StateBlockLinkTables_3cd5c0(t0);
    }
    return 1;
}
