#include "types.h"

extern s32 NavGraphGetEdges_310c10(void);
extern s32 NavGraphGetEdge_310c20(s32 arg0, s16 arg1);
extern s32 NavGraphGetNode_310cd0(s32 arg0, s32 arg1);
extern s32 NavEdgeGetOtherNode_3116b0(s32 arg0, s32 arg1);
extern s32 NavNodeGetEdgeCount_311930(s32 arg0);
extern s16 *NavNodeGetEdgeList_311940(s32 arg0);

s32 NavGraphFindEdge_3106e0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 a;
    s16 *list;
    s32 r;
    s32 i;
    s32 b;
    s32 kb;
    s32 ka;

    if (NavGraphGetEdges_310c10() == 0) {
        return 0;
    }
    a = NavGraphGetNode_310cd0(arg0, arg1);
    if (a == 0) {
        return 0;
    }
    b = NavGraphGetNode_310cd0(arg0, arg2);
    if (b == 0) {
        return 0;
    }
    ka = arg1;
    kb = arg2;
    if (NavNodeGetEdgeCount_311930(b) < NavNodeGetEdgeCount_311930(a)) {
        ka = arg2;
        a = b;
        kb = arg1;
    }
    list = NavNodeGetEdgeList_311940(a);
    if (list == NULL) {
        return 0;
    }
    for (i = 0; i < NavNodeGetEdgeCount_311930(a); i++, list++) {
        r = NavGraphGetEdge_310c20(arg0, *list);
        if (kb == NavEdgeGetOtherNode_3116b0(r, ka)) {
            return r;
        }
    }
    return 0;
}
