/* rgp:protos */
#define RGP_SELF_NavFindNearestEdgePoint_310380 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct { f32 x, y, z, w; } V4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[4];

u8 *NavFindNearestEdgePoint_310380(void *self, V4 *out, V4 *pos, s32 arg3) {
    V4 p __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    u8 flag;
    u8 *res;
    u8 *e;
    f32 best;
    f32 d;
    void *n0;
    void *n1;
    u32 cnt;
    u32 i;

    if (((u8 *)NavGraphGetEdges_310c10(self)) == NULL) {
        return NULL;
    }
    flag = arg3;
    if (flag == 0) {
        NavXformPointToLocal_310d50(self, &p, pos);
    } else {
        VecCopy_1cbe30(&p, pos);
    }
    res = NULL;
    e = ((u8 *)NavGraphGetEdges_310c10(self));
    best = (f32)0xF4240 * D_0045B080[0];
    n0 = NavGraphGetNode_310cd0(self, ((short)NavEdgeGetNodeA_311700(e)));
    if (n0 == NULL) {
        return NULL;
    }
    n1 = NavGraphGetNode_310cd0(self, ((short)NavEdgeGetNodeB_3116f0(e)));
    if (n1 == NULL) {
        return NULL;
    }
    Vec3ToVec4W1_311970(n0, &a);
    Vec3ToVec4W1_311970(n1, &b);
    ClosestPointOnSegment_1c9f60(&c, &a, &b, &p);
    d = VecDistSq_1cb3c0(&c, &p);
    if (d < best) {
        VecCopy_1cbe30(out, &c);
        best = d;
        res = e;
    }
    e += 0x14;
    cnt = ((unsigned short)NavGraphGetEdgeCount_310c00(self));
    for (i = 1; i < cnt; i++, e += 0x14) {
        n0 = NavGraphGetNode_310cd0(self, ((short)NavEdgeGetNodeA_311700(e)));
        if (n0 == NULL) {
            continue;
        }
        n1 = NavGraphGetNode_310cd0(self, ((short)NavEdgeGetNodeB_3116f0(e)));
        if (n1 == NULL) {
            continue;
        }
        Vec3ToVec4W1_311970(n0, &a);
        Vec3ToVec4W1_311970(n1, &b);
        if (PointNearSegmentAabb_310620(self, &p, &a, &b, best) == 0) {
            continue;
        }
        ClosestPointOnSegment_1c9f60(&c, &a, &b, &p);
        d = VecDistSq_1cb3c0(&c, &p);
        if (d < best) {
            VecCopy_1cbe30(out, &c);
            best = d;
            res = e;
        }
    }
    if (flag == 0) {
        NavXformPointToWorld_310d10(self, out, out);
    }
    return res;
}
