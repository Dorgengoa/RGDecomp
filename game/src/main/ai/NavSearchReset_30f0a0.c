/* rgp:protos */
#define RGP_SELF_NavSearchReset_30f0a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 { u8 pad000[0x10E]; s16 m10E; u8 pad110[0x1]; u8 m111; };

void NavSearchReset_30f0a0(struct Obj0 *p0)
{
    s32 r1;
    u32 r2;
    u32 l3;
    s32 l4;
    s32 r6;
    u32 r7;
    u32 l8;
    s32 l9;

    if (((unsigned char)NavGraphIsValid_311140(p0)) == 0) {
        return;
    }
    r1 = NavGraphGetNodes_310cc0(p0);
    r2 = ((unsigned short)NavGraphGetNodeCount_310cb0(p0));
    l3 = 0;
    l4 = r1;
    while (l3 < r2) {
        NavNodeResetDist_311820(l4);
        l3 = (l3 + 1);
        l4 = (l4 + 0x24);
    }
    r6 = NavGraphGetEdges_310c10(p0);
    r7 = ((unsigned short)NavGraphGetEdgeCount_310c00(p0));
    l8 = 0;
    l9 = r6;
    while (l8 < r7) {
        NavEdgeSetBothDirFlags_311590(l9);
        l8 = (l8 + 1);
        l9 = (l9 + 0x14);
    }
    p0->m10E = -1;
    p0->m111 = 0;
}
