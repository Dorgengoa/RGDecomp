/* rgp:protos */
#define RGP_SELF_EvTargetPointObjDebugDraw_2f91b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EvTargetPointObjDebugDraw_2f91b0 -- same stack shape as EvFollowObjDebugDraw_2f7840. */

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Mtx { f32 m[12]; } Mtx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F020;
extern f32 D_0047F024;
extern f32 D_0047F028;
extern f32 D_0047F02C;

void EvTargetPointObjDebugDraw_2f91b0(u8 *p, void *q)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Mtx)]; char m1[0x30 + sizeof(V4)]; char m2[0x40]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Mtx) <= (0x30) && (0x0) >= 0 ? 1 : -1];
    
    V4 v __attribute__((aligned(16)));

    if (q != 0) {
        if ((*(s32 *)(p + 0xD0) & 0x2000000) != 0) {
            TargetRefGetMatrix_2e6870(p + 0xA0, &(*(Mtx *)(rgp_blk1 + 0x0)));
            v.x = D_0047F020;
            v.y = D_0047F024;
            v.z = D_0047F028;
            v.w = D_0047F02C;
            DbgDrawSphere_1cc7e0(q, &(*(V4 *)(rgp_blk1 + 0x30)), &v, TargetRefGetRadius_2e7100(p + 0xA0));
            DrawWireCube_1cc1b0(q, &(*(Mtx *)(rgp_blk1 + 0x0)), &v);
        }
    }
}
