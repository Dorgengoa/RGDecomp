/* rgp:protos */
#define RGP_SELF_NavFindNodeByLinkName_3108d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(s32, s32);

s32 NavFindNodeByLinkName_3108d0(s32 p0, s32 p1)
{
    s32 r0;
    u32 r1;
    u32 l2;
    s32 l3;
    s32 r6;
    s32 r7;

    if (p1 == 0) {
        return 0;
    }
    r0 = NavGraphGetNodes_310cc0(p0);
    if (r0 != 0) {
        goto ok;
    }
    return 0;
ok:
    r1 = ((unsigned short)NavGraphGetNodeCount_310cb0(p0));
    l2 = 0;
    l3 = r0;
    while (l2 < r1) {
        r6 = NavNodeGetLinkName_3119b0(l3);
        if (r6 != 0) {
            r7 = NavNodeGetLinkName_3119b0(l3);
            if (strcmp(r7, p1) == 0) {
                return l3;
            }
        }
        l2 = (l2 + 1);
        l3 = (l3 + 0x24);
    }
    return 0;
}
