/* rgp:protos */
#define RGP_SELF_NavGraphFindEdge_3106e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavGraphFindEdge_3106e0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 a;
    s16 *list;
    s32 r;
    s32 i;
    s32 b;
    s32 kb;
    s32 ka;

    if (NavGraphGetEdges_310c10((void *)arg0) == 0) {
        return 0;
    }
    a = ((s32)NavGraphGetNode_310cd0(arg0, arg1));
    if (a == 0) {
        return 0;
    }
    b = ((s32)NavGraphGetNode_310cd0(arg0, arg2));
    if (b == 0) {
        return 0;
    }
    ka = arg1;
    kb = arg2;
    if (((short)NavNodeGetEdgeCount_311930(b)) < ((short)NavNodeGetEdgeCount_311930(a))) {
        ka = arg2;
        a = b;
        kb = arg1;
    }
    list = ((s16 *)NavNodeGetEdgeList_311940(a));
    if (list == NULL) {
        return 0;
    }
    for (i = 0; i < ((short)NavNodeGetEdgeCount_311930(a)); i++, list++) {
        r = ((s32)NavGraphGetEdge_310c20(arg0, *list));
        if (kb == NavEdgeGetOtherNode_3116b0(r, ka)) {
            return r;
        }
    }
    return 0;
}
