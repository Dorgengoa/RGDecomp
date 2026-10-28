/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkAll_411d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysLinkAll_411d10(void *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 *p = (u8 *)self;
    s32 t;

    t = *(s32 *)(p + 0x14);
    if (t != 0) {
        WorldSubsysLinkParents_415ea0(t, *(s32 *)(p + 4), (int)rgp_a2, (int)rgp_a3);
    }
    t = *(s32 *)(p + 0x18);
    if (t != 0) {
        WorldSubsysLinkIds_415aa0(t, *(s32 *)(p + 4), 0, 0);
    }
    t = *(s32 *)(p + 0x8);
    if (t != 0) {
        WorldSubsysLinkIds_416a70(t, *(s32 *)(p + 4), 0, 0);
    }
    t = *(s32 *)(p + 0x1C);
    if (t != 0) {
        WorldSubsysLinkIds_4155c0(t, *(s32 *)(p + 4), 0, 0);
    }
    t = *(s32 *)(p + 0x24);
    if (t != 0) {
        WorldSubsysLinkIds_415190(t, *(s32 *)(p + 4), 0, 0);
    }
    t = *(s32 *)(p + 0x34);
    if (t != 0) {
        WorldSubsysLinkIds_4147d0(t, *(s32 *)(p + 4), 0, 0);
    }
    return 1;
}
